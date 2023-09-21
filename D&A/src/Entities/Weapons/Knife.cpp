#include "pch.h"
#include "Knife.h"
#include "Entities/Characters/Character.h"

Knife::Knife()
{
}

Knife::~Knife()
{
}

void Knife::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 293, 18, 6, 13 });
	setOrigin(3.f, 20.f);

	m_Bounds.size = { 40.f, 40.f };
	m_HitPoints.resize(1);

	SetPosition(position);
}

void Knife::Update(UpdateArgs args, float dt)
{
	Attack(dt);
	if (m_CanHit)
	{
		for (const auto& it : args.qTree.search(m_Bounds))
		{
			if(it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
			{
				Character* en = (Character*)it->obj;
				if (en->GetBounds().contains(m_HitPoints[0]))
					en->TakeDamage(1);
			}
		}
	}
}

void Knife::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Knife::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = { position.x + 17.f * cosf((m_Angle) * acos(-1.f) / 180.f), position.y + 17.f * sinf((m_Angle) * acos(-1.f) / 180.f) };
	m_HitPoints[0] = m_Center;
	m_Bounds.position = position - sf::Vector2f(20.f, 20.f);
}

EntityID Knife::GetId() const
{
	return EntityID::Knife;
}

void Knife::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking && !m_MousePressed)
	{
		m_IsAttacking = true;
		m_MousePressed = true;
		m_AttackAngle = m_Angle - 90.f;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_MousePressed = false;
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime < 0.2f)
		{
			if (!m_CanHit)
				MUSIC::ATTACK_SOUND->play();
			m_CanHit = true;
			float mag = 5.f * sinf(5.f * acos(-1.f) * m_ElapsedTime);
			const auto& pos = getPosition();
			SetPosition({ pos.x + mag * cosf((m_Angle) * acos(-1.f) / 180.f), pos.y + mag * sinf((m_Angle) * acos(-1.f) / 180.f) });
		}
		else if (!m_MousePressed)
		{
			m_CanHit = false;
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}
}
