#include "pch.h"
#include "UndeadsOne.h"

UndeadsOne::UndeadsOne()
{
}

UndeadsOne::~UndeadsOne()
{
}

void UndeadsOne::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Undeads-1");
	m_Map.load("../res/map/undeads1.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 48.f, 224.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 144.f, 400.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 32.f, 224.f });
	m_Ladder0.SetTeleportLevel(LevelID::Entrance, 4);
	m_Ladder1.Init(resourceManager, { 160.f, 400.f });
	m_Ladder1.SetTeleportLevel(LevelID::UndeadsTwo, 0);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	InitEnemies(resourceManager);
}

LevelID UndeadsOne::GetId() const
{
	return LevelID::UndeadsOne;
}
