#include "pch.h"
#include "Entrance.h"

Entrance::Entrance()
{
}

Entrance::~Entrance()
{
}

bool Entrance::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool Entrance::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void Entrance::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex)
{
	m_Transition.Init(resourceManager);
	m_Label.Init(resourceManager, "Entrance");
	m_Map.load("../res/map/entrance.tmx", &resourceManager.GetTilesetTexture());

	m_Player = &player;

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		m_Player->SetPosition({ 224.f, 432.f }); //starting point

	m_AStar.init(m_Map);
	m_Hud.Init(resourceManager, player, m_Map);
	m_Camera.Init(m_Player->GetCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Tree->insert(m_Player, m_Player->GetBounds());
}

void Entrance::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	for (auto it = m_Tree->begin(); it != m_Tree->end();)
	{
		it->obj->Update({ *m_Tree, m_Map, m_AStar, currentState, currentLevel }, dt);
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

void Entrance::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);

	for (const auto& en : m_Tree->search(m_Camera.GetVisibleArea()))
	{
		en->obj->Render(target);
	}

	m_Map.drawLayer(target, 2);

	m_Player->RenderWeapon(target);

	m_Hud.Render(target);

	m_Label.Render(target);
	m_Transition.Render(target);
}
