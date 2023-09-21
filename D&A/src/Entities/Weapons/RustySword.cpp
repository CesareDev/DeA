#include "pch.h"
#include "RustySword.h"
#include "Entities/Characters/Character.h"

RustySword::RustySword()
{
}

RustySword::~RustySword()
{
}

void RustySword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 307, 26, 10, 21 });
	setOrigin(5.f, 28.f);

	m_Bounds.size = { 56.f, 56.f };
	m_HitPoints.resize(2);

	SetPosition(position);
}

void RustySword::Update(UpdateArgs args, float dt)
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
						en->TakeDamage(2);
			}
		}
	}
}

void RustySword::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void RustySword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 18.f * dir;
	m_HitPoints[0] = m_Center;
	m_HitPoints[1] = m_Center + 9.f * dir;
	m_Bounds.position = position - sf::Vector2f(28.f, 28.f);
}

EntityID RustySword::GetId() const
{
	return EntityID::RustySword;
}

void RustySword::Attack(float dt)
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
		else if (m_ElapsedTime > 0.6f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
