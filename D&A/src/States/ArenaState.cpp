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
}

bool ArenaState::OnEnter(float dt)
{
	return false;
}

bool ArenaState::OnExit(float dt)
{
	return false;
}

void ArenaState::Update(StateID& currentState, float dt)
{
}

void ArenaState::Render(sf::RenderTarget& target)
{
}

StateID ArenaState::GetStateID() const
{
	return StateID();
}
