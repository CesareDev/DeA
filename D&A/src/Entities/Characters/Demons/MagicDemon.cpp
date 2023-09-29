#include "pch.h"
#include "MagicDemon.h"

MagicDemon::MagicDemon()
{
}

MagicDemon::~MagicDemon()
{
}

void MagicDemon::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 256, 328, 16, 24 });
	setOrigin(0.f, 8.f);
	SetPosition(position);
	m_Bounds.size = { 12.f, 17.f };

	InitParameters();
	InitDamageText(resourceManager);

	int coinsCount = (rand() % 5) + 1;
	for (int i = 0; i < coinsCount; ++i)
	{
		Coin* c = new Coin();
		c->Init(resourceManager, position);
		m_Coins.push_back(c);
	}

	m_MagicArea.setFillColor(sf::Color(0, 0, 0, 128));
	m_MagicArea.setRadius(24.f);
}

void MagicDemon::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Rectangle attackArea = { m_Center - sf::Vector2f(64.f, 64.f), {128.f, 128.f} };
		if (!m_ArenaPlayer && args.currentState == StateID::ArenaState)
			attackArea = { 0.f, 0.f, (float)args.tileMap.getMapSize().x, (float)args.tileMap.getMapSize().x };
		m_Velocity = { 0.f, 0.f };
		sf::Vector2f dir = { 0.f, 0.f };

		sf::Vector2f pcenter;
		if (m_ArenaPlayer && args.currentState == StateID::ArenaState)
		{
			pcenter = m_ArenaPlayer->GetCenter();
			float mag = sf::distance(m_Center, pcenter);
			if (mag > 0.5)
			{
				m_IsMoving = true;
				dir = (pcenter - m_Center) / mag;
				m_Velocity = dir * m_VelocityFactor;
			}
			if (m_Bounds.overlaps(m_ArenaPlayer->GetBounds()))
			{
				m_ArenaPlayer->TakeDamage(m_Damage);
				if (!m_CanMagicAttack)
					m_CanMagicAttack = true;
			}
			if (m_CanMagicAttack)
			{
				if (mag < m_MagicArea.getRadius() + (m_ArenaPlayer->GetBounds().size.x / 2.f))
				{
					m_ArenaPlayer->TakeDamage(1);
				}
			}
		}
		for (const auto& it : args.qTree.search(attackArea))
		{
			if (it->obj->GetType() == EntityType::Character)
			{
				if (!m_ArenaPlayer && it->obj->GetId() == EntityID::Player)
				{
					if (args.currentState == StateID::ArenaState)
					{
						if (!m_ArenaPlayer)
							m_ArenaPlayer = (Character*)it->obj;
					}
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
						if (!m_CanMagicAttack)
							m_CanMagicAttack = true;
					}
					if (m_CanMagicAttack)
					{
						if (mag < m_MagicArea.getRadius() + (it->obj->GetBounds().size.x / 2.f))
						{
							((Character*)it->obj)->TakeDamage(1);
						}
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

		if (m_CanMagicAttack)
		{
			m_MagicAttackElapsedTime += dt;
			if (m_MagicAttackElapsedTime > 3.f)
			{
				m_MagicAttackElapsedTime = 0.f;
				m_CanMagicAttack = false;
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
					float overlap = 0.5f - rayMag;
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

		SetPosition(potentialPos - sf::Vector2f(8.f, 8.f));

		if (m_Velocity.x < 0.f)
		{
			setOrigin(m_TextureRect.width, 8.f);
			setScale(-1.f, 1.f);
		}
		else if (m_Velocity.x > 0.f)
		{
			setOrigin(0.f, 8.f);
			setScale(1.f, 1.f);
		}

		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.1f)
		{
			setTextureRect(m_TextureRect);
			m_TextureRect.left += 16;
			if (m_TextureRect.left >= 320)
			{
				m_TextureRect.left = 256;
			}
			m_ElapsedAnimationTime = 0.f;
		}

		//Damage
		DamageAnimation(dt);
	}
	else
	{
		DeathAnimation(dt);
		SpawnCoins(args);
	}
}

void MagicDemon::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	RenderDamage(target);
}

void MagicDemon::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	m_Bounds.position = position + sf::Vector2f(2.f, -1.f);
	m_MagicArea.setPosition(m_Center - sf::Vector2f(24.f, 24.f));
}

void MagicDemon::RenderWeapon(sf::RenderTarget& target)
{
	if (m_CanMagicAttack)
		target.draw(m_MagicArea);
}

EntityID MagicDemon::GetId() const
{
	return EntityID::MagicDemon;
}