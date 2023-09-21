#include "pch.h"
#include "GreatMace.h"
#include "Entities/Characters/Character.h"

GreatMace::GreatMace()
{
}

GreatMace::~GreatMace()
{
}

void GreatMace::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 339, 55, 10, 24 });
	setOrigin(5.f, 31.f);

	m_Bounds.size = { 62.f, 62.f };
	m_HitPoints.resize(2);

	SetPosition(position);
}

void GreatMace::Update(UpdateArgs args, float dt)
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
						en->TakeDamage(7);
			}
		}
	}
}

void GreatMace::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void GreatMace::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 17.f * dir;
	m_HitPoints[0] = position + 21.f * dir;
	m_HitPoints[1] = position + 26.f * dir;
	m_Bounds.position = position - sf::Vector2f(31.f, 31.f);
}

EntityID GreatMace::GetId() const
{
    return EntityID::GreatMace;
}

void GreatMace::Attack(float dt)
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
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = - 60 * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 60 * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.25f && m_ElapsedTime <= 0.35f)
		{
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 120 * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) - 60.f + m_AttackAngle;
			else
				m_Angle = -120 * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) + 60.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = - 60 * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) + 60.f + m_AttackAngle;
			else
				m_Angle = 60 * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) - 60.f + m_AttackAngle;
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
