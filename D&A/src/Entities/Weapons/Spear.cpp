#include "pch.h"
#include "Spear.h"
#include "Entities/Characters/Character.h"

Spear::Spear()
{
}

Spear::~Spear()
{
}

void Spear::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 309, 178, 6, 30 });
	setOrigin(3.f, 37.f);

	m_Bounds.size = { 74.f, 74.f };
	m_HitPoints.resize(1);

	SetPosition(position);
}

void Spear::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	for (const auto& it : args.qTree.search(m_Bounds))
	{
		if (m_CanHit)
		{
			if (it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				if (en->GetBounds().contains(m_HitPoints[0]))
					en->TakeDamage(12);
			}
		}
	}
}

void Spear::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Spear::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf((m_Angle) * acos(-1.f) / 180.f), sinf((m_Angle) * acos(-1.f) / 180.f) };
	m_Center = position + 22.f * dir;
	m_HitPoints[0] = position + 34.f * dir;
	m_Bounds.position = position - sf::Vector2f(37.f, 37.f);
}

EntityID Spear::GetId() const
{
    return EntityID::Spear;
}

void Spear::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking && !m_MousePressed)
	{
		m_IsAttacking = true;
		m_MousePressed = true;
		m_AttackAngle = m_Angle;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_MousePressed = false;
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.15f)
		{
			if (!m_PlaySound)
				MUSIC::ATTACK_SOUND->play();
			m_PlaySound = true;
			m_CanHit = true;
			float mag = 15.f * sinf((10.f / 3.f) * acos(-1.f) * m_ElapsedTime);
			const auto& pos = getPosition();
			SetPosition({ pos.x + mag * cosf(m_Angle * acos(-1.f) / 180.f), pos.y + mag * sinf(m_Angle * acos(-1.f) / 180.f) });
		}
		else if (m_ElapsedTime > 0.2f && m_ElapsedTime <= 0.35f)
		{	
			m_Angle = -30.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.2f)) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
		{
			if (m_PlaySound)
				MUSIC::ATTACK_SOUND->play();
			m_PlaySound = false;
			float mag = 15.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f));
			const auto& pos = getPosition();
			SetPosition({ pos.x + mag * cosf(m_Angle *acos(-1.f) / 180.f), pos.y + mag * sinf(m_Angle *acos(-1.f) / 180.f) });
		}
		else if (m_ElapsedTime > 0.55f && m_ElapsedTime <= 0.7f)
		{
			m_Angle = 60.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.55f)) - 30.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.7f && m_ElapsedTime <= 0.85f)
		{
			if (!m_PlaySound)
				MUSIC::ATTACK_SOUND->play();
			m_PlaySound = true;
			float mag = 15.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.7f));
			const auto& pos = getPosition();
			SetPosition({ pos.x + mag * cosf(m_Angle *acos(-1.f) / 180.f), pos.y + mag * sinf(m_Angle *acos(-1.f) / 180.f) });
		}
		else if (m_ElapsedTime > 0.9f && m_ElapsedTime <= 1.05f)
		{
			m_Angle = -30.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.9f)) + 30 + m_AttackAngle;
		}
		else if (!m_MousePressed && m_ElapsedTime > 1.05f)
		{
			m_CanHit = false;
			m_PlaySound = false;
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
