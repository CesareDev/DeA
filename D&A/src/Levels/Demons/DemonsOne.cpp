#include "pch.h"
#include "DemonsOne.h"

DemonsOne::DemonsOne()
{
}

DemonsOne::~DemonsOne()
{
}

bool DemonsOne::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool DemonsOne::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void DemonsOne::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Demons-1");
	m_Map.load("../res/map/demons1.tmx", &resourceManager.GetTilesetTexture());

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

	m_SmallDemons[0].Init(resourceManager, { 32.f, 560.f });
	m_SmallDemons[1].Init(resourceManager, { 192.f, 560.f });
	m_SmallDemons[2].Init(resourceManager, { 48.f, 400.f });
	m_SmallDemons[3].Init(resourceManager, { 416.f, 560.f });
	m_SmallDemons[4].Init(resourceManager, { 496.f, 496.f });
	m_SmallDemons[5].Init(resourceManager, { 400.f, 400.f  });
	m_SmallDemons[6].Init(resourceManager, { 304.f, 272.f });
	m_SmallDemons[7].Init(resourceManager, { 320.f, 144.f });
	m_HalfDemons[0].Init(resourceManager, { 96.f, 480 });
	m_HalfDemons[1].Init(resourceManager, { 192.f, 416.f });
	m_HalfDemons[2].Init(resourceManager, { 576.f, 528.f });
	m_HalfDemons[3].Init(resourceManager, { 576.f, 400.f });
	m_HalfDemons[4].Init(resourceManager, { 304.f, 368.f });
	m_HalfDemons[5].Init(resourceManager, { 480.f, 224.f });
	m_HalfDemons[6].Init(resourceManager, { 432.f, 128.f });
	m_HalfDemons[7].Init(resourceManager, { 528.f, 64.f });
	m_HalfDemons[8].Init(resourceManager, { 32.f, 160.f });
	m_HalfDemons[9].Init(resourceManager, { 48.f, 48.f });

	m_Demon0.Init(resourceManager, { 80.f, 224.f });
	m_Demon1.Init(resourceManager, { 192.f, 192.f });
	m_Demon2.Init(resourceManager, { 560.f, 160.f });

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	for (auto& sd : m_SmallDemons)
		m_Tree->insert(&sd, sd.GetBounds());

	for (auto& hd : m_HalfDemons)
		m_Tree->insert(&hd, hd.GetBounds());

	m_Tree->insert(&m_Demon0, m_Demon0.GetBounds());
	m_Tree->insert(&m_Demon1, m_Demon1.GetBounds());
	m_Tree->insert(&m_Demon2, m_Demon2.GetBounds());
}

void DemonsOne::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
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

void DemonsOne::Render(sf::RenderTarget& target)
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
