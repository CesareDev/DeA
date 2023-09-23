#include "pch.h"
#include "Princess.h"

Princess::Princess()
{
}

Princess::~Princess()
{
}

void Princess::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 128, 16, 16, 16 });
	m_TextureRect = getTextureRect();
	m_Bounds.size = { 16.f, 16.f };

	SetPosition(position);
}

void Princess::Update(UpdateArgs args, float dt)
{
	if (m_Player)
	{
		if (m_Player->GetBounds().overlaps(m_Bounds))
			args.currentState = StateID::WinState;
	}
	m_ElapsedAnimationTime += dt;
	if (m_ElapsedAnimationTime > 0.1f)
	{
		setTextureRect(m_TextureRect);
		m_TextureRect.left += 16;
		if (m_TextureRect.left >= 192)
		{
			m_TextureRect.left = 128;
		}
		m_ElapsedAnimationTime = 0.f;
	}
}

void Princess::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Princess::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Bounds.position = position;
}

EntityID Princess::GetId() const
{
	return EntityID();
}

void Princess::SetPlayer(const Character& player)
{
	m_Player = &player;
}
