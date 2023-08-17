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
					en->TakeDamage(1);
			}
		}
	}
}

void Spear::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f));

	target.draw(*this);
}

void Spear::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), sinf((m_Angle - 90.f) * acos(-1.f) / 180.f) };
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
		setRotation(m_Angle + 90.f);
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime < 0.2f)
		{
			m_CanHit = true;
			float mag = 5.f * sinf((5.f / 2.f) * acos(-1.f) * m_ElapsedTime);
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
