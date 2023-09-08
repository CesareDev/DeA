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
	m_ShopText.setString("Shop (Right Button to Buy)");
	m_ShopText.setOutlineColor(sf::Color::Black);
	m_ShopText.setOutlineThickness(4.f);
	m_ShopText.setPosition(999.5 - m_ShopText.getGlobalBounds().width / 2.f, 370.f - m_ShopText.getGlobalBounds().height - 8.f);
}

void Shop::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !m_Pressed)
	{
		m_Pressed = true;
		if (m_IsOpen)
			m_IsOpen = false;
		else
			m_IsOpen = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_Pressed)
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
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_MousePressd)
				{
					m_MousePressd = true;
				}
				else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_MousePressd)
				{
					int index = j * 4 + i;
					switch (index)
					{
					case 0:
						m_Player->AddWeapon(new Knife());
						break;
					case 1:
						m_Player->AddWeapon(new RustySword());
						break;
					case 2:
						m_Player->AddWeapon(new Sword());
						break;
					case 3:
						m_Player->AddWeapon(new MagicSword());
						break;
					case 4:
						m_Player->AddWeapon(new GreatHammer());
						break;
					case 5:
						m_Player->AddWeapon(new Hammer());
						break;
					case 6:
						m_Player->AddWeapon(new Mace());
						break;
					case 7:
						m_Player->AddWeapon(new GreatMace());
						break;
					case 8:
						m_Player->AddWeapon(new Katana());
						break;
					case 9:
						m_Player->AddWeapon(new GreatSword());
						break;
					case 10:
						m_Player->AddWeapon(new ColossalSword());
						break;
					case 11:
						m_Player->AddWeapon(new GoldenSword());
						break;
					case 12:
						m_Player->AddWeapon(new ColossalGoldenSword());
						break;
					case 13:
						m_Player->AddWeapon(new GreatAxe());
						break;
					case 14:
						m_Player->AddWeapon(new Spear());
						break;
					case 15:
						m_Player->AddWeapon(new Bow());
						break;
					case 16:
						m_Player->AddWeapon(new HealthPotion());
						break;
					case 17:
						m_Player->AddWeapon(new BigHealthPotion());
						break;
					case 18:
						m_Player->AddWeapon(new DamagePotion());
						break;
					case 19:
						m_Player->AddWeapon(new BigDamagePotion());
						break;
					default:
						break;
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
