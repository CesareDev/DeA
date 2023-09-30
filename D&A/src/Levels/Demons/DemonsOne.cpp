#include "pch.h"
#include "DemonsOne.h"

DemonsOne::DemonsOne()
{
}

DemonsOne::~DemonsOne()
{
}

void DemonsOne::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, CONFIG::LEVELS_INFO[GetId()].name);
	m_Map.load(CONFIG::LEVELS_INFO[GetId()].dir, &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 320.f, 560.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 320.f, 64.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 304.f, 560.f });
	m_Ladder0.SetTeleportLevel(LevelID::Entrance, 3);
	m_Ladder1.Init(resourceManager, { 304.f, 64.f });
	m_Ladder1.SetTeleportLevel(LevelID::DemonsThree, 0);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	InitEnemies(resourceManager);
}

LevelID DemonsOne::GetId() const
{
	return LevelID::DemonsOne;
}
