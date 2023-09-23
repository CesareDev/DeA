#include "pch.h"
#include "BigDamagePotion.h"
#include "Entities/Characters/Character.h"

BigDamagePotion::BigDamagePotion()
{
}

BigDamagePotion::~BigDamagePotion()
{
}

void BigDamagePotion::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 334, 243, 10, 11 });
	setOrigin(-7.f, 5.5f);

	m_Bounds.size = { 64.f, 64.f };

	SetPosition(position);

	m_DamageArea.setRadius(0.f);
	m_DamageArea.setFillColor(sf::Color::Transparent);
	m_DamageArea.setOutlineThickness(1.f);
	m_DamageArea.setOutlineColor(sf::Color(250, 203, 52, 128));

}

void BigDamagePotion::Update(UpdateArgs args, float dt)
{
	Attack(dt);
}

void BigDamagePotion::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void BigDamagePotion::SetPosition(const sf::Vector2f& position)
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
	m_Bounds.position = position - sf::Vector2f(32.f, 32.f);

	if (m_Drinked)
		m_DamageArea.setPosition(position - sf::Vector2f(m_DamageArea.getRadius(), m_DamageArea.getRadius()));
}

EntityID BigDamagePotion::GetId() const
{
	return EntityID::BigDamagePotion;
}

void BigDamagePotion::UpdateAttackZone(UpdateArgs args, float dt)
{
	if (m_Drinked)
	{
		m_ElapsedTime += dt;
		if (m_DamageArea.getRadius() < 31.f)
			m_DamageArea.setRadius(m_DamageArea.getRadius() + 31.f * dt);
		else
			m_DamageArea.setRadius(0.f);
		for (const auto& en : args.qTree.search(m_Bounds))
		{
			if (en->obj->GetType() == EntityType::Character && en->obj->GetId() != EntityID::Player)
			{
				Character* c = (Character*)en->obj;
				if (sf::distance(c->GetCenter(), getPosition()) < m_DamageArea.getRadius() + 1.f + (c->GetBounds().size.x / 2.f))
					c->TakeDamage(3);
			}
		}
		if (m_ElapsedTime > 10.f)
		{
			m_DamageArea.setRadius(0.f);
			m_Drinked = false;
			m_ElapsedTime = 0.f;
			m_IsFinished = true;
		}
	}
}

void BigDamagePotion::RenderAttackZone(sf::RenderTarget& target)
{
	if (m_Drinked)
		target.draw(m_DamageArea);
}

void BigDamagePotion::Drink()
{
	m_Drinked = true;
}

void BigDamagePotion::Attack(float dt)
{
	if (sf::Joystick::isButtonPressed(0, 5) && !m_IsAttacking && !m_Drinked)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking && !m_Drinked)
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
