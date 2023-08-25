#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Player.h"

class MiniMap
{
public:

	MiniMap();
	~MiniMap();

	void Init(const ResourceManager& resourceManager, const sf::TileMap& map, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	const Player* m_Player;
	std::vector<sf::Vertex> m_Map;
	sf::RenderTexture m_RenderTexture;
	sf::Sprite m_Sprite;
	sf::CircleShape m_PlayerPos;
	sf::RenderStates m_States;
	sf::View m_StaticCamera;
};

