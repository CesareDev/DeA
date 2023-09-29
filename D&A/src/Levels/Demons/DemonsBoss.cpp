#include "pch.h"
#include "DemonsBoss.h"

DemonsBoss::DemonsBoss()
{
}

DemonsBoss::~DemonsBoss()
{
}

void DemonsBoss::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Demons-Boss");
	m_Map.load("../res/map/demonsboss.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 224.f, 416.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 208.f, 416.f });
	m_Ladder0.SetTeleportLevel(LevelID::DemonsThree, 2);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());

	InitEnemies(resourceManager);
}

LevelID DemonsBoss::GetId() const
{
	return LevelID::DemonsBoss;
}
