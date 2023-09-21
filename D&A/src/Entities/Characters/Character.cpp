#include "pch.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::RenderWeapon(sf::RenderTarget& target)
{
}

EntityType Character::GetType() const
{
    return EntityType::Character;
}

void Character::TakeDamage(unsigned int damage)
{
	if (m_Vulnerable)
	{
		m_DamageTaken.setString(std::to_string(damage));
		m_Health -= damage;
		m_Vulnerable = false;
		if (GetId() == EntityID::Player)
			MUSIC::PLAYER_DAMAGE_SOUND->play();
		else
			MUSIC::DAMAGE_SOUND->play();
	}		
}

void Character::RenderDamage(sf::RenderTarget& target)
{
	if (m_VulnerableTime > 0.f)
	{
		sf::View currentCamera = target.getView();
		sf::View v(currentCamera.getCenter() * 5.f, currentCamera.getSize() * 5.f);
		target.setView(v);
		target.draw(m_DamageTaken);
		target.setView(currentCamera);
	}
}

void Character::InitDamageText(const ResourceManager& resourceManager)
{
	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
	m_DamageTaken.setFont(font);
	m_DamageTaken.setCharacterSize(40);
	m_DamageTaken.setScale(0.f, 0.f);
	m_DamageTaken.setOutlineColor(sf::Color::Black);
	m_DamageTaken.setOutlineThickness(4.f);
}

void Character::SpawnCoins(UpdateArgs args)
{
	if (m_IsDead)
	{
		for (auto& c : m_Coins)
		{
			float angle = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.f));
			sf::Vector2f dir = { cosf(angle * acos(-1.f) / 180.f), sinf(angle * acos(-1.f) / 180.f) };
			dir *= 4.f;
			c->SetSpawnY(m_Center.y);
			c->SetPosition(m_Center + dir);
			args.qTree.insert(c, c->GetBounds());
		}
	}
}

void Character::DamageAnimation(float dt)
{
	m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + (m_TextureRect.width / 2.f * 5.f)), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height));
	if (!m_Vulnerable)
	{
		m_VulnerableTime += dt;
		if (m_VulnerableTime <= 0.5f)
		{
			if (m_DamageTaken.getScale().x < 1.f)
				m_DamageTaken.setScale(4.f * m_VulnerableTime, 4.f * m_VulnerableTime);
			else
				m_DamageTaken.setScale(1.f, 1.f);
			m_IntervalTime += dt;
			setColor(sf::Color::White);
			if (m_IntervalTime < 0.1f)
				setColor(sf::Color::Red);
			else
				m_IntervalTime = 0.f;
		}
		else
		{
			setColor(sf::Color::White);
			m_DamageTaken.setScale(0.f, 0.f);
			m_Vulnerable = true;
			m_VulnerableTime = 0.f;
		}
	}
}

void Character::DeathAnimation(float dt)
{
	m_VulnerableTime += dt;
	m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + (m_TextureRect.width / 2.f * 5.f)), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height - (m_TextureRect.height * 5.f)));
	sf::Vector2f st = m_DamageTaken.getScale();
	if (st.x <= 1.f)
		m_DamageTaken.setScale(st.x + 4.f * dt, st.y + 4.f * dt);
	sf::Vector2f o = getOrigin();
	setOrigin(o.x, getTextureRect().height);
	sf::Vector2f s = getScale();
	setColor(sf::Color(50, 50, 50, 255)); //darkgrey
	if (s.y == 1.f)
		setPosition({ getPosition().x, getPosition().y + m_Bounds.size.y});
	if (s.y > 0.f)
		setScale(s.x, s.y - dt);
	else
	{
		m_DamageTaken.setScale(0.f, 0.f);
		m_VulnerableTime = 0.f;
		m_IsDead = true;
	}
}
