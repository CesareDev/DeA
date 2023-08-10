#include "pch.h"
#include "StateManager.h"

#include "States/BeginState.h"
#include "States/MainTitleState.h"
#include "States/StartMenuState.h"
#include "States/GameState.h"
#include "States/ArenaState.h"
#include "States/ExitState.h"
#include "States/OptionsMenuState.h"
#include "States/SelectModeState.h"

void StateManager::Init(const ResourceManager& resourceManager)
{
	m_ResourceManager = &resourceManager;
#if DEBUG
	m_CurrentState = std::make_unique<GameState>();
	m_CurrentStateId = StateID::GameState;
	m_OldStateId = StateID::GameState;
#else
	m_CurrentState = std::make_unique<BeginState>();
	m_CurrentStateId = StateID::BeginState;
	m_OldStateId = StateID::BeginState;
#endif // DEBUG

	m_CurrentState->Init(resourceManager);
	m_ChangingState = true;
}

void StateManager::Update(float dt)
{
	if (!m_ChangingState)
	{
		m_OldStateId = m_CurrentStateId;
		
		//Udpate State
		m_CurrentState->Update(m_CurrentStateId, dt);
	}

	ChangeState(dt);
}

void StateManager::Render(sf::RenderTarget& target)
{
	//Render State
	m_CurrentState->Render(target);
}

StateID StateManager::GetCurrentState() const
{
	return m_CurrentStateId;
}

void StateManager::ChangeState(float dt)
{
	if (m_CurrentStateId != m_OldStateId)
	{
		m_ChangingState = true;

		if (!m_CurrentState->OnExit(dt))
		{
			switch (m_CurrentStateId)
			{
			case StateID::BeginState:
				m_CurrentState.reset(new BeginState());
				break;
			case StateID::MainTitleState:
				m_CurrentState.reset(new MainTitleState());
				break;
			case StateID::StartMenuState:
				m_CurrentState.reset(new StartMenuState());
				break;
			case StateID::SelectModeState:
				m_CurrentState.reset(new SelectModeState());
				break;
			case StateID::GameState:
				m_CurrentState.reset(new GameState());
				break;
			case StateID::ArenaState:
				m_CurrentState.reset(new ArenaState());
				break;
			case StateID::ExitState:
				m_CurrentState.reset(new ExitState());
				break;
			case StateID::OptionsMenu:
				m_CurrentState.reset(new OptionsMenuState());
				break;
			default:
				break;
			}

			m_CurrentState->Init(*m_ResourceManager);
			m_OldStateId = m_CurrentStateId;
		}
	}
	else if (!m_CurrentState->OnEnter(dt))
	{
		m_ChangingState = false;
	}
}