#include "pch.h"
#include "Bow.h"

Bow::Bow()
{
}

Bow::~Bow()
{
}

void Bow::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 296, 212, 7, 26 });
	setOrigin(-7.f, 13.f);

	m_Bounds.size = { 26.f, 26.f };

	SetPosition(position);

	m_ResourceManager = &resourceManager;
}

void Bow::Update(UpdateArgs args, float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_IsAttacking)
	{
		setTextureRect({ 305, 212, 14, 26 });
		setOrigin(0.f, 13.f);
		if (!m_MousePressed)
		{
			m_ArrowsQueue.emplace();
			m_ArrowsQueue.back().Init(*m_ResourceManager, getPosition());
		}
		m_ArrowsQueue.back().Spawn(m_Angle, getPosition(), dt);
		m_MousePressed = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MousePressed)
	{
		setTextureRect({ 296, 212, 7, 26 });
		setOrigin(-7.f, 13.f);
		m_IsAttacking = true;
		m_MousePressed = false;
		MUSIC::ATTACK_SOUND->play();
		m_ArrowsQueue.back().Shoot();
		args.qTree.insert(&m_ArrowsQueue.back(), m_ArrowsQueue.back().GetBounds());
	}
	setRotation(m_Angle);
	if (m_IsAttacking)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime > 0.5f)
		{
			m_ElapsedTime = 0.f;
			m_IsAttacking = false;
		}
	}

	//check arrows life
	if (!m_ArrowsQueue.empty())
		if (m_ArrowsQueue.front().IsDead())
			m_ArrowsQueue.pop();
}

void Bow::Render(sf::RenderTarget& target)
{
	target.draw(*this);

	if (!m_ArrowsQueue.empty())
		if (!m_ArrowsQueue.back().IsShooted())
			m_ArrowsQueue.back().Render(target);
}

void Bow::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	sf::Vector2f dir = { cosf(m_Angle * acos(-1.f) / 180.f), sinf(m_Angle * acos(-1.f) / 180.f) };
	m_Center = position + 11.f * dir;
	m_Bounds.position = position - sf::Vector2f(13.f, 13.f);
}

EntityID Bow::GetId() const
{
    return EntityID::Bow;
}

void Bow::Attack(float dt)
{
}
