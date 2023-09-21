#include "pch.h"
#include "LevelManager.h"
#include "Levels/Other/Entrance.h"
#include "Levels/Orcs/OrcsOne.h"
#include "Levels/Orcs/OrcsTwo.h"
#include "Levels/Orcs/OrcsBoss.h"
#include "Levels/Undeads/UndeadsOne.h"
#include "Levels/Undeads/UndeadsTwo.h"
#include "Levels/Undeads/UndeadsBoss.h"
#include "Levels/Demons/DemonsOne.h"
#include "Levels/Demons/DemonsTwo.h"
#include "Levels/Demons/DemonsThree.h"
#include "Levels/Demons/DemonsBoss.h"

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
	case LevelID::OrcsOne:
	{
		m_CurrentLevel = std::make_unique<OrcsOne>();
		m_CurrentLevelId = LevelID::OrcsOne;
		break;
	}
	case LevelID::OrcsTwo:
	{
		m_CurrentLevel = std::make_unique<OrcsTwo>();
		m_CurrentLevelId = LevelID::OrcsTwo;
		break;
	}
	case LevelID::OrcsBoss:
	{
		m_CurrentLevel = std::make_unique<OrcsBoss>();
		m_CurrentLevelId = LevelID::OrcsBoss;
		break;
	}
	case LevelID::UndeadsOne:
	{
		m_CurrentLevel = std::make_unique<UndeadsOne>();
		m_CurrentLevelId = LevelID::UndeadsOne;
		break;
	}
	case LevelID::UndeadsTwo:
	{
		m_CurrentLevel = std::make_unique<UndeadsTwo>();
		m_CurrentLevelId = LevelID::UndeadsTwo;
		break;
	}
	case LevelID::UndeadsBoss:
	{
		m_CurrentLevel = std::make_unique<UndeadsBoss>();
		m_CurrentLevelId = LevelID::UndeadsBoss;
		break;
	}
	case LevelID::DemonsOne:
	{
		m_CurrentLevel = std::make_unique<DemonsOne>();
		m_CurrentLevelId = LevelID::DemonsOne;
		break;
	}
	case LevelID::DemonsTwo:
	{
		m_CurrentLevel = std::make_unique<DemonsTwo>();
		m_CurrentLevelId = LevelID::DemonsTwo;
		break;
	}
	case LevelID::DemonsThree:
	{
		m_CurrentLevel = std::make_unique<DemonsThree>();
		m_CurrentLevelId = LevelID::DemonsThree;
		break;
	}
	case LevelID::DemonsBoss:
	{
		m_CurrentLevel = std::make_unique<DemonsBoss>();
		m_CurrentLevelId = LevelID::DemonsBoss;
		break;
	}
	default:
	{
		m_CurrentLevel = std::make_unique<Entrance>();
		m_EntranceIndex = 0;
		m_CurrentLevelId = LevelID::Entrance;
		break;
	}
	}

	//SAVE::PLAYER_POS
	if (m_EntranceIndex < 0)
		m_Player.Init(resourceManager, SAVE::PLAYER_POS);
	else
		m_Player.Init(resourceManager, { 0.f, 0.f });
	
	m_CurrentLevel->Init(resourceManager, m_Tree, m_Player, m_EntranceIndex);
	m_OldLevelId = m_CurrentLevelId;
	m_ChangingLevel = true;
	m_Initialized = false; //flag usata per evitare il delay creato dall'init del livello che causava un bug nel fade della transazione
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
			m_CurrentLevel->DeleteCoins(); //Because Coin are allocated on the heap

			switch (m_CurrentLevelId)
			{
			case LevelID::Entrance:
			{
				m_CurrentLevel.reset(new Entrance());
				break;
			}
			case LevelID::OrcsOne:
			{
				m_CurrentLevel.reset(new OrcsOne());
				break;
			}
			case LevelID::OrcsTwo:
			{
				m_CurrentLevel.reset(new OrcsTwo());
				break;
			}
			case LevelID::OrcsBoss:
			{
				m_CurrentLevel.reset(new OrcsBoss());
				break;
			}
			case LevelID::UndeadsOne:
			{
				m_CurrentLevel.reset(new UndeadsOne());
				break;
			}
			case LevelID::UndeadsTwo:
			{
				m_CurrentLevel.reset(new UndeadsTwo());
				break;
			}
			case LevelID::UndeadsBoss:
			{
				m_CurrentLevel.reset(new UndeadsBoss());
				break;
			}
			case LevelID::DemonsOne:
			{
				m_CurrentLevel.reset(new DemonsOne());
				break;
			}
			case LevelID::DemonsTwo:
			{
				m_CurrentLevel.reset(new DemonsTwo());
				break;
			}
			case LevelID::DemonsThree:
			{
				m_CurrentLevel.reset(new DemonsThree());
				break;
			}
			case LevelID::DemonsBoss:
			{
				m_CurrentLevel.reset(new DemonsBoss());
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