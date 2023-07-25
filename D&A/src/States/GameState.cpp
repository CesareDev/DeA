#include "pch.h"
#include "GameState.h"

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
}

void GameState::Init(const TextureManager& textureManger)
{
	m_PauseMenu.Init(textureManger);
	m_Transition.Init(textureManger);
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
}

void GameState::Render(sf::RenderTarget& target)
{
	//Render Level

	m_Transition.Render(target);
}

StateID GameState::GetStateID() const
{
	return StateID::GameState;
}