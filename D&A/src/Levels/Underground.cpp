#include "pch.h"
#include "Underground.h"

Underground::Underground()
{
}

Underground::~Underground()
{
}

bool Underground::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);
}

bool Underground::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void Underground::Init(const TextureManager& textureManager, Player* player, unsigned int entranceIndex)
{
	m_Player = player;
	if (entranceIndex == 0)
		m_Player->setCenter({ 56.f, 56.f }); //from hub

	m_Transition.Init(textureManager);
	m_Map.load("../res/map/underground.tmx", &textureManager.GetTilesetTexture());
	m_Camera.Init(m_Player->getCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(textureManager, { 40.f, 56.f });
	m_Ladder0.SetTeleportLevel(LevelID::Hub_Zero);

	//TODO Tree;
}

void Underground::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	m_Player->Update({ m_Tree, m_Map, currentState, currentLevel }, dt);
	m_Camera.Update(m_Player->getCenter(), dt);
	m_Map.update(dt);

	if (m_Ladder0.contains(m_Player->getCenter()))
		m_Ladder0.Teleport(currentLevel);
}

void Underground::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);
	m_Player->Render(target);
	m_Map.drawLayer(target, 2);
	m_Transition.Render(target);
}
