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

		for (int i = 0; i < 8; ++i)
		{
			weaponArray.PushBack((unsigned int)SAVE::WEAPON[i], allocator);
		}

		document.AddMember("pos", playerPos, allocator);
		document.AddMember("health", health, allocator);
		document.AddMember("coin", coin, allocator);
		document.AddMember("level", levelId, allocator);
		document.AddMember("weapons", weaponArray, allocator);

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
			os.close();
		}
	}
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

		for (int i = 0; i < 8; ++i)
			SAVE::WEAPON[i] = (EntityID)document["weapons"][i].GetUint();
	}
}