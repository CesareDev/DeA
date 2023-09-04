#include "pch.h"
#include "OrchsOne.h"

OrchsOne::OrchsOne()
{
}

OrchsOne::~OrchsOne()
{
}

bool OrchsOne::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool OrchsOne::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void OrchsOne::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Orchs-1");
	m_Map.load("../res/map/orchs1.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 32.f, 16.f }); //starting point
	
	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Ladder0.Init(resourceManager, { 16.f, 16.f });
	m_Ladder0.SetTeleportLevel(LevelID::Entrance, 1);

	m_Tree->insert(m_Player, m_Player->GetBounds());
	m_Tree->insert(&m_Ladder0, m_Ladder0.GetBounds());

}

void OrchsOne::Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt)
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
				if (it->obj->GetId() == EntityID::Player)
					m_Camera.Update(it->obj->GetCenter(), dt);
			}
			break;
		}
		default:
			break;
		}
		++it;
	}

	m_Map.update(dt);
	m_Hud.Update(dt);
	m_Label.Update(dt);
}

void OrchsOne::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);

	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);

	for (const auto& en : m_Tree->search(m_Camera.GetVisibleArea()))
		en->obj->Render(target);

	m_Map.drawLayer(target, 2);

	m_Player->RenderWeapon(target);

	m_Hud.Render(target);
	m_Label.Render(target);
	m_Transition.Render(target);
}
