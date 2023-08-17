#include "pch.h"
#include "GreatHammer.h"
#include "Entities/Characters/Character.h"

GreatHammer::GreatHammer()
{
}

GreatHammer::~GreatHammer()
{
}

void GreatHammer::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 291, 42, 10, 37 });
	setOrigin(5.f, 42.f);

	m_Bounds.size = { 84.f, 84.f };
	m_HitPoints.resize(1);

	SetPosition(position);
}

void GreatHammer::Update(UpdateArgs args, float dt)
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
					en->TakeDamage(10);
			}
		}
	}
}

void GreatHammer::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f));

	target.draw(*this);
}

void GreatHammer::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 25.5f * dir;
	m_HitPoints[0] = position + 38.f * dir;
	m_Bounds.position = position - sf::Vector2f(42.f, 42.f);
}

EntityID GreatHammer::GetId() const
{
    return EntityID::GreatHammer;
}

void GreatHammer::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		setRotation(m_Angle + 90.f);
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime <= 0.5)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf(acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 90.f * sinf(acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.6 && m_ElapsedTime <= 0.75)
		{
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 180.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.6f)) - 90.f + m_AttackAngle;
			else
				m_Angle = -180.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.6f)) + 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.9f && m_ElapsedTime <= 1.1f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf((5.f / 2.f) * acos(-1.f) * (m_ElapsedTime - 0.9f)) + 90.f + m_AttackAngle;
			else
				m_Angle = 90.f * sinf((5.f / 2.f) * acos(-1.f) * (m_ElapsedTime - 0.9f)) - 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 1.1f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
