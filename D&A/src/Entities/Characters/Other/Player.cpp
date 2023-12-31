#include "pch.h"
#include "Player.h"
#include "Entities/Weapons/WeaponInclude.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	m_ResourceManager = &resourceManager;

	setTexture(resourceManager.GetTilesetTexture());
	setOrigin(0.f, 8.f);
	setTextureRect({ 0, 464, 16, 24 });
	SetPosition(position);

	m_IsMoving = false;
	m_ElapsedAnimationTime = 0.f;
	m_TextureRect = getTextureRect();
	m_Velocity = { 0.f, 0.f };

	InitDamageText(resourceManager);

	//SAVE::HEALTH
	m_Health = SAVE::PLAYER_HEALTH;
	m_Coin = SAVE::COIN_NUMBER;

	//Switch SAVE::WEAPONS
	m_Weapons.resize(8);

	for (int i = 0; i < 8; ++i)
	{
		switch (SAVE::WEAPON[i])
		{
		case EntityID::Knife:
			m_Weapons[i].reset(new Knife());
			break;
		case EntityID::RustySword:
			m_Weapons[i].reset(new RustySword());
			break;
		case EntityID::Sword:
			m_Weapons[i].reset(new Sword());
			break;
		case EntityID::MagicSword:
			m_Weapons[i].reset(new MagicSword());
			break;
		case EntityID::GreatHammer:
			m_Weapons[i].reset(new GreatHammer());
			break;
		case EntityID::Hammer:
			m_Weapons[i].reset(new Hammer());
			break;
		case EntityID::Mace:
			m_Weapons[i].reset(new Mace());
			break;
		case EntityID::GreatMace:
			m_Weapons[i].reset(new GreatMace());
			break;
		case EntityID::Katana:
			m_Weapons[i].reset(new Katana());
			break;
		case EntityID::GreatSword:
			m_Weapons[i].reset(new GreatSword());
			break;
		case EntityID::ColossalSword:
			m_Weapons[i].reset(new ColossalSword());
			break;
		case EntityID::GoldenSword:
			m_Weapons[i].reset(new GoldenSword());
			break;
		case EntityID::ColossalGoldenSword:
			m_Weapons[i].reset(new ColossalGoldenSword());
			break;
		case EntityID::GreatAxe:
			m_Weapons[i].reset(new GreatAxe());
			break;
		case EntityID::Spear:
			m_Weapons[i].reset(new Spear());
			break;
		case EntityID::Bow:
			m_Weapons[i].reset(new Bow());
			break;
		case EntityID::HealthPotion:
			m_Weapons[i].reset(new HealthPotion());
			break;
		case EntityID::BigHealthPotion:
			m_Weapons[i].reset(new BigHealthPotion());
			break;
		case EntityID::DamagePotion:
			m_Weapons[i].reset(new DamagePotion());
			break;
		case EntityID::BigDamagePotion:
			m_Weapons[i].reset(new BigDamagePotion());
			break;
		default:
			break;
		}
		if (m_Weapons[i])
			m_Weapons[i]->Init(resourceManager, m_Center);
	}
}

void Player::Update(UpdateArgs args, float dt)
{
	if (m_Health > 0)
	{
		m_Paused = false;
		Movement(args, dt);

		//Update Weapons
		if (m_Weapons[m_WeaponIndex])
			m_Weapons[m_WeaponIndex]->Update(args, dt);

		for (auto& weapon : m_Weapons)
		{
			if (weapon)
			{
				if (weapon->GetId() == EntityID::BigDamagePotion)
				{
					((BigDamagePotion*)weapon.get())->UpdateAttackZone(args, dt);
					if (((BigDamagePotion*)weapon.get())->IsFinished())
						weapon.reset();
				}
				else if (weapon->GetId() == EntityID::DamagePotion)
				{
					((DamagePotion*)weapon.get())->UpdateAttackZone(args, dt);
					if (((DamagePotion*)weapon.get())->IsFinished())
						weapon.reset();
				}
				else if (weapon->GetId() == EntityID::BigHealthPotion)
				{
					if (((BigHealthPotion*)weapon.get())->IsFinished())
					{
						if (m_Health + 50 > 100)
							m_Health = 100;
						else
							m_Health += 50;
						MUSIC::REGEN_SOUND->play();
						weapon.reset();
					}
				}
				else if (weapon->GetId() == EntityID::HealthPotion)
				{
					if (((HealthPotion*)weapon.get())->IsFinished())
					{
						if (m_Health + 25 > 100)
							m_Health = 100;
						else
							m_Health += 25;
						MUSIC::REGEN_SOUND->play();
						weapon.reset();
					}
				}
			}
		}

		for (auto& en : args.qTree.search(m_Bounds))
		{
			if (en->obj->GetId() == EntityID::Coin)
			{
				Entity* p = en->obj;
				args.qTree.remove(en);
				m_Coin++;
				MUSIC::COIN_SOUND->play();
				delete p;
			}
		}

		UpdateAnimation(dt);
		DamageAnimation(dt);
	}
	else
	{
		DeathAnimation(dt);
		if (m_IsDead)
			args.currentState = StateID::GameOverState;
	}
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	RenderDamage(target);
}

