#include "pch.h"
#include "DemonsThree.h"

DemonsThree::DemonsThree()
{
}

DemonsThree::~DemonsThree()
{
}

bool DemonsThree::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool DemonsThree::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
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

	m_HalfDemons[0].Init(resourceManager, { 352.f, 896.f });
	m_HalfDemons[1].Init(resourceManager, { 592.f, 896.f });
	m_HalfDemons[2].Init(resourceManager, { 336.f, 784.f });
	m_HalfDemons[3].Init(resourceManager, { 608.f, 784.f });
	m_Demons[0].Init(resourceManager, { 128.f, 896.f });
	m_Demons[1].Init(resourceManager, { 224.f, 896.f });
	m_Demons[2].Init(resourceManager, { 816.f, 896.f });
	m_Demons[3].Init(resourceManager, { 720.f, 896.f });
	m_Demons[4].Init(resourceManager, { 192.f, 704.f });
	m_Demons[5].Init(resourceManager, { 752.f, 704.f });
	m_Demons[6].Init(resourceManager, { 352.f, 496.f });
	m_Demons[7].Init(resourceManager, { 592.f, 528.f });
	m_Demons[8].Init(resourceManager, { 48.f, 368.f });
	m_Demons[9].Init(resourceManager, { 192.f, 240.f });
	m_Demons[10].Init(resourceManager, { 896.f, 368.f });
	m_Demons[11].Init(resourceManager, { 752.f, 240.f });
	m_MagicDemons[0].Init(resourceManager, { 464.f, 768.f });
	m_MagicDemons[1].Init(resourceManager, { 64.f, 640.f });
	m_MagicDemons[2].Init(resourceManager, { 848.f, 640.f });
	m_MagicDemons[3].Init(resourceManager, { 336.f, 608.f });
	m_MagicDemons[4].Init(resourceManager, { 592.f, 592.f });
	m_MagicDemons[5].Init(resourceManager, { 592.f, 384.f });
	m_MagicDemons[6].Init(resourceManager, { 400.f, 352.f });
	m_MagicDemons[7].Init(resourceManager, { 720.f, 480.f });
	m_MagicDemons[8].Init(resourceManager, { 224.f, 480.f });
	m_MagicDemons[9].Init(resourceManager, { 480.f, 256.f });
	m_MagicDemons[10].Init(resourceManager, { 369.f, 144.f });
	m_MagicDemons[11].Init(resourceManager, { 576.f, 144.f });

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());
	m_Tree->insert(&m_Ladder2, m_Ladder2.GetBounds());


	for (auto& hd : m_HalfDemons)
		m_Tree->insert(&hd, hd.GetBounds());

	for (auto& d : m_Demons)
		m_Tree->insert(&d, d.GetBounds());

	for (auto& md : m_MagicDemons)
		m_Tree->insert(&md, md.GetBounds());
}

void DemonsThree::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
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

void DemonsThree::Render(sf::RenderTarget& target)
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
