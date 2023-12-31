#include "pch.h"
#include "StateManager.h"

#include "States/BeginState.h"
#include "States/MainTitleState.h"
#include "States/StartMenuState.h"
#include "States/GameState.h"
#include "States/GameOverState.h"
#include "States/ArenaState.h"
#include "States/ExitState.h"
#include "States/OptionsMenuState.h"
#include "States/SelectModeState.h"
#include "States/WinState.h"

void StateManager::Init(const ResourceManager& resourceManager)
{
	m_ResourceManager = &resourceManager;

	m_CurrentState = std::make_unique<BeginState>();
	m_CurrentState->Init(resourceManager);

	m_CurrentStateId = m_CurrentState->GetStateID();
	m_OldStateId = m_CurrentState->GetStateID();

	m_ChangingState = true;
	m_Initialized = false;
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
			case StateID::GameOverState:
				m_CurrentState.reset(new GameOverState());
				break;
			case StateID::ExitState:
				m_CurrentState.reset(new ExitState());
				break;
			case StateID::OptionsMenuState:
				m_CurrentState.reset(new OptionsMenuState());
				break;
			case StateID::WinState:
				m_CurrentState.reset(new WinState());
				break;
			default:
				break;
			}

			m_CurrentState->Init(*m_ResourceManager);
			m_OldStateId = m_CurrentStateId;
			m_Initialized = true;
		}
	}
	else if (m_Initialized)
	{
		m_Initialized = false;
	}
	else if (!m_CurrentState->OnEnter(dt) && m_ChangingState)
	{
		m_ChangingState = false;
	}
}