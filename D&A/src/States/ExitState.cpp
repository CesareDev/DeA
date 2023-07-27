#include "pch.h"
#include "ExitState.h"

ExitState::ExitState()
{
}

ExitState::~ExitState()
{
}

void ExitState::Init(const ResourceManager& resourceManager)
{
}

bool ExitState::OnEnter(float dt)
{
    return false;
}

bool ExitState::OnExit(float dt)
{
    return false;
}

void ExitState::Update(StateID& currentState, float dt)
{
}

void ExitState::Render(sf::RenderTarget& target)
{
    ((sf::RenderWindow&)target).close();
}

StateID ExitState::GetStateID() const
{
    return StateID();
}
