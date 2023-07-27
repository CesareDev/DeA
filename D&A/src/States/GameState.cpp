#include "pch.h"
#include "GameState.h"

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
}

void GameState::Init(const ResourceManager& resourceManager)
{
	m_LevelManager.Init(resourceManager);
	m_PauseMenu.Init(resourceManager);
	m_Transition.Init(resourceManager);
}

bool GameState::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt);
}

bool GameState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt);
}

void GameState::Update(StateID& currentState, float dt)
{
	if (!m_LevelManager.IsChanging())
	{
		m_PauseMenu.Update(currentState, dt);
	}
	if (!m_PauseMenu.IsPaused())
	{
		m_LevelManager.Update(currentState, dt);
	}
}

void GameState::Render(sf::RenderTarget& target)
{
	//Render Level
	m_LevelManager.Render(target);
	m_PauseMenu.Render(target);
	m_Transition.Render(target);
}

StateID GameState::GetStateID() const
{
	return StateID::GameState;
}