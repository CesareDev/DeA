#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setOrigin(0.f, 8.f);
	setTextureRect({ 0, 464, 16, 24 });
	setPosition(position);

	m_Center = getPosition() + sf::Vector2f(8.f, 8.f);
	m_Bounds = { getPosition(), {16.f, 16.f} };
	m_IsMoving = false;
	m_ElapsedAnimationTime = 0.f;
	m_TextureRect = getTextureRect();
	m_Velocity = { 0.f, 0.f };
	m_Health = 100;

	weapon.Init(resourceManager, m_Center);
}

void Player::Update(UpdateArgs args, float dt)
{
	Movement(args, dt);
	UpdateAnimation(dt);

	weapon.Update(args, dt);
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(*this);	
}

void Player::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	weapon.SetPosition(m_Center);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	m_Bounds.position = getPosition();
}

EntityID Player::GetId() const
{
	return EntityID::Player;
}

Weapon* Player::GetWeapon()
{
	return &weapon;
}

void Player::Movement(UpdateArgs args, float dt)
{
	m_IsMoving = false;
	m_Velocity = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_IsMoving = true;
		m_Velocity.y = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		setOrigin(m_TextureRect.width, 8.f);
		setScale(-1.f, 1.f);
		m_IsMoving = true;
		m_Velocity.x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_IsMoving = true;
		m_Velocity.y = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		setOrigin(0.f, 8.f);
		setScale(1.f, 1.f);
		m_IsMoving = true;
		m_Velocity.x = 1.f;
	}

	float mag = std::sqrtf(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
	if (mag != 0.f)
		m_Velocity /= mag;
	m_Velocity *= 64.f;

	sf::Vector2f potentialPos = getPosition() + m_Velocity * dt;

	sf::Vector2f potentialPosInUnit = { potentialPos.x / m_TextureRect.width, potentialPos.y / m_TextureRect.width };
	sf::Vector2f positionInUnit = { getPosition().x / m_TextureRect.width, getPosition().y / m_TextureRect.width };

	//Left
	if (m_Velocity.x < 0)
	{
		if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y + 0.9f)))
		{
			potentialPosInUnit.x = (int)potentialPosInUnit.x + 1;
			m_Velocity.x = 0.f;
		}
	}
	//Right
	else
	{
		if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y + 0.9f)))
		{
			potentialPosInUnit.x = (int)potentialPosInUnit.x;
			m_Velocity.x = 0.f;
		}
	}

	//Up
	if (m_Velocity.y < 0)
	{
		if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y)))
		{
			potentialPosInUnit.y = (int)potentialPosInUnit.y + 1;
			m_Velocity.y = 0.f;
		}
	}
	//Down
	else
	{
		if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y + 1.f)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y + 1.f)))
		{
			potentialPosInUnit.y = (int)potentialPosInUnit.y;
			m_Velocity.y = 0.f;
		}
	}

	potentialPos.x = potentialPosInUnit.x * m_TextureRect.width;
	potentialPos.y = potentialPosInUnit.y * m_TextureRect.width;

	SetPosition(potentialPos);
}

void Player::UpdateAnimation(float dt)
{
	m_ElapsedAnimationTime += dt;
	if (m_ElapsedAnimationTime > 0.1f)
	{
		if (m_IsMoving)
		{
			m_TextureRect.top = 488;
			setTextureRect(m_TextureRect);
			m_TextureRect.left += 16;
			if (m_TextureRect.left >= 64)
			{
				m_TextureRect.left = 0;
			}
			m_ElapsedAnimationTime = 0.f;
		}
		else
		{
			m_TextureRect.top = 464;
			setTextureRect(m_TextureRect);
			m_TextureRect.left += 16;
			if (m_TextureRect.left >= 64)
			{
				m_TextureRect.left = 0;
			}
			m_ElapsedAnimationTime = 0.f;
		}
	}
}