#include "pch.h"
#include "BigHealthPotion.h"
#include "Entities/Characters/Character.h"

BigHealthPotion::BigHealthPotion()
{
}

BigHealthPotion::~BigHealthPotion()
{
}

void BigHealthPotion::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 286, 243, 10, 11 });
	setOrigin(-7.f, 5.5f);

	m_Bounds.size = { 34.f, 34.f };

	SetPosition(position);
}

void BigHealthPotion::Update(UpdateArgs args, float dt)
{
	Attack(dt);
}

void BigHealthPotion::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void BigHealthPotion::SetPosition(const sf::Vector2f& position)
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
	m_Center = position + 12.f * dir;
	m_Bounds.position = position - sf::Vector2f(15.f, 15.f);
}

EntityID BigHealthPotion::GetId() const
{
    return EntityID::BigHealthPotion;
}

void BigHealthPotion::Attack(float dt)
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
		else if (m_ElapsedTime > 1.25f && m_ElapsedTime <= 1.5f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 90.f * sinf(2 * M_PI * (m_ElapsedTime - 1.25f)) - 90.f + m_AttackAngle;
			else
				m_Angle = -90.f * sinf(2 * M_PI * (m_ElapsedTime - 1.25f)) + 90.f + m_AttackAngle;
			setRotation(m_Angle);
		}
		else if (m_ElapsedTime > 1.5f)
		{
			m_Drinked = true;
			m_IsAttacking = false;
			m_ElapsedTime = 0.f;
		}
	}
}
