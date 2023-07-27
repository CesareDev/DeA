#include "pch.h"
#include "SelectModeState.h"

SelectModeState::SelectModeState()
{
}

SelectModeState::~SelectModeState()
{
}

void SelectModeState::Init(const ResourceManager& resourceManager)
{
    m_Menu.Init(resourceManager);
    m_Transition.Init(resourceManager);
}

bool SelectModeState::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 0.5f);
}

bool SelectModeState::OnExit(float dt)
{
    return m_Transition.FadeOut(dt, 0.5f);
}

void SelectModeState::Update(StateID& currentState, float dt)
{
    m_Menu.Update(currentState, dt);
}

void SelectModeState::Render(sf::RenderTarget& target)
{
    m_Menu.Render(target);
    m_Transition.Render(target);
}

StateID SelectModeState::GetStateID() const
{
    return StateID::SelectModeState;
}
