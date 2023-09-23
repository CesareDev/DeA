#include "pch.h"
#include "ArenaState.h"

ArenaState::ArenaState()
{
}

ArenaState::~ArenaState()
{
	for (auto& c : m_Tree)
		if (c.obj->GetId() != EntityID::Player)
			delete c.obj;
}

void ArenaState::Init(const ResourceManager& resourceManager)
{
	m_Transition.Init(resourceManager);
	m_PauseMenu.Init(resourceManager);

	m_Arena.load("../res/map/arena.tmx", &resourceManager.GetTilesetTexture());
	m_AStar.init(m_Arena);
	m_Tree.create(4, { 0.f, 0.f, (float)m_Arena.getMapSize().x, (float)m_Arena.getMapSize().y });
	m_Player.Init(resourceManager, { m_Arena.getMapSize().x / 2.f, m_Arena.getMapSize().y / 2.f });
	m_Camera.Init(m_Player.GetCenter(), { 0.f, 0.f, (float)m_Arena.getMapSize().x, (float)m_Arena.getMapSize().y }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 4.f, GLOBAL::WIN_HEIGHT / 4.f });
	m_Hud.Init(resourceManager, m_Player, m_Arena);
	m_Spawner.Init(resourceManager, 160.f, 192.f);

	m_Tree.insert(&m_Player, m_Player.getGlobalBounds());
}

bool ArenaState::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt);
}

bool ArenaState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt);
}

void ArenaState::Update(StateID& currentState, float dt)
{
	m_PauseMenu.Update(currentState, dt);
	if (!m_PauseMenu.IsPaused())
	{	
		m_Spawner.Update(m_Tree, m_Arena, m_Player.GetCenter(), dt);
		
		auto l = LevelID::Arena;
		int e = 0;
		for (auto it = m_Tree.begin(); it != m_Tree.end();)
		{
			it->obj->Update({ m_Tree, m_Arena, m_AStar, currentState, l, e}, dt);
			switch (it->obj->GetType())
			{
			case EntityType::Character:
			{
				if (((Character*)it->obj)->IsDead())
				{
					it = m_Tree.remove(it);
					continue;
				}
				else
				{
					if (((Character*)it->obj)->IsMoving())
						m_Tree.relocate(it, it->obj->GetBounds());
				}
				break;
			}
			default:
				break;
			}
			++it;
		}
		m_Hud.Update(dt);
		m_Arena.update(dt);
		m_Camera.Update(m_Player.GetCenter(), dt);
	}
}

void ArenaState::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);

	m_Arena.drawLayer(target, 0);
	m_Arena.drawLayer(target, 1);

	const auto& list = m_Tree.search(m_Camera.GetVisibleArea());

	for (const auto& en : list)
		en->obj->Render(target);

	m_Arena.drawLayer(target, 2);

	for (const auto& en : list)
		if (en->obj->GetType() == EntityType::Character)
			((Character*)en->obj)->RenderWeapon(target);

	m_Hud.Render(target);
	m_PauseMenu.Render(target);
	m_Transition.Render(target);
}

StateID ArenaState::GetStateID() const
{
	return StateID::ArenaState;
}
