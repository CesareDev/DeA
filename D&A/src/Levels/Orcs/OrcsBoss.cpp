#include "pch.h"
#include "OrcsBoss.h"

OrcsBoss::OrcsBoss()
{
}

OrcsBoss::~OrcsBoss()
{
}

void OrcsBoss::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Orcs-Boss");
	m_Map.load("../res/map/orcsboss.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 48.f, 64.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 32.f, 64.f });
	m_Ladder0.SetTeleportLevel(LevelID::OrcsTwo, 1);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());

	InitEnemies(resourceManager);
}

LevelID OrcsBoss::GetId() const
{
	return LevelID::OrcsBoss;
}
