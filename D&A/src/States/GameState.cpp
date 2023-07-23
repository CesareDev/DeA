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
	if (!m_Pause) {}
		//TODO: Update Level

	if (m_Pause)
	{
		m_PauseMenu.Update(currentState, dt);
		m_PauseMenu.Resume(m_Pause);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !m_EnterPress)
	{
		m_EnterPress = true;
		m_Pause = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !m_Pause)
		m_EnterPress = false;
}

void GameState::Render(sf::RenderTarget& target)
{
	//Render Level

	if (m_Pause)
		m_PauseMenu.Render(target);

	m_Transition.Render(target);
}

StateID GameState::GetStateID() const
{
	return StateID::GameState;
}