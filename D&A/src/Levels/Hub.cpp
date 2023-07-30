#include "pch.h"
#include "Hub.h"

Hub::Hub()
{
}

Hub::~Hub()
{
}

bool Hub::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool Hub::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void Hub::Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex)
{
	m_Label.Init(resourceManager, "Hub");
	m_Transition.Init(resourceManager);
	m_Map.load("../res/map/hub.tmx", &resourceManager.GetTilesetTexture());

	m_Tree = &tree;
	m_Tree->resize({ 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y });

	if (entranceIndex == 0)
		player.setCenter({ 224.f, 416.f }); //starting point
	else if (entranceIndex == 1)
		player.setCenter({ 424.f, 440.f }); //from undeground

	m_Camera.Init(player.getCenter(), { 0.f, 0.f, (float)m_Map.getMapSize().x, (float)m_Map.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });
	m_Tree->insert(&player, player.getGlobalBounds());
	
	m_Ladder0.Init(resourceManager, { 408.f, 440.f });
	m_Ladder0.SetTeleportLevel(LevelID::UnderGround_Zero);

	m_Tree->insert(&m_Ladder0, m_Ladder0.getGlobalBounds());
}

void Hub::Update(StateID& currentState, LevelID& currentLevel, float dt)
{
	for (auto it = m_Tree->begin(); it != m_Tree->end();)
	{
		it->obj->Update({ *m_Tree, m_Map, currentState, currentLevel }, dt);
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
						m_Tree->relocate(it, it->obj->getGlobalBounds());
					if (it->obj->GetId() == EntityID::Player)
						m_Camera.Update(it->obj->getCenter(), dt);
				}
				break;
			}
			case EntityType::Weapon:
			{
				break;
			}
			case EntityType::Environment:
			{
				break;
			}
			default:
				break;
		}
		++it;
	}

	m_Map.update(dt);
	m_Label.Update(dt);
}

void Hub::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Map.drawLayer(target, 0);
	m_Map.drawLayer(target, 1);

	for (const auto& en : m_Tree->search(m_Camera.GetVisibleArea()))
	{
		en->obj->Render(target);
	}

	m_Map.drawLayer(target, 2);
	m_Label.Render(target);
	m_Transition.Render(target);
}
