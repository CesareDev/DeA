#include "pch.h"
#include "DemonsThree.h"

DemonsThree::DemonsThree()
{
}

DemonsThree::~DemonsThree()
{
}

void DemonsThree::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Demons-3");
	m_Map.load("../res/map/demons3.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 896.f, 896.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 48.f, 896.f });
	else if (entranceIndex == 2)
		m_Player->SetPosition({ 480.f, 64.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 912.f, 896.f });
	m_Ladder0.SetTeleportLevel(LevelID::DemonsOne, 1);

	m_Ladder1.Init(resourceManager, { 32.f, 896.f });
	m_Ladder1.SetTeleportLevel(LevelID::DemonsTwo, 1);

	m_Ladder2.Init(resourceManager, { 464.f, 64.f });
	m_Ladder2.SetTeleportLevel(LevelID::DemonsBoss, 0);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());
	m_Tree->insert(&m_Ladder2, m_Ladder2.GetBounds());

	InitEnemies(resourceManager);
}

LevelID DemonsThree::GetId() const
{
	return LevelID::DemonsThree;
}
