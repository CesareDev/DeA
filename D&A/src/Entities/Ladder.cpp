#include "pch.h"
#include "Ladder.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Init(const TextureManager& textureManager, const sf::Vector2f& centerPosition)
{
    setCenter(centerPosition);
    setRadius(8.f);
}

void Ladder::Update(UpdateArgs args, float dt)
{
}

void Ladder::Render(sf::RenderTarget& target)
{
}

EntityID Ladder::GetId() const
{
    return EntityID::Ladder;
}

void Ladder::SetTeleportLevel(LevelID teleportLevel)
{
    m_Teleport = teleportLevel;
}

void Ladder::Teleport(LevelID& currentLevel)
{
    if (m_Teleport != LevelID::Null)
        currentLevel = m_Teleport;
}
