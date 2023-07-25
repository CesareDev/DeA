#include "pch.h"
#include "ArenaState.h"

ArenaState::ArenaState()
{
}

ArenaState::~ArenaState()
{
}

void ArenaState::Init(const TextureManager& textureManger)
{
	m_Transition.Init(textureManger);
	m_PauseMenu.Init(textureManger);

	m_Arena.load("res/arena.tmx", &textureManger.GetTilesetTexture());
	m_Tree.create(4, { 0.f, 0.f, (float)m_Arena.getMapSize().x, (float)m_Arena.getMapSize().y });
	m_Player = new Player();
	m_Player->Init(textureManger, { m_Arena.getMapSize().x / 2.f, m_Arena.getMapSize().y / 2.f });
	m_Camera.Init(m_Player->getCenter(), { 0.f, 0.f, (float)m_Arena.getMapSize().x, (float)m_Arena.getMapSize().y }, { 0.f, 0.f, WIN_WIDTH / 4.f, WIN_HEIGHT / 4.f });

	m_Tree.insert(m_Player, m_Player->getGlobalBounds());
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
		m_Arena.update(dt);
		for (auto it = m_Tree.begin(); it != m_Tree.end(); ++it)
		{
			it->obj->Update({ m_Tree, m_Arena, currentState }, dt);
			m_Tree.relocate(it, it->obj->getGlobalBounds());
		}
		m_Camera.Update(m_Player->getCenter(), dt);
	}
}

void ArenaState::Render(sf::RenderTarget& target)
{
	target.setView(m_Camera);
	m_Arena.drawLayer(target, 0);
	m_Arena.drawLayer(target, 1);
	for (auto& entity : m_Tree.search(m_Camera.GetVisibleArea()))
	{
		entity->obj->Render(target);
	}
	m_Arena.drawLayer(target, 2);

	m_PauseMenu.Render(target);

	m_Transition.Render(target);
}

StateID ArenaState::GetStateID() const
{
	return StateID::ArenaState;
}
