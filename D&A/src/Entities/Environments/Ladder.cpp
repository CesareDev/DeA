#include "pch.h"
#include "Ladder.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    SetPosition(position);
}

void Ladder::Update(UpdateArgs args, float dt)
{
    for (const auto& en : args.qTree.search(m_Bounds))
    {
        if (en->obj->GetId() == EntityID::Player)
        {
            auto d = sf::distance(en->obj->GetCenter(), GetCenter());
            if (d < 4.f)
            {
                args.currentLevel = m_Teleport;
                args.entranceIndex = m_TeleportEntranceIndex;
            }
        }
    }
}

void Ladder::Render(sf::RenderTarget& target)
{
}

void Ladder::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    m_Center = position + sf::Vector2f(8.f, 8.f);
    m_Bounds = { position, {16.f, 16.f} };
}

EntityID Ladder::GetId() const
{
    return EntityID::Ladder;
}

void Ladder::SetTeleportLevel(LevelID teleportLevel, unsigned int teleportEntranceIndex)
{
    m_Teleport = teleportLevel;
    m_TeleportEntranceIndex = teleportEntranceIndex;
}
