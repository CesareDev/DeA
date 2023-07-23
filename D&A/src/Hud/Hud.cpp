#include "pch.h"
#include "Hud.h"

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::Init(const TextureManager& textureManager, const Player* player)
{
	m_Player = player;
}

void Hud::Update(float dt)
{
}

void Hud::Render(sf::RenderTarget& target)
{
}
