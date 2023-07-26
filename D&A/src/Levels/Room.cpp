#include "pch.h"
#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

bool Room::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);
}

bool Room::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void Room::Init(const TextureManager& textureManager, Player* player, unsigned int entranceIndex)
{
	m_Player = player;
    m_Transition.Init(textureManager);
	m_Map.load("res/map.tmx");
	if (entranceIndex == 0)
	{
		m_Player->setCenter({ 32.f, 48.f });
	}
	else
	{
		m_Player->setCenter({ 272.f, 48.f });
	}
}

void Room::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	m_Player->Update({ m_Tree, m_Map, currentState, currentLevel }, dt);
	m_Map.update(dt);
}

void Room::Render(sf::RenderTarget& target)
{
	target.setView(target.getDefaultView());
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);
	m_Player->Render(target);
	m_Map.drawLayer(target, 2);
	m_Transition.Render(target);
}
