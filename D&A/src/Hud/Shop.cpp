#include "pch.h"
#include "Shop.h"
#include "Entities/Weapons/WeaponInclude.h"

Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::Init(const ResourceManager& resourceManager, const Player& player)
{
	m_Player = const_cast<Player*>(&player);

	m_ItemList.setTexture(resourceManager.GetTilesetTexture());
	m_ItemList.setTextureRect({ 392, 197, 95, 62 });
	m_ItemList.setPosition(152.f, 74.f);

	m_SelectedWeaponFrame.setSize({ 21.f, 10.f });
	m_SelectedWeaponFrame.setFillColor(sf::Color(238, 142, 46, 80));

	const_cast<sf::Texture&>(resourceManager.GetFont().getTexture(40)).setSmooth(false);
	m_ShopText.setFont(resourceManager.GetFont());
	m_ShopText.setCharacterSize(40);
	if (GLOBAL::JOYSTICK_AVAILABLE)
		m_ShopText.setString("Shop (Right Button to Buy / X)");
	else
		m_ShopText.setString("Shop (Right Button to Buy)");
	m_ShopText.setOutlineColor(sf::Color::Black);
	m_ShopText.setOutlineThickness(4.f);
	m_ShopText.setPosition(999.5 - m_ShopText.getGlobalBounds().width / 2.f, 370.f - m_ShopText.getGlobalBounds().height - 8.f);

	m_WeaponsCost[0] = 0;
	m_WeaponsCost[1] = 3;
	m_WeaponsCost[2] = 7;
	m_WeaponsCost[3] = 15;
	m_WeaponsCost[4] = 18;
	m_WeaponsCost[5] = 12;
	m_WeaponsCost[6] = 8;
	m_WeaponsCost[7] = 12;
	m_WeaponsCost[8] = 20;
	m_WeaponsCost[9] = 25;
	m_WeaponsCost[10] = 30;
	m_WeaponsCost[11] = 60;
	m_WeaponsCost[12] = 80;
	m_WeaponsCost[13] = 25;
	m_WeaponsCost[14] = 20;
	m_WeaponsCost[15] = 50;
	m_WeaponsCost[16] = 10;
	m_WeaponsCost[17] = 25;
	m_WeaponsCost[18] = 5;
	m_WeaponsCost[19] = 10;
}

