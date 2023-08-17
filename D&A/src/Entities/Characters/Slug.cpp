#include "pch.h"
#include "Slug.h"

Slug::Slug()
{
}

Slug::~Slug()
{
}

void Slug::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
    setTexture(resourceManager.GetTilesetTexture());
    setOrigin(0.f, 8.f);
    setTextureRect({ 320, 328, 16, 24 });
    SetPosition(position);

    m_Bounds.size = {16.f, 16.f};
    m_IsMoving = false;
    m_ElapsedAnimationTime = 0.f;
    m_TextureRect = getTextureRect();

	m_Health = 5;
	m_Vulnerable = true;
	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(40)).setSmooth(false);
	m_DamageTaken.setFont(font);
	m_DamageTaken.setCharacterSize(40);
	m_DamageTaken.setScale(0.f, 0.f);
	m_DamageTaken.setOutlineColor(sf::Color::Black);
	m_DamageTaken.setOutlineThickness(4.f);
}

void Slug::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		//Moving
		m_IsMoving = false;
		sf::Rectangle attackArea = { m_Center - sf::Vector2f(64.f, 64.f), {128.f, 128.f} };
		m_Velocity = { 0.f, 0.f };
		sf::Vector2f dir = { 0.f, 0.f };

		for (const auto& it : args.qTree.search(attackArea))
		{
			if (it->obj->GetType() == EntityType::Character)
			{
				if (it->obj->GetId() == EntityID::Player)
				{
					const auto& ppos = it->obj->GetCenter();
					float mag = sf::distance(ppos, m_Center);
					if (mag > 0.5f)
					{
						dir = (ppos - m_Center) / mag;
						m_IsMoving = true;
					}
					m_Velocity = dir * 8.f;
				}
				if (it->obj != this && it->obj->GetId() != EntityID::Player)
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

		sf::Vector2f potentialPos = getPosition() + m_Velocity * dt;

		sf::Vector2f potentialPosInUnit = { potentialPos.x / m_TextureRect.width, potentialPos.y / m_TextureRect.width };
		sf::Vector2f positionInUnit = { getPosition().x / m_TextureRect.width, getPosition().y / m_TextureRect.width };

		bool wallx = false;
		bool wally = false;

		//Left
		if (m_Velocity.x < 0)
		{
			if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y + 0.9f)))
			{
				potentialPosInUnit.x = (int)potentialPosInUnit.x + 1;
				m_Velocity.x = 0.f;
				if (m_IsMoving)
				{
					m_Velocity.y = m_Velocity.y > 0.f ? 8.f : -8.f;
					wallx = true;
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
					m_Velocity.y = m_Velocity.y > 0 ? 8.f : -8.f;
					wallx = true;
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
					m_Velocity.x = m_Velocity.x > 0.f ? 8.f : -8.f;
					wally = true;
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
					m_Velocity.x = m_Velocity.x > 0.f ? 8.f : -8.f;
					wally = true;
				}
			}
		}

		if (wallx)
			potentialPos.y = (potentialPosInUnit.y * m_TextureRect.width) + (m_Velocity.y * dt);
		else
			potentialPos.y = potentialPosInUnit.y * m_TextureRect.width;

		if (wally)
			potentialPos.x = (potentialPosInUnit.x * m_TextureRect.width) + (m_Velocity.x * dt);
		else
			potentialPos.x = potentialPosInUnit.x * m_TextureRect.width;


		SetPosition(potentialPos);
		
		//Animation
		m_ElapsedAnimationTime += dt;
		if (m_ElapsedAnimationTime > 0.25f)
		{
			if (m_IsMoving)
			{
				m_TextureRect.top = 352;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 384)
				{
					m_TextureRect.left = 320;
				}
				m_ElapsedAnimationTime = 0.f;
			}
			else
			{
				m_TextureRect.top = 328;
				setTextureRect(m_TextureRect);
				m_TextureRect.left += 16;
				if (m_TextureRect.left >= 384)
				{
					m_TextureRect.left = 320;
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

void Slug::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	if (m_VulnerableTime > 0.f)
	{
		sf::View currentCamera = target.getView();
		sf::View v(currentCamera.getCenter() * 5.f, currentCamera.getSize() * 5.f);
		target.setView(v);
		target.draw(m_DamageTaken);

		target.setView(currentCamera);
	}
}

void Slug::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	m_Bounds.position = position;
}

EntityID Slug::GetId() const
{
    return EntityID::Slug;
}
