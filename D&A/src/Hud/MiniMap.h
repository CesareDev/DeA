#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Other/Player.h"

class MiniMap
{
public:

	MiniMap();
	~MiniMap();

	void Init(const ResourceManager& resourceManager, const sf::TileMap& map, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	sf::View m_StaticCamera;

	const Player* m_Player;
	const sf::TileMap* m_TileMap;
	sf::Vector2u m_TileSize;
	sf::Vector2u m_MapSizeInTile;

	std::vector<sf::Vertex> m_Map;
	sf::RenderTexture m_RenderTexture;
	sf::Sprite m_Sprite;
	sf::RenderStates m_States;

	sf::CircleShape m_PlayerPos;
	sf::View m_MiniCamera;
};

