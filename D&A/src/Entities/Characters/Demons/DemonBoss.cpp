#include "pch.h"
#include "DemonBoss.h"

DemonBoss::DemonBoss()
{
}

DemonBoss::~DemonBoss()
{
}

void DemonBoss::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setTextureRect({ 0, 352, 32, 48 });
    setOrigin(0.f, 16.f);
    SetPosition(position);

	InitParameters();
	InitDamageText(resourceManager);

	int coinsCount = 10;
	for (int i = 0; i < coinsCount; ++i)
	{
		Coin* c = new Coin();
		c->Init(resourceManager, position);
		m_Coins.push_back(c);
	}

	m_Spawner.Init(resourceManager, 24.f, 64.f);
	m_Spawner.AddEntity(EntityID::SmallDemon);
	m_Spawner.AddEntity(EntityID::HalfDemon);
	m_Spawner.AddEntity(EntityID::Demon);
	m_Spawner.AddEntity(EntityID::MagicDemon);
}

void DemonBoss::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Vector2f offsetRect = sf::Vector2f(args.tileMap.getMapSize());
		sf::Rectangle attackArea = { m_Center - offsetRect / 2.f, offsetRect };
		m_Velocity = { 0.f, 0.f };
		sf::Vector2f dir = { 0.f, 0.f };

		sf::Vector2f pcenter;
		for (const auto& it : args.qTree.search(attackArea))
		{
			if (it->obj->GetType() == EntityType::Character)
			{
				if (it->obj->GetId() == EntityID::Player)
				{
					pcenter = it->obj->GetCenter();
					float mag = sf::distance(m_Center, pcenter);
					if (mag > 0.5)
					{
						m_IsMoving = true;
						dir = (pcenter - m_Center) / mag;
						m_Velocity = dir * m_VelocityFactor;
					}
					if (m_Bounds.overlaps(it->obj->GetBounds()))
					{
						((Character*)it->obj)->TakeDamage(m_Damage);
					}
					continue;
				}
				if (it->obj != this && it->obj->GetId() != EntityID::Player && it->obj->GetId() != EntityID::Arrow)
				{
					if (m_Bounds.overlaps(it->obj->GetBounds()))
					{
						const auto& epos = it->obj->GetCenter();
						float d = sf::distance(m_Center, epos);
						float radsum = (m_Bounds.size.x / 2.f) + (it->obj->GetBounds().size.x / 2.f);
						if (d < radsum)
						{
							sf::Vector2f normal = (m_Center - epos) / d;
							float depth = radsum - d;
							SetPosition(getPosition() + normal * depth / 2.f);
							m_IsMoving = true;
						}
					}
				}
			}
		}

		//Spawner
		m_Spawner.Update();
		if (m_Spawner.GetEntitiesCount() == 0)
		{
			if (!m_CanSpawn)
			{
				m_SpawnTime += dt;
				if (m_SpawnTime > 5.f)
				{
					m_CanSpawn = true;
					m_SpawnTime = 0.f;
				}
			}
		}
		if (m_CanSpawn)
		{
			if (m_Spawner.GetEntitiesCount() < 5)
			{
				m_SpawnTime += dt;
				if (m_SpawnTime > 2.f)
				{
					Character* c = m_Spawner.Spawn(args.tileMap, m_Center);
					if (c)
						args.qTree.insert(c, c->GetBounds());
					m_SpawnTime = 0.f;
				}
			}
			else
			{
				m_SpawnTime = 0.f;
				m_CanSpawn = false;
			}
		}

		if (m_FindPath)
		{
			const auto& path = args.astar.calcolatePath(sf::Vector2i(m_Center), sf::Vector2i(pcenter));
			if (path.size() > 1)
			{
				sf::Vector2f target = sf::Vector2f(path.back()->position) + sf::Vector2f(8.f, 8.f);
				float mag = sf::distance(m_Center, target);
				if (mag > 0.5)
				{
					m_IsMoving = true;
					dir = (target - m_Center) / mag;
					m_Velocity = dir * m_VelocityFactor;
				}
			}
			else
			{
				m_FindPath = false;
			}
		}

		sf::Vector2f potentialPos = m_Center + m_Velocity * dt;
		sf::Vector2f potentialPosInUnit = { potentialPos.x / 16.f, potentialPos.y / 16.f };
		sf::Vector2f positionInUnit = { m_Center.x / 16.f, m_Center.y / 16.f };

		bool wall = false;
		sf::Vector2i currentCell = sf::Vector2i(std::floor(positionInUnit.x), std::floor(positionInUnit.y));
		sf::Vector2i targetCell = sf::Vector2i(potentialPosInUnit);
		sf::Vector2i tl =
		{
			std::min(currentCell.x, targetCell.x) - 1,
			std::min(currentCell.y, targetCell.y) - 1
		};
		sf::Vector2i br =
		{
			std::max(currentCell.x, targetCell.x) + 1,
			std::max(currentCell.y, targetCell.y) + 1
		};

		sf::Vector2f rayToNearest;
		sf::Vector2i cell;
		for (cell.y = tl.y; cell.y <= br.y; cell.y++)
		{
			for (cell.x = tl.x; cell.x <= br.x; cell.x++)
			{
				if (args.tileMap.isCellWall(cell))
				{
					sf::Vector2f nearestPoint =
					{
						std::max(float(cell.x), std::min(potentialPosInUnit.x, float(cell.x + 1))),
						std::max(float(cell.y), std::min(potentialPosInUnit.y, float(cell.y + 1)))
					};
					rayToNearest = nearestPoint - potentialPosInUnit;
					float rayMag = std::sqrtf(rayToNearest.x * rayToNearest.x + rayToNearest.y * rayToNearest.y);
					float overlap = 1.f - rayMag;
					if (std::isnan(overlap))
						overlap = 0.f;
					if (overlap > 0.f)
					{
						wall = true;
						potentialPosInUnit = potentialPosInUnit - (rayToNearest / rayMag) * overlap;
					}
				}
			}
		}

		if (wall)
			m_FollowElapsedTime += dt;

		if (m_FollowElapsedTime > 5.f)
		{
			m_FindPath = true;
			m_FollowElapsedTime = 0.f;
		}

		potentialPos.x = potentialPosInUnit.x * 16.f;
		potentialPos.y = potentialPosInUnit.y * 16.f;

		SetPosition(potentialPos - sf::Vector2f(16.f, 16.f));

		if (m_Velocity.x < 0.f)
		{
			setOrigin(m_TextureRect.width, 16.f);
			setScale(-1.f, 1.f);
		}
		else if (m_Velocity.x > 0.f)
		{
			setOrigin(0.f, 16.f);
			setScale(1.f, 1.f);
		}

		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.1f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 400;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 32;
				if (m_TextureRect.left >= 128)
				{
					m_TextureRect.left = 0;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 352;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 32;
				if (m_TextureRect.left >= 128)
				{
					m_TextureRect.left = 0;
				}
				m_ElapsedAnimationTime = 0.f;
			}
		}

		DamageAnimation(dt);
	}
	else
	{
		DeathAnimation(dt);
		SpawnCoins(args);
		if (m_IsDead)
			SAVE::DEMON_BOSS_DEFEATED = true;
	}
}

void DemonBoss::Render(sf::RenderTarget& target)
{
    target.draw(*this);
	RenderDamage(target);
}

void DemonBoss::SetPosition(const sf::Vector2f& position)
{
    setPosition(position);
    m_Center = position + sf::Vector2f(16.f, 16.f);
	if (m_IsMoving)
	{
		m_Bounds.position = position + sf::Vector2f(7.f, 4.f);
		m_Bounds.size = { 18.f, 28.f };
	}
	else
	{
		m_Bounds.position = position + sf::Vector2f(7.f, 6.f);
		m_Bounds.size = { 18.f, 26.f };
	}
}

EntityID DemonBoss::GetId() const
{
    return EntityID::DemonBoss;
}
