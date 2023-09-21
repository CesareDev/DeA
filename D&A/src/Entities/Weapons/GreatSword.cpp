#include "pch.h"
#include "GreatSword.h"
#include "Entities/Characters/Character.h"

GreatSword::GreatSword()
{
}

GreatSword::~GreatSword()
{
}

void GreatSword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 307, 86, 10, 25 });
	setOrigin(5.f, 32.f);

	m_Bounds.size = { 64.f, 64.f };
	m_HitPoints.resize(3);

	SetPosition(position);
}

void GreatSword::Update(UpdateArgs args, float dt)
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
						en->TakeDamage(15);
			}
		}
	}
}

void GreatSword::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void GreatSword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 19.f * dir;
	m_HitPoints[0] = position + 17.f * dir;
	m_HitPoints[1] = position + 24.f * dir;
	m_HitPoints[2] = position + 30.f * dir;
	m_Bounds.position = position - sf::Vector2f(32.f, 32.f);
}

EntityID GreatSword::GetId() const
{
	return EntityID::GreatSword;
}

void GreatSword::Attack(float dt)
{
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
			m_Angle = -60.f * sinf(2.f * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
		{
			m_Angle = 330.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) - 60.f + m_AttackAngle;
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
		}
		else if (m_ElapsedTime > 0.5f && m_ElapsedTime <= 0.8f)
		{
			m_Angle = -270.f * sinf((5.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.5f)) + 270.f + m_AttackAngle;
			m_CanHit = false;
		}
		else if (m_ElapsedTime > 0.8f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
