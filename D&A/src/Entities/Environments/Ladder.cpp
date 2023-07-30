#include "pch.h"
#include "Ladder.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Init(const ResourceManager& resourceManager, const sf::Vector2f& centerPosition)
{
    setCenter(centerPosition);
    setRadius(8.f);
}

void Ladder::Update(UpdateArgs args, float dt)
{
    for (const auto& en : args.qTree.search(getGlobalBounds()))
    {
        if (en->obj->GetId() == EntityID::Player)
        {
            if (contains(en->obj->getCenter()))
            {
                args.currentLevel = m_Teleport;
            }
        }
    }
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
