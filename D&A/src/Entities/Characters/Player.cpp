#include "pch.h"
#include "Player.h"
#include "Entities/Weapons/Bow.h"
#include "Entities/Weapons/ColossalSword.h"
#include "Entities/Weapons/BigDamagePotion.h"
#include "Entities/Weapons/DamagePotion.h"

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
	SetPosition(position);

	m_Center = getPosition() + sf::Vector2f(8.f, 8.f);
	m_Bounds = { getPosition(), {16.f, 16.f} };
	m_IsMoving = false;
	m_ElapsedAnimationTime = 0.f;
	m_TextureRect = getTextureRect();
	m_Velocity = { 0.f, 0.f };

	//SAVE::HEALTH
	m_Health = SAVE::PLAYER_HEALTH;
	m_Coin = SAVE::COIN_NUMBER;

	//Switch SAVE::WEAPONS
	m_Weapons.resize(8);
	m_Weapons[m_WeaponIndex].reset(new Bow());
	m_Weapons[m_WeaponIndex]->Init(resourceManager, m_Center);
	m_Weapons[m_WeaponIndex + 1].reset(new BigDamagePotion());
	m_Weapons[m_WeaponIndex + 1]->Init(resourceManager, m_Center);
	m_Weapons[m_WeaponIndex + 2].reset(new ColossalSword());
	m_Weapons[m_WeaponIndex + 2]->Init(resourceManager, m_Center);
}

void Player::Update(UpdateArgs args, float dt)
{
	m_Paused = false;
	Movement(args, dt);
	UpdateAnimation(dt);

	if (m_Weapons[m_WeaponIndex])
		m_Weapons[m_WeaponIndex]->Update(args, dt);

	for (const auto& weapon : m_Weapons)
		if (weapon)
			if (weapon->GetId() == EntityID::BigDamagePotion)
				((BigDamagePotion*)weapon.get())->UpdateAttackZone(args, dt);
			else if (weapon->GetId() == EntityID::DamagePotion)
				((DamagePotion*)weapon.get())->UpdateAttackZone(args, dt);

	for (auto& en : args.qTree.search(m_Bounds))
	{
		if (en->obj->GetId() == EntityID::Coin)
		{
			Entity* p = en->obj;
			args.qTree.remove(en);
			m_Coin++;
			delete p;
		}
	}
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Player::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	for (const auto& weapon : m_Weapons)
		if (weapon)
			weapon->SetPosition(m_Center);
	m_Bounds.position = getPosition();
}

EntityID Player::GetId() const
{
	return EntityID::Player;
}

void Player::SetCurrentWeaponIndex(unsigned int index)
{
	m_WeaponIndex = index;
}

EntityID Player::GetWeaponID(unsigned int index)
{
	if (m_Weapons[index])
		return m_Weapons[index]->GetId();
	return EntityID::Null;
}

bool Player::IsAttacking()
{ 
	if (m_Weapons[m_WeaponIndex])
		return m_Weapons[m_WeaponIndex]->IsAttacking();
	return false;
}

void Player::RenderWeapon(sf::RenderTarget& target)
{
	if (!m_Paused)
		for (auto& weapon : m_Weapons)
			if (weapon)
				weapon->SetAngle(target);
	if (m_Weapons[m_WeaponIndex])
		m_Weapons[m_WeaponIndex]->Render(target);
	for (const auto& weapon : m_Weapons)
		if (weapon)
			if (weapon->GetId() == EntityID::BigDamagePotion)
				((BigDamagePotion*)weapon.get())->RenderAttackZone(target);
			else if (weapon->GetId() == EntityID::DamagePotion)
				((DamagePotion*)weapon.get())->RenderAttackZone(target);
	m_Paused = true;
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

	SAVE::PLAYER_POS = getPosition();
	SAVE::PLAYER_HEALTH = m_Health;
	SAVE::COIN_NUMBER = m_Coin;
	SAVE::LEVEL_ID = args.currentLevel;
	for (int i = 0; i < m_Weapons.size(); ++i)
		if (m_Weapons[i])
			SAVE::WEAPON[i] = m_Weapons[i]->GetId();
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