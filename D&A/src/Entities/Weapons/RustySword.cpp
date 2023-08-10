#include "pch.h"
#include "RustySword.h"

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
	for (auto it = args.qTree.begin(); it != args.qTree.end(); ++it)
	{
		if (it->obj->GetId() == EntityID::Player)
		{
			m_PlayerCenter = it->obj->GetCenter();
			SetPosition(m_PlayerCenter);
		}
	}
	Attack(dt);
}

void RustySword::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - m_PlayerCenter.y, mpos.x - m_PlayerCenter.x) * 180.f / acos(-1.f)) + 90.f;

	target.draw(*this);
}

void RustySword::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = m_Center = { getPosition().x + 18.f * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), getPosition().y + 18.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f) };
	m_HitPoints[0] = m_Center;
	m_HitPoints[1] = m_Center + sf::Vector2f(9.f * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), 9.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f));
	m_Bounds.position = position - sf::Vector2f(28.f, 28.f);
}

const sf::Vector2f& RustySword::GetCenter() const
{
	return m_Center;
}

const sf::Rectangle& RustySword::GetBounds() const
{
	return m_Bounds;
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
		m_AttackAngle = m_Angle - 90.f;
		std::cout << "Now: " << m_Angle << " " << "Target: " << m_AttackAngle << std::endl;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		setRotation(m_Angle);
	}
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime < 0.5f)
		{
			m_Angle = sinf(acos(-1.f) * m_ElapsedTime);
			setRotation(m_Angle);
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}
}