void Player::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_Center = position + sf::Vector2f(8.f, 8.f);
	for (const auto& weapon : m_Weapons)
		if (weapon)
			weapon->SetPosition(m_Center);
	if (m_IsMoving)
	{
		m_Bounds.position = position + sf::Vector2f(3.f, -2.f);
		m_Bounds.size = { 10.f, 18.f };
	}
	else
	{
		m_Bounds.position = position + sf::Vector2f(3.f, 0.f);
		m_Bounds.size = { 10.f, 16.f };
	}
}

void Player::RenderWeapon(sf::RenderTarget& target)
{
	if (m_Health > 0)
	{
		if (!m_Paused)
			for (auto& weapon : m_Weapons)
				if (weapon)
					weapon->SetAngle(target);
		if (m_Weapons[m_WeaponIndex])
			m_Weapons[m_WeaponIndex]->Render(target);
		for (const auto& weapon : m_Weapons)
		{
			if (weapon)
			{
				if (weapon->GetId() == EntityID::BigDamagePotion)
					((BigDamagePotion*)weapon.get())->RenderAttackZone(target);
				else if (weapon->GetId() == EntityID::DamagePotion)
					((DamagePotion*)weapon.get())->RenderAttackZone(target);
			}
		}
		m_Paused = true;
	}
}

EntityID Player::GetId() const
{
	return EntityID::Player;
}

void Player::SetCoin(unsigned int coin)
{
	m_Coin = coin;
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

bool Player::AddWeapon(Weapon* weapon)
{
	if (weapon->GetId() != EntityID::Null)
	{
		if (m_Weapons[m_WeaponIndex] && weapon->GetId() != m_Weapons[m_WeaponIndex]->GetId())
		{
			m_Weapons[m_WeaponIndex].reset(weapon);
			m_Weapons[m_WeaponIndex]->Init(*m_ResourceManager, m_Center);
		}
		else if (!m_Weapons[m_WeaponIndex])
		{
			m_Weapons[m_WeaponIndex].reset(weapon);
			m_Weapons[m_WeaponIndex]->Init(*m_ResourceManager, m_Center);
		}
		return true;
	}
	return false;
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
	

	if (GLOBAL::JOYSTICK_AVAILABLE)
	{
		int rx = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		int ry = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

		if (rx > 10)
		{
			setOrigin(0.f, 8.f);
			setScale(1.f, 1.f);
			m_IsMoving = true;
			m_Velocity.x = (rx - 10.f) / 90.f;
		}
		else if (rx < -10)
		{
			setOrigin(m_TextureRect.width, 8.f);
			setScale(-1.f, 1.f);
			m_IsMoving = true;
			m_Velocity.x = (rx + 10.f) / 90.f;
		}

		if (ry > 10)
		{
			m_IsMoving = true;
			m_Velocity.y = (ry - 10.f) / 90.f;
		}
		else if (ry < -10)
		{
			m_IsMoving = true;
			m_Velocity.y = (ry + 10.f) / 90.f;
		}
	}

	m_Velocity *= 64.f;

	sf::Vector2f potentialPos = m_Center + m_Velocity * dt;

	sf::Vector2f potentialPosInUnit = { potentialPos.x / m_TextureRect.width, potentialPos.y / m_TextureRect.width };
	sf::Vector2f positionInUnit = { m_Center.x / m_TextureRect.width, m_Center.y / m_TextureRect.width };

	//TEST OTHER COLLISION
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
					potentialPosInUnit = potentialPosInUnit - (rayToNearest / rayMag) * overlap;
				}
			}
		}
	}

	////Left
	//if (m_Velocity.x < 0)
	//{
	//	if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, positionInUnit.y + 0.9f)))
	//	{
	//		potentialPosInUnit.x = (int)potentialPosInUnit.x + 1;
	//		m_Velocity.x = 0.f;
	//	}
	//}
	////Right
	//else
	//{
	//	if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 1.f, positionInUnit.y + 0.9f)))
	//	{
	//		potentialPosInUnit.x = (int)potentialPosInUnit.x;
	//		m_Velocity.x = 0.f;
	//	}
	//}

	////Up
	//if (m_Velocity.y < 0)
	//{
	//	if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y)))
	//	{
	//		potentialPosInUnit.y = (int)potentialPosInUnit.y + 1;
	//		m_Velocity.y = 0.f;
	//	}
	//}
	////Down
	//else
	//{
	//	if (args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x, potentialPosInUnit.y + 1.f)) || args.tileMap.isCellWall(sf::Vector2i(potentialPosInUnit.x + 0.9f, potentialPosInUnit.y + 1.f)))
	//	{
	//		potentialPosInUnit.y = (int)potentialPosInUnit.y;
	//		m_Velocity.y = 0.f;
	//	}
	//}

	potentialPos.x = potentialPosInUnit.x * m_TextureRect.width;
	potentialPos.y = potentialPosInUnit.y * m_TextureRect.width;

	SetPosition(potentialPos - sf::Vector2f(8.f, 8.f));

	SAVE::PLAYER_POS = getPosition();
	SAVE::PLAYER_HEALTH = m_Health;
	SAVE::COIN_NUMBER = m_Coin;
	for (int i = 0; i < m_Weapons.size(); ++i)
		if (m_Weapons[i])
			SAVE::WEAPON[i] = m_Weapons[i]->GetId();
		else
			SAVE::WEAPON[i] = EntityID::Null;
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