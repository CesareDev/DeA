#include "pch.h"
#include "OptionsMenuState.h"

OptionsMenuState::OptionsMenuState()
{
}

OptionsMenuState::~OptionsMenuState()
{
}

void OptionsMenuState::Init(const ResourceManager& resourceManager)
{
	m_Menu.Init(resourceManager);
	m_Transition.Init(resourceManager);
}

bool OptionsMenuState::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt, 0.5f);
}

bool OptionsMenuState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt, 0.5f);
}

void OptionsMenuState::Update(StateID& currentState, float dt)
{
	m_Menu.Update(currentState, dt);
}

void OptionsMenuState::Render(sf::RenderTarget& target)
{
	m_Menu.Render(target);
	m_Transition.Render(target);
}

StateID OptionsMenuState::GetStateID() const
{
	return StateID::OptionsMenuState;
}
