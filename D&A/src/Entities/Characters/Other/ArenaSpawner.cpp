#include "pch.h"
#include "ArenaSpawner.h"
#include "Entities/EntityInclude.h"

ArenaSpawner::ArenaSpawner()
{
}

ArenaSpawner::~ArenaSpawner()
{
}

void ArenaSpawner::Init(const ResourceManager& resourceManager, float minDistance, float maxDistance)
{
    m_ResourceManager = &resourceManager;
    m_MinDistance = minDistance;
    m_MaxDistance = maxDistance;
	m_MaxEntities = 25;
	m_SpawnInterval = 5.f;

	AddEntity(EntityID::SmallDemon);
	AddEntity(EntityID::HalfDemon);
	AddEntity(EntityID::Demon);
	AddEntity(EntityID::MagicDemon);
	AddEntity(EntityID::SmallOrc);
	AddEntity(EntityID::Orc);
	AddEntity(EntityID::MaskedOrc);
	AddEntity(EntityID::TribalOrc);
	AddEntity(EntityID::SmallUndead);
	AddEntity(EntityID::HalfUndead);
	AddEntity(EntityID::Undead);
	AddEntity(EntityID::UndeadSlime);
}

void ArenaSpawner::AddEntity(EntityID entityId)
{
    if (std::find(m_EntitiesToSpawn.begin(), m_EntitiesToSpawn.end(), entityId) == m_EntitiesToSpawn.end())
        m_EntitiesToSpawn.push_back(entityId);
}

void ArenaSpawner::Update(sf::DynamicQuadTree<Entity>& tree, const sf::TileMap& tileMap, const sf::Vector2f& offset, float dt)
{
	m_ElapsedTime += dt;
	if (tree.size() - 1 < m_MaxEntities)
	{
		m_SpawnTime += dt;
		if (m_SpawnTime > m_SpawnInterval)
		{
			Character* c = Spawn(tileMap, offset);
			if (c)
			{
				tree.insert(c, c->GetBounds());
				m_SpawnTime = 0.f;
			}
		}
	}

	if (m_ElapsedTime > 60.f)
	{
		if (m_MaxEntities < 200)
		{
			m_MaxEntities += 25;
		}
		if (m_SpawnInterval > 1.f)
		{
			m_SpawnInterval -= 0.5f;
		}
		m_ElapsedTime = 0.f;
	}
}

Character* ArenaSpawner::Spawn(const sf::TileMap& tileMap, const sf::Vector2f& offset)
{
	float angle = RandomAngle();
	float radius = RandomDistance();
	float x = radius * cosf(angle * M_PI / 180.f);
	float y = radius * sinf(angle * M_PI / 180.f);

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
		entity->Init(*m_ResourceManager, { x, y });
	return entity;
}

float ArenaSpawner::RandomDistance()
{
	return m_MinDistance + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_MaxDistance - m_MinDistance)));
}

float ArenaSpawner::RandomAngle()
{
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 360.f));
}

unsigned int ArenaSpawner::RandomIndex()
{
	return rand() % m_EntitiesToSpawn.size();
}
