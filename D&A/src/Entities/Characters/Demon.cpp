#include "pch.h"
#include "Demon.h"

Demon::Demon()
{
}

Demon::~Demon()
{
}

void Demon::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 256, 400, 16, 24 });
	SetPosition(position);
	setOrigin(0.f, 8.f);

	m_IsMoving = false;
	m_ElapsedAnimationTime = 0.f;
	m_TextureRect = getTextureRect();

	m_Health = 1;
	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
	m_DamageTaken.setFont(font);
	m_DamageTaken.setCharacterSize(40);
	m_DamageTaken.setScale(0.f, 0.f);
	m_DamageTaken.setOutlineColor(sf::Color::Black);
	m_DamageTaken.setOutlineThickness(4.f);
}

void Demon::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Rectangle attackArea = { m_Center - sf::Vector2f(64.f, 64.f), {128.f, 128.f} };
		m_Velocity = { 0.f, 0.f };
		sf::Vector2f dir = { 0.f, 0.f };

		sf::Vector2f pcenter;
		bool findPlayer = false;
		for (const auto& it : args.qTree.search(attackArea))
		{
			if (it->obj->GetType() == EntityType::Character)
			{
				if (it->obj->GetId() == EntityID::Player)
				{
					pcenter = it->obj->GetCenter();
					findPlayer = true;
					continue;
				}
				if (it->obj != this && it->obj->GetId() != EntityID::Player && it->obj->GetId() != EntityID::Arrow)
				{
					if (m_Bounds.overlaps(it->obj->GetBounds()))
					{
						const auto& epos = it->obj->GetCenter();
						float d = sf::distance(m_Center, epos);
						float radsum = 8.f + (it->obj->GetBounds().size.x / 2.f);
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

		if (findPlayer)
		{
			const auto& path = args.astar.calcolatePath(sf::Vector2i(m_Center), sf::Vector2i(pcenter));
			if (path.size() > 0)
			{
				sf::Vector2f target = sf::Vector2f(path.back()->position) + sf::Vector2f(8.f, 8.f);
				float mag = sf::distance(m_Center, target);
				if (mag > 0.5)
				{
					m_IsMoving = true;
					dir = (target - m_Center) / mag;
					m_Velocity = dir * 32.f;
				}
			}
		}

		sf::Vector2f potentialPos = getPosition() + m_Velocity * dt;
		
		sf::Vector2f potentialPosInUnit = { potentialPos.x / m_TextureRect.width, potentialPos.y / m_TextureRect.width };
		sf::Vector2f positionInUnit = { getPosition().x / m_TextureRect.width, getPosition().y / m_TextureRect.width };

		bool wally = false;
		bool wallx = false;
		sf::Vector2f wallVel;

		//Left
		if (m_Velocity.x < 0)
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y + 0.9f)))
			{
				potentialPosInUnit.x = (int)potentialPosInUnit.x + 1;
				m_Velocity.x = 0.f;
				if (m_IsMoving)
				{
					wallx = true;
					wallVel.y = m_Velocity.y > 0.f ? 32.f : -32.f;
				}
			}
		}
		//Right
		else
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y + 0.9f)))
			{
				potentialPosInUnit.x = (int)potentialPosInUnit.x;
				m_Velocity.x = 0.f;
				if (m_IsMoving)
				{
					wallx = true;
					wallVel.y = m_Velocity.y > 0.f ? 32.f : -32.f;
				}
			}
		}

		//Up
		if (m_Velocity.y < 0)
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y)))
			{
				potentialPosInUnit.y = (int)potentialPosInUnit.y + 1;
				m_Velocity.y = 0.f;
				if (m_IsMoving)
				{
					wally = true;
					wallVel.x = m_Velocity.x > 0.f ? 32.f : -32.f;
				}
			}
		}
		//Down
		else
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y + 1.f)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y + 1.f)))
			{
				potentialPosInUnit.y = (int)potentialPosInUnit.y;
				m_Velocity.y = 0.f;
				if (m_IsMoving)
				{
					wally = true;
					wallVel.x = m_Velocity.x > 0.f ? 32.f : -32.f;
				}
			}
		}

		if (wallx)
		{
			if (wallVel.x < 0.f)
			{
				setOrigin(m_TextureRect.width, 8.f);
				setScale(-1.f, 1.f);
			}
			else if (wallVel.x > 0.f)
			{
				setOrigin(0.f, 8.f);
				setScale(1.f, 1.f);
			}
		}
		else
		{
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
		}

		if (wallx)
			potentialPos.y = ((potentialPosInUnit.y * m_TextureRect.width) - m_Velocity.y * dt) + wallVel.y * dt;
		else
			potentialPos.y = potentialPosInUnit.y * m_TextureRect.width;

		if (wally)
			potentialPos.x = ((potentialPosInUnit.x * m_TextureRect.width) - m_Velocity.x * dt) + wallVel.x * dt;
		else
			potentialPos.x = potentialPosInUnit.x * m_TextureRect.width;

		SetPosition(potentialPos);

		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.1f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 424;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 320)
				{
					m_TextureRect.left = 256;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 400;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 320)
				{
					m_TextureRect.left = 256;
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

void Demon::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	RenderDamage(target);
}

void Demon::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	if (m_IsMoving)
	{
		m_Bounds.position = position + sf::Vector2f(2.f, -2.f);
		m_Bounds.size = m_Bounds.size = { 12.f, 18.f };
	}
	else
	{
		m_Bounds.position = position + sf::Vector2f(2.f, 0.f);
		m_Bounds.size = m_Bounds.size = { 12.f, 16.f };
	}
}

EntityID Demon::GetId() const
{
	return EntityID::Demon;
}
