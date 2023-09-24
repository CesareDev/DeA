#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Character.h"

class ArenaSpawner
{
public:

	ArenaSpawner();
	~ArenaSpawner();

	void Init(const ResourceManager& resourceManager, float minDistance, float maxDistance);
	void Update(sf::DynamicQuadTree<Entity>& tree, const sf::TileMap& tileMap, const sf::Vector2f& offset, float dt);

private:

	void AddEntity(EntityID entityId);
	Character* Spawn(const sf::TileMap& tileMap, const sf::Vector2f& offset);
	float RandomDistance();
	float RandomAngle();
	unsigned int RandomIndex();

private:

	const ResourceManager* m_ResourceManager;
	std::vector<EntityID> m_EntitiesToSpawn;
	float m_MinDistance;
	float m_MaxDistance;

	float m_SpawnTime;
	float m_SpawnInterval;
	float m_ElapsedTime;
	unsigned int m_MaxEntities;
};

