#include "pch.h"
#include "Mace.h"
#include "Core/Camera.h"

Mace::Mace()
{
}

Mace::~Mace()
{
}

void Mace::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 323, 57, 10, 22 });
	setOrigin(5.f, 29.f);

	m_Bounds.size = { 32.f, 32.f };
	m_HitPoints.resize(3);

	SetPosition(position);
}

void Mace::Update(UpdateArgs args, float dt)
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

static int count = 0;

void Mace::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	if (!m_IsAttacking)
		m_Angle = (atan2f(mpos.y - m_PlayerCenter.y, mpos.x - m_PlayerCenter.x) * 180.f / acos(-1.f)) + 90.f;

	target.draw(*this);
}

void Mace::SetPosition(const sf::Vector2f& position)
{
	if (m_IsAttacking)
	{
		setOrigin(5.f, 22.f);
		setPosition(position.x + 7.f * cosf(m_AttackAngle * acos(-1.f) / 180.f), position.y + 7.f * sinf(m_AttackAngle * acos(-1.f) / 180.f));
		m_Center = { getPosition().x + 9 * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), getPosition().y + 9 * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f) };
	}
	else
	{
		setOrigin(5.f, 29.f);
		setPosition(position);
		m_Center = { getPosition().x + 14.f * cosf((m_Angle -90.f) * acos(-1.f) / 180.f), getPosition().y + 14.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f)};
	}
	m_HitPoints[0] = m_Center;
	m_HitPoints[1] = m_HitPoints[0] + sf::Vector2f(7.f * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), 7.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f));
	m_HitPoints[2] = m_HitPoints[1] + sf::Vector2f(7.f * cosf((m_Angle - 90.f) * acos(-1.f) / 180.f), 7.f * sinf((m_Angle - 90.f) * acos(-1.f) / 180.f));;
	m_Bounds.position = getPosition() - sf::Vector2f(16.f, 16.f);
}

const sf::Vector2f& Mace::GetCenter() const
{ 
	return m_Center;
}

const sf::Rectangle& Mace::GetBounds() const
{
	return m_Bounds;
}

EntityID Mace::GetId() const
{
	return EntityID::Mace;
}

void Mace::Attack(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		m_IsAttacking = true;
		m_AttackAngle = m_Angle - 90.f;
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
			if (m_AttackAngle < 0)
				m_Angle = m_AttackAngle - 120 * sinf(4 * acos(-1.f) * m_ElapsedTime) + 90.f;
			else
				m_Angle = m_AttackAngle + 120 * sinf(4 * acos(-1.f) * m_ElapsedTime) + 90.f;
			setRotation(m_Angle);
		}
		else
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}
}