void Shop::Update(float dt)
{
	if (GLOBAL::JOYSTICK_AVAILABLE)
		m_ShopText.setString("Shop (Right Button to Buy / X)");
	else
		m_ShopText.setString("Shop (Right Button to Buy)");
	m_ShopText.setPosition(999.5 - m_ShopText.getGlobalBounds().width / 2.f, 370.f - m_ShopText.getGlobalBounds().height - 8.f);
	if (sf::Joystick::isButtonPressed(0, 0) && !m_Pressed)
	{
		m_Pressed = true;
		if (m_IsOpen)
			m_IsOpen = false;
		else
			m_IsOpen = true;
	}
	else if (!sf::Joystick::isButtonPressed(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_Pressed)
	{
		m_Pressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !m_Pressed)
	{
		m_Pressed = true;
		if (m_IsOpen)
			m_IsOpen = false;
		else
			m_IsOpen = true;
	}
	else if (!sf::Joystick::isButtonPressed(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_Pressed)
	{
		m_Pressed = false;
	}
}

void Shop::Render(sf::RenderTarget& target)
{
	if (m_IsOpen)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
		sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);

		target.draw(m_ItemList);
		if (m_ItemList.getGlobalBounds().contains(mpos))
		{
			mpos -= { 155.f, 77.f };
			int i = mpos.x / 22.f;
			int j = mpos.y / 11.f;

			if (i >= 0 && i < 4 && j >= 0 && j < 5)
			{
				sf::Vector2f rectPos = { i * 22.f + 156.f, j * 11.f + 78.f };
				m_SelectedWeaponFrame.setPosition(rectPos);

				if (sf::Joystick::isButtonPressed(0, 1) && !m_JoystickPressed)
				{
					m_JoystickPressed = true;
				}
				else if (!sf::Joystick::isButtonPressed(0, 1) && m_JoystickPressed)
				{
					int index = j * 4 + i;
					if (index >= 0 && index < 20)
					{
						bool result = false;
						if (m_Player->GetCoin() >= m_WeaponsCost[index])
						{
							switch (index)
							{
							case 0:
								result = m_Player->AddWeapon(new Knife());
								break;
							case 1:
								result = m_Player->AddWeapon(new RustySword());
								break;
							case 2:
								result = m_Player->AddWeapon(new Sword());
								break;
							case 3:
								result = m_Player->AddWeapon(new MagicSword());
								break;
							case 4:
								result = m_Player->AddWeapon(new GreatHammer());
								break;
							case 5:
								result = m_Player->AddWeapon(new Hammer());
								break;
							case 6:
								result = m_Player->AddWeapon(new Mace());
								break;
							case 7:
								result = m_Player->AddWeapon(new GreatMace());
								break;
							case 8:
								result = m_Player->AddWeapon(new Katana());
								break;
							case 9:
								result = m_Player->AddWeapon(new GreatSword());
								break;
							case 10:
								result = m_Player->AddWeapon(new ColossalSword());
								break;
							case 11:
								result = m_Player->AddWeapon(new GoldenSword());
								break;
							case 12:
								result = m_Player->AddWeapon(new ColossalGoldenSword());
								break;
							case 13:
								result = m_Player->AddWeapon(new GreatAxe());
								break;
							case 14:
								result = m_Player->AddWeapon(new Spear());
								break;
							case 15:
								result = m_Player->AddWeapon(new Bow());
								break;
							case 16:
								result = m_Player->AddWeapon(new HealthPotion());
								break;
							case 17:
								result = m_Player->AddWeapon(new BigHealthPotion());
								break;
							case 18:
								result = m_Player->AddWeapon(new DamagePotion());
								break;
							case 19:
								result = m_Player->AddWeapon(new BigDamagePotion());
								break;
							default:
								break;
							}
							if (result)
							{
								m_Player->SetCoin(m_Player->GetCoin() - m_WeaponsCost[index]);
								m_IsOpen = false;
							}
						}
					}
					m_JoystickPressed = false;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_MousePressd)
				{
					m_MousePressd = true;
				}
				else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_MousePressd)
				{
					int index = j * 4 + i;
					if (index >= 0 && index < 20)
					{
						bool result = false;
						if (m_Player->GetCoin() >= m_WeaponsCost[index])
						{
							switch (index)
							{
							case 0:
								result = m_Player->AddWeapon(new Knife());
								break;
							case 1:
								result = m_Player->AddWeapon(new RustySword());
								break;
							case 2:
								result = m_Player->AddWeapon(new Sword());
								break;
							case 3:
								result = m_Player->AddWeapon(new MagicSword());
								break;
							case 4:
								result = m_Player->AddWeapon(new GreatHammer());
								break;
							case 5:
								result = m_Player->AddWeapon(new Hammer());
								break;
							case 6:
								result = m_Player->AddWeapon(new Mace());
								break;
							case 7:
								result = m_Player->AddWeapon(new GreatMace());
								break;
							case 8:
								result = m_Player->AddWeapon(new Katana());
								break;
							case 9:
								result = m_Player->AddWeapon(new GreatSword());
								break;
							case 10:
								result = m_Player->AddWeapon(new ColossalSword());
								break;
							case 11:
								result = m_Player->AddWeapon(new GoldenSword());
								break;
							case 12:
								result = m_Player->AddWeapon(new ColossalGoldenSword());
								break;
							case 13:
								result = m_Player->AddWeapon(new GreatAxe());
								break;
							case 14:
								result = m_Player->AddWeapon(new Spear());
								break;
							case 15:
								result = m_Player->AddWeapon(new Bow());
								break;
							case 16:
								result = m_Player->AddWeapon(new HealthPotion());
								break;
							case 17:
								result = m_Player->AddWeapon(new BigHealthPotion());
								break;
							case 18:
								result = m_Player->AddWeapon(new DamagePotion());
								break;
							case 19:
								result = m_Player->AddWeapon(new BigDamagePotion());
								break;
							default:
								break;
							}
							if (result)
							{
								m_Player->SetCoin(m_Player->GetCoin() - m_WeaponsCost[index]);
								m_IsOpen = false;
							}
						}
					}
					m_MousePressd = false;
				}
				target.draw(m_SelectedWeaponFrame);
			}
		}
		sf::View c = target.getView();
		sf::View v({ 0.f, 0.f, 1280.f, 720.f });
		target.setView(v);
		target.draw(m_ShopText);
		target.setView(c);
	}
}