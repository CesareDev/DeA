#include "pch.h"
#include "Slug.h"

Slug::Slug()
{
}

Slug::~Slug()
{
}

void Slug::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setOrigin(0.f, 8.f);
    setTextureRect({ 368, 431, 16, 24 });
    setPosition(position);

    m_Center = getPosition() + sf::Vector2f(8.f, 8.f);
    m_Bounds = { getPosition(), {16.f, 16.f} };
    m_IsMoving = false;
    m_ElapsedAnimationTime = 0.f;
    m_TextureRect = getTextureRect();

	m_Health = 5;
	m_Vulnerable = true;
	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
	m_DamageTaken.setFont(font);
	m_DamageTaken.setCharacterSize(40);
	m_DamageTaken.setScale(0.f, 0.f);
	m_DamageTaken.setOutlineColor(sf::Color::Black);
	m_DamageTaken.setOutlineThickness(4.f);
}

void Slug::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Rectangle attackArea = { GetCenter() - sf::Vector2f(64.f, 64.f), {128.f, 128.f} };
		m_Velocity = { 0.f, 0.f };

		for (const auto& it : args.qTree.search(attackArea))
		{
			if (it->obj->GetId() == EntityID::Player)
			{
				const auto& ppos = it->obj->GetCenter();
				float mag = sf::distance(ppos, GetCenter());
				sf::Vector2f dir = { 0.f, 0.f };
				if (mag > 0.5f)
				{
					dir = (ppos - GetCenter()) / mag;
					m_IsMoving = true;
				}
				m_Velocity = dir * 8.f;
			}
		}

		if (m_Velocity.x < 0.f)
		{
			setOrigin(m_TextureRect.width, 8.f);
			setScale(-1.f, 1.f);
		}
		else if (m_Velocity.x > 0.f)
		{
			setOrigin(0.f, 8.f);
			setScale(1.f, 1.f);
		}

		sf::Vector2f potentialPos = getPosition() + m_Velocity * dt;

		sf::Vector2f potentialPosInUnit = { potentialPos.x / m_TextureRect.width, potentialPos.y / m_TextureRect.width };
		sf::Vector2f positionInUnit = { getPosition().x / m_TextureRect.width, getPosition().y / m_TextureRect.width };

		bool wallx = false;
		bool wally = false;

		//Left
		if (m_Velocity.x < 0)
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y + 0.9f)))
			{
				potentialPosInUnit.x = (int)potentialPosInUnit.x + 1;
				m_Velocity.x = 0.f;
				m_Velocity.y = (m_Velocity.y > 0 ? 1 : -1) * 8.f; //fixed vel
				wallx = true;
			}
		}
		//Right
		else
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y + 0.9f)))
			{
				potentialPosInUnit.x = (int)potentialPosInUnit.x;
				m_Velocity.x = 0.f;
				m_Velocity.y = (m_Velocity.y > 0 ? 1 : -1) * 8.f;
				wallx = true;
			}
		}

		//Up
		if (m_Velocity.y < 0)
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y)))
			{
				potentialPosInUnit.y = (int)potentialPosInUnit.y + 1;
				m_Velocity.y = 0.f;
				m_Velocity.x = (m_Velocity.x > 0 ? 1 : -1) * 8.f;
				wally = true;
			}
		}
		//Down
		else
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y + 1.f)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y + 1.f)))
			{
				potentialPosInUnit.y = (int)potentialPosInUnit.y;
				m_Velocity.y = 0.f;
				m_Velocity.x = (m_Velocity.x > 0 ? 1 : -1) * 8.f;
				wally = true;
			}
		}

		if (wallx)
			potentialPos.y = (potentialPosInUnit.y * m_TextureRect.width) + (m_Velocity.y * dt);
		else
			potentialPos.y = potentialPosInUnit.y * m_TextureRect.width;

		if (wally)
			potentialPos.x = (potentialPosInUnit.x * m_TextureRect.width) + (m_Velocity.x * dt);
		else
			potentialPos.x = potentialPosInUnit.x * m_TextureRect.width;


		SetPosition(potentialPos);
																											 //40 perchè il testo deve stare al centro dell'entità per questo deve essere slittato di 8 (metà della lunghezza dell'entità) verso destra poi * 5
		m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + 40.f), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height));
		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.25f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 455;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 416)
				{
					m_TextureRect.left = 368;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 431;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 416)
				{
					m_TextureRect.left = 368;
				}
				m_ElapsedAnimationTime = 0.f;
			}
		}

		//Damage
		if (!m_Vulnerable)
		{
			m_VulnerableTime += dt;
			sf::Vector2f s = m_DamageTaken.getScale();
			setColor(sf::Color::Red);
			if (s.x <= 1.f)
				m_DamageTaken.setScale(s.x + 4.f * dt, s.y + 4.f * dt);
			if (m_VulnerableTime > 1.f)
			{
				setColor(sf::Color::White);
				m_DamageTaken.setScale(0.f, 0.f);
				m_Vulnerable = true;
				m_VulnerableTime = 0.f;
			}
		}
	}
	else
	{
		m_VulnerableTime += dt;
		m_DamageTaken.setPosition(int(getPosition().x * 5.f - m_DamageTaken.getGlobalBounds().width / 2.f + 40.f), int(getPosition().y * 5.f - m_DamageTaken.getGlobalBounds().height - 80.f));
		sf::Vector2f st = m_DamageTaken.getScale();
		if (st.x <= 1.f)
			m_DamageTaken.setScale(st.x + 4.f * dt, st.y + 4.f * dt);
		sf::Vector2f o = getOrigin();
		setOrigin(o.x, 24.f);
		sf::Vector2f s = getScale();
		setColor(sf::Color::Blue);
		if (s.y == 1.f)
			setPosition({ getPosition().x, getPosition().y + 16.f });
		if (s.y > 0.f)
			setScale(s.x, s.y - dt);
		else
		{
			m_DamageTaken.setScale(0.f, 0.f);
			m_VulnerableTime = 0.f;
			m_IsDead = true;
		}
	}
}

void Slug::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	if (m_VulnerableTime > 0.f)
	{
		sf::View currentCamera = target.getView();
		sf::View v(currentCamera.getCenter() * 5.f, currentCamera.getSize() * 5.f);
		target.setView(v);
		target.draw(m_DamageTaken);

		target.setView(currentCamera);
	}
}

void Slug::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	m_Bounds.position = getPosition();
}

const sf::Vector2f& Slug::GetCenter() const
{
	return m_Center;
}

const sf::Rectangle& Slug::GetBounds() const
{
	return m_Bounds;
}

void Slug::TakeDamage(unsigned int damage)
{
	if (m_Vulnerable)
	{
		m_DamageTaken.setString(std::to_string(damage));
		m_Health -= damage;
		m_Vulnerable = false;
	}
}

EntityID Slug::GetId() const
{
    return EntityID::Slug;
}
