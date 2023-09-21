#include "pch.h"
#include "Spawner.h"
#include "Entities/EntityInclude.h"

#include <algorithm>

Spawner::Spawner()
{
}

Spawner::~Spawner()
{
	while (!m_CharacterQueue.empty())
	{
		delete m_CharacterQueue.front();
		m_CharacterQueue.pop();
	}
}

void Spawner::Init(const ResourceManager& resourceManager, float minDistance, float maxDistance)
{
	m_ResourceManager = &resourceManager;
	m_MinDistance = minDistance;
	m_MaxDistance = maxDistance;
}

void Spawner::Update()
{
	if (!m_CharacterQueue.empty())
	{
		auto c = m_CharacterQueue.front();
		if (c->IsDead())
		{
			delete c;
			m_CharacterQueue.pop();
		}
	}
}

void Spawner::AddEntity(EntityID entityId)
{
	if (std::find(m_EntitiesToSpawn.begin(), m_EntitiesToSpawn.end(), entityId) == m_EntitiesToSpawn.end())
		m_EntitiesToSpawn.push_back(entityId);
}

Character* Spawner::Spawn(const sf::TileMap& tileMap, const sf::Vector2f& offset)
{
	float angle = RandomAngle();
	float radius = RandomDistance();
	float x = radius * cosf(angle * acos(-1.f) / 180.f);
	float y = radius * sinf(angle * acos(-1.f) / 180.f);
	
	x += offset.x;
	y += offset.y;

	int ux = x / 16.f;
	int uy = y / 16.f;

	if (tileMap.isCellWall({ ux, uy }) || !tileMap.isCellTile({ ux, uy }))
		return nullptr;

	unsigned int index = RandomIndex();
	EntityID id = EntityID::Null;
	if (!m_EntitiesToSpawn.empty())
		id = m_EntitiesToSpawn[index];
	Character* entity = nullptr;
	switch (id)
	{
	case EntityID::SmallDemon:
		entity = new SmallDemon();
		break;
	case EntityID::HalfDemon:
		entity = new HalfDemon();
		break;
	case EntityID::Demon:
		entity = new Demon();
		break;
	case EntityID::MagicDemon:
		entity = new MagicDemon();
		break;
	case EntityID::SmallOrc:
		entity = new SmallOrc();
		break;
	case EntityID::Orc:
		entity = new Orc();
		break;
	case EntityID::MaskedOrc:
		entity = new MaskedOrc();
		break;
	case EntityID::TribalOrc:
		entity = new TribalOrc();
		break;
	case EntityID::SmallUndead:
		entity = new SmallUndead();
		break;
	case EntityID::HalfUndead:
		entity = new HalfUndead();
		break;
	case EntityID::Undead:
		entity = new Undead();
		break;
	case EntityID::UndeadSlime:
		entity = new UndeadSlime();
		break;
	default:
		break;
	}
	if (entity)
	{
		entity->Init(*m_ResourceManager, { x, y });
		m_CharacterQueue.push(entity);
	}
	return entity;
}

unsigned int Spawner::GetEntitiesCount() const
{
	return m_CharacterQueue.size();
}

float Spawner::RandomDistance()
{
	return m_MinDistance + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_MaxDistance - m_MinDistance)));
}

float Spawner::RandomAngle()
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360.f));
}

unsigned int Spawner::RandomIndex()
{
	return rand() % m_EntitiesToSpawn.size();
}
