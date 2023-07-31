#include "pch.h"
#include "LevelManager.h"
#include "Levels/Hub.h"
#include "Levels/Underground.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init(const ResourceManager& resourceManager)
{
	m_Player.Init(resourceManager, { 0.f, 0.f });
	m_Tree.create(4, {-100.f, -100.f, 200.f, 200.f });
	m_ResourceManager = &resourceManager;

	m_CurrentLevel = std::make_unique<Hub>();
	m_CurrentLevel->Init(resourceManager, m_Tree, m_Player, 0);
	m_OldLevelId = LevelID::Hub_Starting;
	m_CurrentLevelId = LevelID::Hub_Starting;
	m_ChangingLevel = true;
}

void LevelManager::Update(StateID& currentState, float dt)
{
	if (!m_ChangingLevel)
	{
		m_OldLevelId = m_CurrentLevelId;

		//Udpate Level
		m_CurrentLevel->Update(currentState, m_CurrentLevelId, dt);
	}

	ChangeLevel(dt);
}

void LevelManager::Render(sf::RenderTarget& target)
{
	m_CurrentLevel->Render(target);
}

bool LevelManager::IsChanging()
{
	return m_ChangingLevel;
}

void LevelManager::ChangeLevel(float dt)
{
	if (m_CurrentLevelId != m_OldLevelId)
	{
		m_ChangingLevel = true;

		if (!m_CurrentLevel->OnExit(dt))
		{
			unsigned int entanceIndex = 0;
			switch (m_CurrentLevelId)
			{
				case LevelID::Hub_Starting:
				{
					m_CurrentLevel.reset(new Hub());
					entanceIndex = 0;
					break;
				}
				case LevelID::Hub_Zero:
				{
					m_CurrentLevel.reset(new Hub());
					entanceIndex = 1;
					break;
				}
				case LevelID::UnderGround_Zero:
				{
					m_CurrentLevel.reset(new Underground());
					entanceIndex = 0;
					break;
				}
				default:
					break;
			}

			m_CurrentLevel->Init(*m_ResourceManager, m_Tree, m_Player, entanceIndex);
			m_OldLevelId = m_CurrentLevelId;
		}
	}
	else if (!m_CurrentLevel->OnEnter(dt))
	{
		m_ChangingLevel = false;
	}
}
