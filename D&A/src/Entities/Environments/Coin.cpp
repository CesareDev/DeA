#include "pch.h"
#include "Coin.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 445, 115, 8, 8 });
	m_TextureRect = getTextureRect();

	m_Bounds.size = { 8.f, 8.f };

	SetPosition(position);
}

void Coin::Update(UpdateArgs args, float dt)
{
	m_ElapsedTime += dt;
	if (m_Spawned)
	{
		m_BounceElapsedTime += dt;
		if (m_BounceElapsedTime <= 1.f)
		{
			float y = 8.f * (1.f - m_BounceElapsedTime) * -std::abs(sinf(4 * acos(-1.f) * m_BounceElapsedTime)) + m_SpawnY;
			SetPosition({ getPosition().x, y });
		}
		else
		{
			m_BounceElapsedTime = 0.f;
			m_Spawned = false;
		}
	}
	if (m_ElapsedTime > 0.1f)
	{
		setTextureRect(m_TextureRect);
		m_TextureRect.left += 8;
		if (m_TextureRect.left >= 469)
		{
			m_TextureRect.left = 445;
			m_CanBePicked = true;
		}
		m_ElapsedTime = 0.f;
	}
}

void Coin::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Coin::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(4.f, 4.f);
	m_Bounds.position = position;
}

EntityID Coin::GetId() const
{
	if (m_CanBePicked)
		return EntityID::Coin;
	return EntityID::Null;
}

void Coin::SetSpawnY(float y)
{
	m_SpawnY = y;
}
