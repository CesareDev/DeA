#include "pch.h"
#include "OrcAxe.h"
#include "Entities/Characters/Character.h"

OrcAxe::OrcAxe()
{
}

OrcAxe::~OrcAxe()
{
}

void OrcAxe::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 340, 178, 10, 14 });
	setOrigin(3.f, 21.f);

	m_Bounds.size = { 42.f, 42.f };
	m_HitPoints.resize(1);

	SetPosition(position);
}

void OrcAxe::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	for (const auto& it : args.qTree.search(m_Bounds))
	{
		if (m_CanHit)
		{
			if (it->obj->GetId() == EntityID::Player)
			{
				Character* en = (Character*)it->obj;
				if (en->GetBounds().contains(m_HitPoints[0]))
					en->TakeDamage(8);
			}
		}
	}
}

void OrcAxe::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void OrcAxe::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = { position.x + 17.5f * cosf((m_Angle + 13.2f) * acos(-1.f) / 180.f), position.y + 17.5f * sinf((m_Angle + 13.2f) * acos(-1.f) / 180.f) };
	m_HitPoints[0] = m_Center;
	m_Bounds.position = position - sf::Vector2f(21.f, 21.f);
}

EntityID OrcAxe::GetId() const
{
	return EntityID::OrcAxe;
}

void OrcAxe::Attack(float dt)
{
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.25f)
		{
			m_Angle = -90.f * sinf(2.f * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.25f && m_ElapsedTime <= 0.4f)
		{
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
			m_Angle = 180.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.25)) - 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.4f && m_ElapsedTime <= 0.65f)
		{
			m_CanHit = false;
			m_Angle = -90 * sinf(2.f * acos(-1.f) * (m_ElapsedTime - 0.4f)) + 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.65f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}

void OrcAxe::StartAttack()
{
	if (!m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
}

void OrcAxe::SetAxeAngle(const sf::Vector2f& playerPosition)
{
	if (!m_IsAttacking)
	{
		m_Angle = (atan2f(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x) * 180.f / acos(-1.f));
		setRotation(m_Angle + 90.f);
	}
}
