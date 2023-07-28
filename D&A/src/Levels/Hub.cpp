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

void Hub::Init(const ResourceManager& resourceManager, Player* player, unsigned int entranceIndex)
{
	m_Player = player;
	if (entranceIndex == 0)
		m_Player->setCenter({ 224.f, 416.f }); //starting point
	else if (entranceIndex == 1)
		m_Player->setCenter({ 424.f, 440.f }); //from undeground

	m_Hud.Init(resourceManager, m_Player);
	m_Label.Init(resourceManager, "Hub");
	m_Transition.Init(resourceManager);
	m_Map.load("../res/map/hub.tmx", &resourceManager.GetTilesetTexture());
	m_Camera.Init(m_Player->getCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });
	
	m_Ladder0.Init(resourceManager, { 408.f, 440.f });
	m_Ladder0.SetTeleportLevel(LevelID::UnderGround_Zero);

	//TODO Tree;
}

void Hub::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	m_Player->Update({ m_Tree, m_Map, currentState, currentLevel }, dt);
	m_Camera.Update(m_Player->getCenter(), dt);
	m_Map.update(dt);

	if (m_Ladder0.contains(m_Player->getCenter()))
		m_Ladder0.Teleport(currentLevel);

	m_Hud.Update(dt);
	m_Label.Update(dt);
}

void Hub::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);
	m_Player->Render(target);
	m_Map.drawLayer(target, 2);
	m_Hud.Render(target);
	m_Label.Render(target);
	m_Transition.Render(target);
}
