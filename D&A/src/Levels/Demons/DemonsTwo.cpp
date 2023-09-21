#include "pch.h"
#include "DemonsTwo.h"

DemonsTwo::DemonsTwo()
{
}

DemonsTwo::~DemonsTwo()
{
}

bool DemonsTwo::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);
}

bool DemonsTwo::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void DemonsTwo::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Demons-2");
	m_Map.load("../res/map/demons2.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 576.f, 576.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 576.f, 48.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 592.f, 576.f });
	m_Ladder0.SetTeleportLevel(LevelID::Entrance, 2);
	m_Ladder1.Init(resourceManager, { 592.f, 48.f });
	m_Ladder1.SetTeleportLevel(LevelID::DemonsThree, 1);

	m_SmallDemons[0].Init(resourceManager, { 432.f, 576.f });
	m_SmallDemons[1].Init(resourceManager, { 512.f, 480.f });
	m_SmallDemons[2].Init(resourceManager, { 256.f, 576.f });
	m_SmallDemons[3].Init(resourceManager, { 336.f, 336.f });
	m_SmallDemons[4].Init(resourceManager, { 352.f, 128.f });
	m_SmallDemons[5].Init(resourceManager, { 80.f, 352.f });
	m_SmallDemons[6].Init(resourceManager, { 16.f, 128.f });
	m_SmallDemons[7].Init(resourceManager, { 464.f, 32.f });
	m_HalfDemons[0].Init(resourceManager, { 384.f, 480.f });
	m_HalfDemons[1].Init(resourceManager, { 256.f, 448.f });
	m_HalfDemons[2].Init(resourceManager, { 32.f, 512.f });
	m_HalfDemons[3].Init(resourceManager, { 32.f, 288.f });
	m_HalfDemons[4].Init(resourceManager, { 80.f, 192.f });
	m_HalfDemons[5].Init(resourceManager, { 224.f, 144.f });
	m_HalfDemons[6].Init(resourceManager, { 464.f, 368.f });
	m_HalfDemons[7].Init(resourceManager, { 528.f, 384.f });
	m_HalfDemons[8].Init(resourceManager, { 560.f, 144.f });
	m_Demons[0].Init(resourceManager, { 144.f, 448.f });
	m_Demons[1].Init(resourceManager, { 128.f, 576.f });
	m_Demons[2].Init(resourceManager, { 464.f, 272.f });
	m_Demons[3].Init(resourceManager, { 560.f, 256.f });
	m_Demons[4].Init(resourceManager, { 464.f, 176.f });
	m_Demons[5].Init(resourceManager, { 32.f, 592.f });
	m_Demons[6].Init(resourceManager, { 128.f, 48.f });
	m_Demons[7].Init(resourceManager, { 256.f, 48.f });
	m_Demons[8].Init(resourceManager, { 208.f, 272.f });

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	for (auto& sd : m_SmallDemons)
		m_Tree->insert(&sd, sd.GetBounds());

	for (auto& hd : m_HalfDemons)
		m_Tree->insert(&hd, hd.GetBounds());

	for (auto& d : m_Demons)
		m_Tree->insert(&d, d.GetBounds());
}

void DemonsTwo::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
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

void DemonsTwo::Render(sf::RenderTarget& target)
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
