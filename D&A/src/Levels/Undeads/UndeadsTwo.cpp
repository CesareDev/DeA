#include "pch.h"
#include "UndeadsTwo.h"

UndeadsTwo::UndeadsTwo()
{
}

UndeadsTwo::~UndeadsTwo()
{
}

void UndeadsTwo::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Undeads-2");
	m_Map.load("../res/map/undeads2.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 48.f, 64.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 448.f, 256.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 32.f, 64.f });
	m_Ladder0.SetTeleportLevel(LevelID::UndeadsOne, 1);

	m_Ladder1.Init(resourceManager, { 432.f, 256.f });
	m_Ladder1.SetTeleportLevel(LevelID::UndeadsBoss, 0);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	InitEnemies(resourceManager);
}

LevelID UndeadsTwo::GetId() const
{
	return LevelID::UndeadsTwo;
}
