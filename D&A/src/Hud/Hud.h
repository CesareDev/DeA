#pragma once
#include "Core/ResourceManager.h"
#include "Inventory.h"
#include "Entities/Characters/Player.h"

class Hud
{
public:

	Hud();
	~Hud();

	void Init(const ResourceManager& resourceManager, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	const Player* m_Player;
	
	sf::View m_StaticCamera;
	sf::Sprite m_BarFrame;
	sf::Sprite m_HealthTail;
	sf::Sprite m_ManaTail;
	sf::RectangleShape m_HealthBar;
	sf::RectangleShape m_ManaBar;

	sf::Text m_CoinQuantity;

	Inventory m_Inv;
};