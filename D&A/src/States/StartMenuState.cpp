#include "pch.h"
#include "StartMenuState.h"

StartMenuState::StartMenuState()
{
}

StartMenuState::~StartMenuState()
{
}

void StartMenuState::Init(const TextureManager& textureManger)
{
	m_StartMenu.Init(textureManger);
	m_Transition.Init(textureManger);
}

bool StartMenuState::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool StartMenuState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void StartMenuState::Update(StateID& currentState, float dt)
{
	m_StartMenu.Update(currentState, dt);
}

void StartMenuState::Render(sf::RenderTarget& target)
{
	m_StartMenu.Render(target);
	m_Transition.Render(target);
}

StateID StartMenuState::GetStateID() const
{
	return StateID::StartMenuState;
}
