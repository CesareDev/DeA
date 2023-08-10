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
	for (auto it = args.qTree.begin(); it != args.qTree.end(); ++it)
	{
		if (it->obj->GetId() == EntityID::Player)
		{
			m_PlayerCenter = it->obj->GetCenter();
			SetPosition(m_PlayerCenter);
		}
	}
	Attack(dt);
	for (const auto& it : args.qTree.search(m_Bounds))
	{
		if (m_IsAttacking && it->obj->GetId() != EntityID::Player && it->obj->GetType() == EntityType::Character)
		{
			Character* en = (Character*)it->obj;
			if (en->GetBounds().contains(m_HitPoints[0]))
				en->TakeDamage(1);
		}
	}
}

void Knife::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - m_PlayerCenter.y, mpos.x - m_PlayerCenter.x) * 180.f / acos(-1.f)) + 90.f;

	target.draw(*this);
}

void Knife::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = { getPosition().x + 17.f * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), getPosition().y + 17.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f) };
	m_HitPoints[0] = m_Center;
	m_Bounds.position = getPosition() - sf::Vector2f(20.f, 20.f);
}

const sf::Vector2f& Knife::GetCenter() const
{
	return m_Center;
}

const sf::Rectangle& Knife::GetBounds() const
{
	return m_Bounds;
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
		setRotation(m_Angle);
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime < 0.2f)
		{
			float mag = 5.f * sinf(10.f * acos(-1.f) * m_ElapsedTime);
			const auto& pos = getPosition();
			SetPosition({ pos.x + mag * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), pos.y + mag * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f) });
		}
		else if (!m_MousePressed)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}
}
