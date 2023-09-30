#pragma once
#include "Entities/EntityID.h"

struct EntityInfo
{
	EntityID id;
	sf::Vector2f position;
};

struct LevelInfo 
{
	std::string name;
	std::string dir;
};

struct EntityParameters
{
	unsigned int health;
	unsigned int damage;
	float velocityFactor;
};


namespace CONFIG
{
	inline std::vector<std::vector<EntityInfo>> LEVELS_ENTITIES_INFO;
	inline std::unordered_map<LevelID, LevelInfo> LEVELS_INFO;

	inline std::unordered_map<EntityID, EntityParameters> ENTITIES_PARAM;
	inline std::unordered_map<EntityID, unsigned int> WEAPONS_PARAM;
}
