#include "pch.h"
#include "SaveManager.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <fstream>
#include <sstream>

using namespace rapidjson;

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
}

void SaveManager::Save()
{
	if (m_SaveIndex >= 0)
	{
		Document document;
		document.SetObject();

		auto& allocator = document.GetAllocator();

		Value playerPos(kObjectType);
		playerPos.AddMember("x", SAVE::PLAYER_POS.x, allocator);
		playerPos.AddMember("y", SAVE::PLAYER_POS.y, allocator);

		Value health(SAVE::PLAYER_HEALTH);
		Value coin(SAVE::COIN_NUMBER);
		Value levelId((unsigned int)SAVE::LEVEL_ID);
		Value weaponArray(kArrayType);

		Value orcBoss(SAVE::ORC_BOSS_DEFEATED);
		Value undeadBoss(SAVE::UNDEAD_BOSS_DEFEATED);
		Value demonBoss(SAVE::DEMON_BOSS_DEFEATED);

		for (int i = 0; i < 8; ++i)
		{
			weaponArray.PushBack((unsigned int)SAVE::WEAPON[i], allocator);
		}

		document.AddMember("pos", playerPos, allocator);
		document.AddMember("health", health, allocator);
		document.AddMember("coin", coin, allocator);
		document.AddMember("level", levelId, allocator);
		document.AddMember("weapons", weaponArray, allocator);

		document.AddMember("orcBoss", orcBoss, allocator);
		document.AddMember("undeadBoss", undeadBoss, allocator);
		document.AddMember("demonBoss", demonBoss, allocator);

		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		document.Accept(writer);

		const char* json = buffer.GetString();
		std::string path = "..\\res\\saves\\save_" + std::to_string(m_SaveIndex) + ".json";
		std::ofstream os;
		os.open(path);
		if (os.is_open())
		{
			os << json;
		}
		os.close();
	}

	ResetVariables();
}

void SaveManager::LoadSave(unsigned int saveIndex)
{
	m_SaveIndex = saveIndex;
	std::string path = "..\\res\\saves\\save_" + std::to_string(m_SaveIndex) + ".json";
	std::ifstream is;
	is.open(path);
	if (is.is_open())
	{
		std::stringstream buffer;
		buffer << is.rdbuf();
		
		Document document;
		document.Parse(buffer.str().c_str());

		SAVE::PLAYER_POS.x = document["pos"]["x"].GetFloat();
		SAVE::PLAYER_POS.y = document["pos"]["y"].GetFloat();

		SAVE::PLAYER_HEALTH = document["health"].GetInt();
		SAVE::COIN_NUMBER = document["coin"].GetUint();
		SAVE::LEVEL_ID = (LevelID)document["level"].GetUint();

		SAVE::ORC_BOSS_DEFEATED = document["orcBoss"].GetBool();
		SAVE::UNDEAD_BOSS_DEFEATED = document["undeadBoss"].GetBool();
		SAVE::DEMON_BOSS_DEFEATED = document["demonBoss"].GetBool();

		for (int i = 0; i < 8; ++i)
			SAVE::WEAPON[i] = (EntityID)document["weapons"][i].GetUint();
	}
	is.close();
}

void SaveManager::DeleteSave(unsigned int saveIndex)
{
	std::string path = "..\\res\\saves\\save_" + std::to_string(saveIndex) + ".json";
	std::string cmd = "if exist " + path + " (del " + path + ")";
	system(cmd.c_str());
	ResetVariables();
}

void SaveManager::SaveConfig()
{
	Document document;
	document.SetObject();

	auto& allocator = document.GetAllocator();

	Value musicValue(GLOBAL::MUSIC_VOLUME);
	Value soundValue(GLOBAL::SOUND_VOLUME);
	Value fullscreen(GLOBAL::FULLSCREEN);

	document.AddMember("music", musicValue, allocator);
	document.AddMember("sound", soundValue, allocator);
	document.AddMember("fullscreen", fullscreen, allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);

	const char* json = buffer.GetString();
	std::string path = "..\\res\\config.txt";
	std::ofstream os;
	os.open(path);
	if (os.is_open())
	{
		os << json;
	}
	os.close();
}

void SaveManager::LoadConfig()
{
	std::string path = "..\\res\\config.txt";
	std::ifstream is;
	is.open(path);
	if (is.is_open())
	{
		std::stringstream buffer;
		buffer << is.rdbuf();

		Document document;
		document.Parse(buffer.str().c_str());

		GLOBAL::MUSIC_VOLUME = document["music"].GetUint();
		GLOBAL::SOUND_VOLUME = document["sound"].GetUint();
		GLOBAL::FULLSCREEN = document["fullscreen"].GetBool();
	}
	is.close();
}

std::string SaveManager::GetInfo(unsigned int saveIndex)
{
	std::string s = "";
	unsigned int health = 0;
	unsigned int coin = 0;
	LevelID level = LevelID::Null;

	std::string path = "..\\res\\saves\\save_" + std::to_string(saveIndex) + ".json";
	std::ifstream is;
	is.open(path);
	if (is.is_open())
	{
		std::stringstream buffer;
		buffer << is.rdbuf();

		Document document;
		document.Parse(buffer.str().c_str());

		health = document["health"].GetInt();
		coin = document["coin"].GetUint();
		level = (LevelID)document["level"].GetUint();

		s += "Level: ";
		switch (level)
		{
		case LevelID::Entrance:
		{
			s += "Entrance\n";
			break;
		}
		case LevelID::OrcsOne:
		{
			s += "Orcs-1\n";
			break;
		}
		case LevelID::OrcsTwo:
		{
			s += "Orcs-2\n";
			break;
		}
		case LevelID::OrcsBoss:
		{
			s += "Orcs-Boss\n";
			break;
		}
		case LevelID::UndeadsOne:
		{
			s += "Undeads-1\n";
			break;
		}
		case LevelID::UndeadsTwo:
		{
			s += "Undeads-2\n";
			break;
		}
		case LevelID::UndeadsBoss:
		{
			s += "Undeads-Boss\n";
			break;
		}
		case LevelID::DemonsOne:
		{
			s += "Demons-1\n";
			break;
		}
		case LevelID::DemonsTwo:
		{
			s += "Demons-2\n";
			break;
		}
		default:
			break;
		}

		s += "Health: " + std::to_string(health) + "\n";
		s += "Coin: " + std::to_string(coin);
	}
	is.close();

	return s;
}

void SaveManager::ResetVariables()
{
	SAVE::PLAYER_POS = { 0.f, 0.f };
	SAVE::PLAYER_HEALTH = 100;
	SAVE::COIN_NUMBER = 0;
	SAVE::LEVEL_ID = LevelID::Null;
	for (int i = 0; i < 8; ++i)
		SAVE::WEAPON[i] = EntityID::Null;
	SAVE::ORC_BOSS_DEFEATED = false;
	SAVE::UNDEAD_BOSS_DEFEATED = false;
	SAVE::DEMON_BOSS_DEFEATED = false;
}
