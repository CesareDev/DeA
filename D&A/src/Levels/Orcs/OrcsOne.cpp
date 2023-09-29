#include "pch.h"
#include "OrcsOne.h"

OrcsOne::OrcsOne()
{
}

OrcsOne::~OrcsOne()
{
}

void OrcsOne::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Orcs-1");
	m_Map.load("../res/map/orcs1.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 192.f, 224.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 96.f, 400.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 208.f, 224.f });
	m_Ladder0.SetTeleportLevel(LevelID::Entrance, 1);
	m_Ladder1.Init(resourceManager, { 80.f, 400.f });
	m_Ladder1.SetTeleportLevel(LevelID::OrcsTwo, 0);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	InitEnemies(resourceManager);
}

LevelID OrcsOne::GetId() const
{
	return LevelID::OrcsOne;
}
