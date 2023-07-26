#include "pch.h"
#include "Hub.h"

Hub::Hub()
{
}

Hub::~Hub()
{
}

bool Hub::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool Hub::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void Hub::Init(const TextureManager& textureManager, Player* player, unsigned int entranceIndex)
{
	m_Player = player;
	m_Transition.Init(textureManager);
	m_Map.load("res/map1.tmx", &textureManager.GetTilesetTexture());
	
	if (entranceIndex == 0)
	{
		m_Player->setCenter({ 32.f, 128.f });
	}
	else
	{
		m_Player->setCenter({ 272.f, 192.f });
	}

	m_Camera.Init(m_Player->getCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(textureManager, { 280.f, 200.f });
	m_Ladder0.SetTeleportLevel(LevelID::Room_Zero);
}

void Hub::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	m_Player->Update({ m_Tree, m_Map, currentState, currentLevel }, dt);
	if (m_Ladder0.contains(m_Player->getCenter()))
		m_Ladder0.Update({ m_Tree, m_Map, currentState, currentLevel }, dt);
	m_Camera.Update(m_Player->getCenter(), dt);
	m_Map.update(dt);
}

void Hub::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);
	m_Player->Render(target);
	m_Map.drawLayer(target, 2);
	m_Transition.Render(target);
}
