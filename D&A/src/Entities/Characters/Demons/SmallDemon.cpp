#include "pch.h"
#include "SmallDemon.h"

SmallDemon::SmallDemon()
{
}

SmallDemon::~SmallDemon()
{
}

void SmallDemon::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 128, 416, 16, 16 });
	SetPosition(position);
	setOrigin(0.f, 6.f);

	m_IsMoving = false;
	m_ElapsedAnimationTime = 0.f;
	m_TextureRect = getTextureRect();

	m_Health = 5;
	InitDamageText(resourceManager);
}

void SmallDemon::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Rectangle attackArea = { m_Center - sf::Vector2f(64.f, 64.f), {128.f, 128.f} };
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
					if (!m_FindPath)
					{
						float mag = sf::distance(m_Center, pcenter);
						if (mag > 0.5)
						{
							m_IsMoving = true;
							dir = (pcenter - m_Center) / mag;
							m_Velocity = dir * 48.f;
						}
						float radsum = (m_Bounds.size.x / 2.f) + (it->obj->GetBounds().size.x / 2.f);
						if (mag < radsum)
						{
							((Character*)it->obj)->TakeDamage(2);
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

		if (m_FindPath)
		{
			const auto& path = args.astar.calcolatePath(sf::Vector2i(m_Center), sf::Vector2i(pcenter));
			if (path.size() > 1)
			{
				sf::Vector2f targetCenter = sf::Vector2f(path.back()->position) + sf::Vector2f(8.f, 8.f);
				float mag = sf::distance(m_Center, targetCenter);
				if (mag > 0.5f)
				{
					m_IsMoving = true;
					dir = (targetCenter - m_Center) / mag;
					m_Velocity = dir * 48.f;
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
					float overlap = (m_Bounds.size.x / 32.f) - rayMag;
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

		SetPosition(potentialPos - sf::Vector2f(8.f, 5.f));

		if (m_Velocity.x < 0.f)
		{
			setOrigin(m_TextureRect.width, 6.f);
			setScale(-1.f, 1.f);
		}
		else if (m_Velocity.x > 0.f)
		{
			setOrigin(0.f, 6.f);
			setScale(1.f, 1.f);
		}

		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.08f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 432;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 192)
				{
					m_TextureRect.left = 128;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 416;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 192)
				{
					m_TextureRect.left = 128;
				}
				m_ElapsedAnimationTime = 0.f;
			}
		}

		//Damage
		DamageAnimation(dt);
	}
	else
	{
		DeathAnimation(dt);
	}
}

void SmallDemon::Render(sf::RenderTarget& target)
{    
	target.draw(*this);
	RenderDamage(target);
}

void SmallDemon::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 5.f);
	if (m_IsMoving)
	{
		m_Bounds.position = position + sf::Vector2f(4.f, -2.f);
		m_Bounds.size = { 8.f, 10.f };
	}
	else
	{
		m_Bounds.position = position + sf::Vector2f(4.f, 0.f);
		m_Bounds.size  = { 8.f, 8.f };
	}

}

EntityID SmallDemon::GetId() const
{
	return EntityID::SmallDemon;
}
