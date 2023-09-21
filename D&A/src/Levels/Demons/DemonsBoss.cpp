#include "pch.h"
#include "DemonsBoss.h"

DemonsBoss::DemonsBoss()
{
}

DemonsBoss::~DemonsBoss()
{
}

bool DemonsBoss::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);;
}

bool DemonsBoss::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
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

	if (!SAVE::DEMON_BOSS_DEFEATED)
	{
		m_DemonBoss.Init(resourceManager, { 224.f, 224.f });
		m_Tree->insert(&m_DemonBoss, m_DemonBoss.GetBounds());
	}

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
}

void DemonsBoss::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
{
	for (auto it = m_Tree->begin(); it != m_Tree->end();)
	{
		it->obj->Update({ *m_Tree, m_Map, m_AStar, currentState, currentLevel, entranceIndex }, dt);
		switch (it->obj->GetType())
		{
		case EntityType::Character:
		{
			if (((Character*)it->obj)->IsDead())
			{
				it = m_Tree->remove(it);
				continue;
			}
			else
			{
				if (((Character*)it->obj)->IsMoving())
					m_Tree->relocate(it, it->obj->GetBounds());
			}
			break;
		}
		default:
			break;
		}
		++it;
	}

	m_Camera.Update(m_Player->GetCenter(), dt);
	m_Map.update(dt);
	m_Hud.Update(dt);
	m_Label.Update(dt);
}

void DemonsBoss::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);

	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);

	const auto& list = m_Tree->search(m_Camera.GetVisibleArea());

	for (const auto& en : list)
		en->obj->Render(target);

	m_Map.drawLayer(target, 2);

	for (const auto& en : list)
		if (en->obj->GetType() == EntityType::Character)
			((Character*)en->obj)->RenderWeapon(target);

	m_Hud.Render(target);
	m_Label.Render(target);
	m_Transition.Render(target);
}
