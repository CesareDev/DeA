#include "pch.h"
#include "Hammer.h"
#include "Entities/Characters/Character.h"

Hammer::Hammer()
{
}

Hammer::~Hammer()
{
}

void Hammer::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 307, 55, 10, 24 });
	setOrigin(5.f, 31.f);

	m_Bounds.size = { 62.f, 62.f };
	m_HitPoints.resize(1);

	SetPosition(position);
}

void Hammer::Update(UpdateArgs args, float dt)
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
					en->TakeDamage(2);
			}
		}
	}
}

void Hammer::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - getPosition().y, mpos.x - getPosition().x) * 180.f / acos(-1.f));

	target.draw(*this);

	sf::RectangleShape r({ 1.f, 1.f });
	r.setPosition(m_HitPoints[0]);
	r.setFillColor(sf::Color::Green);
	target.draw(r);
}

void Hammer::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 19.f * dir;
	m_HitPoints[0] = position + 27.f * dir;
	m_Bounds.position = position - sf::Vector2f(31.f, 31.f);
}

EntityID Hammer::GetId() const
{
	return EntityID::Hammer;
}

void Hammer::Attack(float dt)
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
		if (m_ElapsedTime <= 0.1f)
		{
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -60.f * sinf(5.f * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
			else
				m_Angle = 60.f * sinf(5.f * acos(-1.f) * m_ElapsedTime) + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.1f && m_ElapsedTime <= 0.2f)
		{
			m_CanHit = true;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = 120.f * sinf(5.f* acos(-1.f) * (m_ElapsedTime - 0.1f)) - 60.f + m_AttackAngle;
			else
				m_Angle = -120.f * sinf(5.f * acos(-1.f) * (m_ElapsedTime - 0.1f)) + 60.f + m_AttackAngle;
		}
		else if (m_ElapsedTime > 0.2f && m_ElapsedTime <= 0.3f)
		{
			m_CanHit = false;
			if (std::abs(m_AttackAngle) < 90.f)
				m_Angle = -60.f * sinf(5.f * acos(-1.f) * (m_ElapsedTime - 0.2f)) + 60.f + m_AttackAngle;
			else
				m_Angle = 60.f * sinf(5.f * acos(-1.f) * (m_ElapsedTime - 0.2f)) - 60.f + m_AttackAngle;
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
		setRotation(m_Angle + 90.f);
	}
}
