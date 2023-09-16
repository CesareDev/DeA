#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Character.h"

#include <queue>

class Spawner
{
public:

	Spawner();
	~Spawner();

	void Init(const ResourceManager& resourceManager, float minDistance, float maxDistance);
	void AddEntity(EntityID entityId);
	void Update();
	Character* Spawn(const sf::TileMap& tileMap, const sf::Vector2f& offset);
	unsigned int GetEntitiesCount() const;

private:

	float RandomDistance();
	float RandomAngle();
	unsigned int RandomIndex();

private:

	const ResourceManager* m_ResourceManager;
	std::vector<EntityID> m_EntitiesToSpawn;
	std::queue<Character*> m_CharacterQueue;
	float m_MinDistance;
	float m_MaxDistance;
};

