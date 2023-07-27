#include "pch.h"
#include "BeginState.h"

BeginState::BeginState()
	: State()
{
}

BeginState::~BeginState()
{
}

void BeginState::Init(const ResourceManager& resourceManager)
{
}

bool BeginState::OnEnter(float dt)
{
	return false;
}

bool BeginState::OnExit(float dt)
{
	return false;
}

void BeginState::Update(StateID& currentState, float dt)
{
	currentState = StateID::MainTitleState;
}

void BeginState::Render(sf::RenderTarget& target)
{
}

StateID BeginState::GetStateID() const
{
	return StateID::BeginState;
}