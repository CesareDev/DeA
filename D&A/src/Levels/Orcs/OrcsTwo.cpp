#include "pch.h"
#include "OrcsTwo.h"
#include "Entities/Characters/Character.h"

OrcsTwo::OrcsTwo()
{
}

OrcsTwo::~OrcsTwo()
{
}

bool OrcsTwo::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);
}

bool OrcsTwo::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void OrcsTwo::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Orcs-2");
	m_Map.load("../res/map/orcs2.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 416.f, 64.f });
	else if (entranceIndex == 1)
		m_Player->SetPosition({ 16.f, 256.f });

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 432.f, 64.f });
	m_Ladder0.SetTeleportLevel(LevelID::OrcsOne, 1);

	m_Ladder1.Init(resourceManager, { 32.f, 256.f });
	m_Ladder1.SetTeleportLevel(LevelID::OrcsBoss, 0);

	m_SmallOrc0.Init(resourceManager, { 32.f, 192.f });
	m_SmallOrc1.Init(resourceManager, { 192.f, 192.f });
	m_SmallOrc2.Init(resourceManager, { 416.f, 256.f });
	m_Orc0.Init(resourceManager, { 32.f, 144.f });
	m_MaskedOrc0.Init(resourceManager, { 32.f, 48.f });
	m_MaskedOrc1.Init(resourceManager, { 192.f, 64.f });
	m_TribalOrc0.Init(resourceManager, { 160.f, 256.f });
	m_TribalOrc1.Init(resourceManager, { 432.f, 160 });

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());
	m_Tree->insert(&m_Ladder1, m_Ladder1.GetBounds());

	m_Tree->insert(&m_SmallOrc0, m_SmallOrc0.GetBounds());
	m_Tree->insert(&m_SmallOrc1, m_SmallOrc1.GetBounds());
	m_Tree->insert(&m_SmallOrc2, m_SmallOrc2.GetBounds());
	m_Tree->insert(&m_Orc0, m_Orc0.GetBounds());
	m_Tree->insert(&m_MaskedOrc0, m_MaskedOrc0.GetBounds());
	m_Tree->insert(&m_MaskedOrc1, m_MaskedOrc1.GetBounds());
	m_Tree->insert(&m_TribalOrc0, m_TribalOrc0.GetBounds());
	m_Tree->insert(&m_TribalOrc1, m_TribalOrc1.GetBounds());
}

void OrcsTwo::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
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

void OrcsTwo::Render(sf::RenderTarget& target)
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
