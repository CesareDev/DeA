#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Player.h"

class Inventory
{
public:

	Inventory();
	~Inventory();

	void Init(const ResourceManager& resourceManager, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	Player* m_Player;

	sf::Sprite m_Inv;
	sf::Vector2f m_IconPos[8];
	unsigned int m_CurrentIndex;
	sf::RectangleShape m_CurrentIconFrame;

	std::vector<sf::Vertex> m_Icons;
	sf::RenderStates m_States;
};

