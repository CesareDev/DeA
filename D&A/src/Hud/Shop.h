#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Other/Player.h"

class Shop
{
public:

	Shop();
	~Shop();

	void Init(const ResourceManager& resourceManager, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	Player* m_Player;
	bool m_IsOpen = false;
	bool m_Pressed = false;
	int m_SelectedWeaponIndex;

	bool m_MousePressd = false;
	bool m_JoystickPressed = false;

	sf::Sprite m_ItemList;
	sf::Text m_ShopText;
	sf::RectangleShape m_SelectedWeaponFrame;

	unsigned int m_WeaponsCost[20];
};

