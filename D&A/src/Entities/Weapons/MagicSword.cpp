#include "pch.h"
#include "MagicSword.h"
#include "Entities/Characters/Character.h"

MagicSword::MagicSword()
{
}

MagicSword::~MagicSword()
{
}

void MagicSword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 339, 26, 10, 21 });
	setOrigin(5.f, 28.f);

	m_Bounds.size = { 56.f, 56.f };
	m_HitPoints.resize(2);

	SetPosition(position);

	m_MagicAttack.setRadius(31.f);
	m_MagicAttack.setFillColor(sf::Color::Transparent);
	m_MagicAttack.setOutlineColor(sf::Color::Red);
	m_MagicAttack.setOutlineThickness(1.f);
}

void MagicSword::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	for (const auto& it : args.qTree.search(m_MagicAttack.getGlobalBounds()))
	{
		if (m_CanHit)
		{
			if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				for (const auto& p : m_HitPoints)
					if (en->GetBounds().contains(p))
						en->TakeDamage(3);
			}
		}
		if (m_IsMagicAttacking && it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
		{
			float d = sf::distance(getPosition(), it->obj->GetCenter());
			Character* en = (Character*)it->obj;
			if (d < 32.f + en->GetBounds().size.x)
				en->TakeDamage(1);
		}
	}
}

void MagicSword::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	if (m_IsMagicAttacking)
		target.draw(m_MagicAttack);
}

void MagicSword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_HitPoints[0] = position + 18.f * dir;
	m_HitPoints[1] = position + 27.f * dir;
	m_Bounds.position = position - sf::Vector2f(28.f, 28.f);
	m_Center = m_HitPoints[0];
	m_MagicAttack.setPosition(position - sf::Vector2f(32., 32.f));
}

EntityID MagicSword::GetId() const
{
	return EntityID::MagicSword;
}

void MagicSword::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking && !m_IsMagicAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	if (m_IsAttacking || m_IsMagicAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.25f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 90.f * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.25f && m_ElapsedTime <= 0.45f)
		{
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 180.f * sinf((5.f / 2.f) * acos(-1.f) * (m_ElapsedTime - 0.25f)) - 90.f + m_AttackAngle;
			else
				m_Angle = -180.f * sinf((5.f / 2.f) * acos(-1.f) * (m_ElapsedTime - 0.25f)) + 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.45f && m_ElapsedTime <= 0.6f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.45f)) + 90.f + m_AttackAngle;
			else
				m_Angle = 90.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.45f)) - 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.6f && m_ElapsedTime <= 1.6f)
		{
			m_IsMagicAttacking = true;
			m_IsAttacking = false;
		}
		else if (m_ElapsedTime > 1.6f)
		{
			m_ElapsedTime = 0.f;
			m_IsMagicAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
