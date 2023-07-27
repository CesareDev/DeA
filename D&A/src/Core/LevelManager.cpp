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

void LevelManager::Init(const TextureManager& textureManager)
{
	m_Player.Init(textureManager, { 0.f, 0.f });
	m_TextureManager = &textureManager;

	m_CurrentLevel = std::make_unique<Hub>();
	m_CurrentLevel->Init(textureManager, &m_Player, 0);

	m_ChangingLevel = true;
}

void LevelManager::Update(StateID& currentState, float dt)
{
	if (!m_ChangingLevel)
	{
		m_OldState = m_CurrentLevelId;

		//Udpate State
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
	if (m_CurrentLevelId != m_OldState)
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

			m_CurrentLevel->Init(*m_TextureManager, &m_Player, entanceIndex);
			m_OldState = m_CurrentLevelId;
		}
	}
	else if (!m_CurrentLevel->OnEnter(dt))
	{
		m_ChangingLevel = false;
	}
}
