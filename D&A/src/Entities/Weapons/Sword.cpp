#include "pch.h"
#include "Sword.h"
#include "Entities/Characters/Character.h"

Sword::Sword()
{
}

Sword::~Sword()
{
}

void Sword::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 323, 26, 10, 21 });
	setOrigin(5.f, 28.f);

	m_Bounds.size = { 56.f, 56.f };
	m_HitPoints.resize(2);

	SetPosition(position);
}

void Sword::Update(UpdateArgs args, float dt)
{
	for (auto it = args.qTree.begin(); it != args.qTree.end(); ++it)
	{
		if (it->obj->GetId() == EntityID::Player)
			SetPosition(it->obj->GetCenter());
	}
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
						en->TakeDamage(3);
			}
		}
	}
}

void Sword::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f));

	target.draw(*this);
}

void Sword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 18.f * dir;
	m_HitPoints[0] = m_Center;
	m_HitPoints[1] = m_Center + 9.f * dir;
	m_Bounds.position = position - sf::Vector2f(28.f, 28.f);
}

EntityID Sword::GetId() const
{
	return EntityID::Sword;
}

void Sword::Attack(float dt)
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
		if (m_ElapsedTime <= 0.25f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 90.f * sinf(2 * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.25f && m_ElapsedTime <= 0.35f)
		{
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 180.f * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) - 90.f + m_AttackAngle;
			else
				m_Angle = -180.f * sinf(5 * acos(-1.f) * (m_ElapsedTime - 0.25f)) + 90.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.35f && m_ElapsedTime <= 0.5f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -90.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) + 90.f + m_AttackAngle;
			else
				m_Angle = 90.f * sinf((10.f / 3.f) * acos(-1.f) * (m_ElapsedTime - 0.35f)) - 90.f + m_AttackAngle;
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
