#include "pch.h"
#include "GreatAxe.h"
#include "Entities/Characters/Character.h"

GreatAxe::GreatAxe()
{
}

GreatAxe::~GreatAxe()
{
}

void GreatAxe::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 288, 184, 16, 24 });
	setOrigin(8.f, 31.f);

	m_Bounds.size = { 62.f, 62.f };
	m_HitPoints.resize(2);

	SetPosition(position);
}

void GreatAxe::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	if (m_CanHit)
	{
		for (const auto& it : args.qTree.search(m_Bounds))
		{
			if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				for (const auto& p : m_HitPoints)
					if (en->GetBounds().contains(p))
						en->TakeDamage(14);
			}
		}
	}
}

void GreatAxe::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void GreatAxe::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = { position.x + 19.f * cosf(m_Angle * acos(-1.f) / 180.f), position.y + 19.f * sinf(m_Angle * acos(-1.f) / 180.f) };
	m_HitPoints[0] = { position.x + 25.f * cosf((m_Angle - 12.f) * acos(-1.f) / 180.f), position.y + 25.f * sinf((m_Angle - 12.f) * acos(-1.f) / 180.f) };
	m_HitPoints[1] = { position.x + 25.f * cosf((m_Angle + 12.f) * acos(-1.f) / 180.f), position.y + 25.f * sinf((m_Angle + 12.f) * acos(-1.f) / 180.f) };
	m_Bounds.position = position - sf::Vector2f(31.f, 31.f);

	//          /|
	//         / |                                                5
	//   25.5 /  |      ----> 5 = 25.5 * sin (x) ---> x = arcsin( -  ) ---> x = 11.3 -> 12
	//   	 /   | 25                                            25.5
	//      /    |  ^->7 distaza da centro giocatore fino al manico + 18 pixel dove ci sono i punti
	//     /_____|
	//        5
}

EntityID GreatAxe::GetId() const
{
	return EntityID::GreatAxe;
}

void GreatAxe::Attack(float dt)
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
		if (m_ElapsedTime < 0.5f)
		{
			m_Angle = -90.f * sinf(acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			setRotation(m_Angle + 90.f);
		}
		if (m_ElapsedTime > 0.75f && m_ElapsedTime <= 1.15f)
		{
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
			m_Angle = 450.f * sinf((5.f / 4.f) * acos(-1.f) * (m_ElapsedTime - 0.75f)) - 90.f + m_AttackAngle;
			setRotation(m_Angle + 90.f);
		}
		else if (m_ElapsedTime > 1.15f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
			m_CanHit = false;
		}
	}
}
