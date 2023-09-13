#include "pch.h"
#include "ColossalGoldenSword.h"
#include "Entities/Characters/Character.h"

ColossalGoldenSword::ColossalGoldenSword()
{
}

ColossalGoldenSword::~ColossalGoldenSword()
{
}

void ColossalGoldenSword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	m_Potion.Init(resourceManager, position);

	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 307, 145, 10, 30 });
	setOrigin(5.f, 37.f);

	m_Bounds.size = { 74.f, 74.f };
	m_HitPoints.resize(4);

	SetPosition(position);
}

void ColossalGoldenSword::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	for (const auto& it : args.qTree.search(m_Bounds))
	{
		if (m_CanHit)
		{
			if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				for (const auto& p : m_HitPoints)
					if (en->GetBounds().contains(p))
						if (m_ChargingTime > 0.5f)
							en->TakeDamage(m_ChargingTime * 10.f);
						else
							en->TakeDamage(5.f);
			}
		}
	}
	m_Potion.UpdateAttackZone(args, dt);

}

void ColossalGoldenSword::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	m_Potion.RenderAttackZone(target);
}

void ColossalGoldenSword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Potion.SetPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 22.f * dir;
	m_HitPoints[0] = position + 16.f * dir;
	m_HitPoints[1] = m_Center;
	m_HitPoints[2] = position + 29.f * dir;
	m_HitPoints[3] = position + 35.f * dir;
	m_Bounds.position = position - sf::Vector2f(29.f, 29.f);

}

EntityID ColossalGoldenSword::GetId() const
{
    return EntityID::ColossalGoldenSword;
}

void ColossalGoldenSword::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking && !m_Pressed)
	{
		m_Pressed = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_Pressed)
	{
		m_Pressed = false;
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	if (m_Pressed)
	{
		if (m_ChargingTime <= 3.f)
		{
			m_ChargingTime += dt;
			if (m_ChargingTime > 3.f)
				m_ChargingTime = 3.f;
			m_RedChannel += 255.f * dt / 3.f;
			if (m_RedChannel <= 255.f)
				setColor(sf::Color(255, 255 - m_RedChannel, 255 - m_RedChannel, 255));
			else
				m_RedChannel = 255.f;
		}
		else
		{
			setColor(sf::Color::Red);
		}
	}
	else if (m_IsAttacking && !m_Pressed)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 1.f)
		{
			m_Angle = -360.f * sinf(0.5f * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 1.f && m_ElapsedTime <= 1.5f)
		{
			if (!m_PlaySound)
				MUSIC::ATTACK_SOUND->play();
			m_PlaySound = true;
			m_Angle = 720.f * sinf(acos(-1.f) * (m_ElapsedTime - 1.f)) - 360.f + m_AttackAngle;
			m_CanHit = true;
		}
		else if (m_ElapsedTime > 1.5f && m_ElapsedTime <= 2.f)
		{
			if (m_PlaySound)
				MUSIC::ATTACK_SOUND->play();
			m_PlaySound = false;
			m_Angle = -720.f * sinf(acos(-1.f) * (m_ElapsedTime - 1.5f)) + 360.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 2.f && m_ElapsedTime <= m_ChargingTime + 2.f)
		{
			if (m_CanHit)
				if (!m_Potion.IsDrinking())
					m_Potion.Drink();
			m_CanHit = false;
			m_RedChannel -= 255.f * dt / m_ChargingTime;
			if (m_RedChannel > 0.f)
				setColor(sf::Color(255, 255 - m_RedChannel, 255 - m_RedChannel, 255));
			else
				m_RedChannel = 0.f;
		}
		else if (m_ElapsedTime > m_ChargingTime + 2.f)
		{
			m_IsAttacking = false;
			m_ElapsedTime = 0.f;
			m_ChargingTime = 0.f;
			m_RedChannel = 0.f;
			setColor(sf::Color::White);
		}
		setRotation(m_Angle + 90.f);
	}
}
