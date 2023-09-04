#pragma once
#include "Inventory.h"
#include "MiniMap.h"
#include "Entities/Characters/Player.h"

class Hud
{
public:

	Hud();
	~Hud();

	void Init(const ResourceManager& resourceManager, const Player& player, const sf::TileMap& map);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	const Player* m_Player;
	
	sf::View m_StaticCamera;
	sf::Sprite m_BarFrame;
	sf::Sprite m_HealthTail;
	sf::RectangleShape m_HealthBar;

	sf::Text m_CoinQuantity;

	Inventory m_Inv;
	MiniMap m_MiniMap;
};