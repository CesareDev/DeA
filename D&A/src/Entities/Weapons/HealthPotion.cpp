#include "pch.h"
#include "HealthPotion.h"

HealthPotion::HealthPotion()
{
}

HealthPotion::~HealthPotion()
{
}

void HealthPotion::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 287, 259, 8, 11 });
	setOrigin(-7.f, 5.5f);

	m_Bounds.size = { 30.f, 30.f };

	SetPosition(position);

	m_Damage = CONFIG::WEAPONS_PARAM[GetId()];
}

void HealthPotion::Update(UpdateArgs args, float dt)
{
	Attack(dt);
}

void HealthPotion::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void HealthPotion::SetPosition(const sf::Vector2f& position)
{
	if (m_IsAttacking)
	{
		sf::Vector2f adir = { cosf(m_AttackAngle * M_PI / 180.f), sinf(m_AttackAngle * M_PI / 180.f) };
		setOrigin(0.f, 5.5f);
		setPosition(position + 7.f * adir);
	}
	else
	{
		if (std::abs(m_Angle) < 90.f)
			setScale(1.f, 1.f);
		else
			setScale(1.f, -1.f);
		setOrigin(-7.f, 5.5f);
		setPosition(position);
	}
	sf::Vector2f dir = { cosf(m_Angle * M_PI / 180.f), sinf(m_Angle * M_PI / 180.f) };
	m_Center = position + 11.f * dir;
	m_Bounds.position = position - sf::Vector2f(15.f, 15.f);
}

EntityID HealthPotion::GetId() const
{
	return EntityID::HealthPotion;
}

void HealthPotion::Attack(float dt)
{
	if (sf::Joystick::isButtonPressed(0, 5) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.25f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf(2 * M_PI * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 90.f * sinf(2 * M_PI * m_ElapsedTime) + m_AttackAngle;
			setRotation(m_Angle);
		}
		else if (m_ElapsedTime > 0.75f && m_ElapsedTime <= 1.f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 90.f * sinf(2 * M_PI * (m_ElapsedTime - 0.75f)) - 90.f + m_AttackAngle;
			else
				m_Angle = -90.f * sinf(2 * M_PI * (m_ElapsedTime - 0.75f)) + 90.f + m_AttackAngle;
			setRotation(m_Angle);
		}
		else if (m_ElapsedTime > 1.f)
		{
			m_IsAttacking = false;
			m_ElapsedTime = 0.f;
			m_Drinked = true;
		}
	}
}
