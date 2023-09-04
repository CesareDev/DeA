#include "pch.h"
#include "LevelManager.h"
#include "Levels/Entrance.h"
#include "Levels/OrchsOne.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init(const ResourceManager& resourceManager)
{
	m_Tree.create(4, {-100.f, -100.f, 200.f, 200.f });
	m_ResourceManager = &resourceManager;

	//SAVE::LEVEL_ID && level->init(entrance index = -1)
	m_EntranceIndex = -1;
	switch (SAVE::LEVEL_ID)
	{
	case LevelID::Null:
	{
		m_CurrentLevel = std::make_unique<Entrance>();
		m_EntranceIndex = 0;
		m_CurrentLevelId = LevelID::Entrance;
		break;
	}
	case LevelID::Entrance:
	{
		m_CurrentLevel = std::make_unique<Entrance>();
		m_CurrentLevelId = LevelID::Entrance;
		break;
	}
	case LevelID::OrchsOne:
	{
		m_CurrentLevel = std::make_unique<OrchsOne>();
		m_CurrentLevelId = LevelID::OrchsOne;
		break;
	}
	default:
		break;
	}

	//SAVE::PLAYER_POS
	if (m_EntranceIndex < 0)
		m_Player.Init(resourceManager, SAVE::PLAYER_POS);
	else
		m_Player.Init(resourceManager, { 0.f, 0.f });
	
	m_CurrentLevel->Init(resourceManager, m_Tree, m_Player, m_EntranceIndex);
	m_OldLevelId = m_CurrentLevelId;
	m_ChangingLevel = true;
	m_Initialized = false; //flag usata per evitare il delay creato dall init del livello che causava un bug nel fade della transazione
}

void LevelManager::Update(StateID& currentState, float dt)
{
	if (!m_ChangingLevel)
	{
		m_OldLevelId = m_CurrentLevelId;

		//Udpate Level
		m_CurrentLevel->Update(currentState, m_CurrentLevelId, m_EntranceIndex, dt);
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
			switch (m_CurrentLevelId)
			{
			case LevelID::Entrance:
			{
				m_CurrentLevel.reset(new Entrance());
				break;
			}
			case LevelID::OrchsOne:
			{
				m_CurrentLevel.reset(new OrchsOne());
				break;
			}
			default:
				break;
			}

			m_CurrentLevel->Init(*m_ResourceManager, m_Tree, m_Player, m_EntranceIndex);
			m_OldLevelId = m_CurrentLevelId;
			m_Initialized = true;
		}
	}
	else if (m_Initialized)
	{
		m_Initialized = false;
	}
	else if (!m_CurrentLevel->OnEnter(dt) && m_ChangingLevel)
	{
		m_ChangingLevel = false;
	}
}