#include "pch.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init(const ResourceManager& resourceManager, const sf::TileMap& map, const Player& player)
{
	m_Player = &player;
	m_TileMap = &map;
	m_States.blendMode = sf::BlendNone;

	unsigned int tw = map.getTileSize().x;
	unsigned int th = map.getTileSize().y;
	unsigned int w = map.getMapSize().x / tw;
	unsigned int h = map.getMapSize().y / th;

	m_MapSizeInTile = { w, h };
	m_TileSize = { tw, th };

	m_RenderTexture.create(512, 288);

	m_Map.resize(w * h * 4);
	for (unsigned int j = 0; j < h; ++j)
	{
		for (unsigned int i = 0; i < w; ++i)
		{
			sf::Vertex* v = &m_Map[(j * w + i) * 4];
			sf::Vector2f pos = sf::Vector2f(i * tw, j * th);
			v[0].position = pos;
			v[1].position = pos + sf::Vector2f(tw, 0.f);
			v[2].position = pos + sf::Vector2f(tw, th);
			v[3].position = pos + sf::Vector2f(0.f, th);
			if (map.isCellTile(sf::Vector2i(i, j)) && !map.isCellWall(sf::Vector2i(i, j)))
			{
				v[0].color = sf::Color(238, 142, 46);
				v[1].color = sf::Color(238, 142, 46);
				v[2].color = sf::Color(238, 142, 46);
				v[3].color = sf::Color(238, 142, 46);
			}
			else
			{
				v[0].color = sf::Color::Transparent;
				v[1].color = sf::Color::Transparent;
				v[2].color = sf::Color::Transparent;
				v[3].color = sf::Color::Transparent;
			}
		}
	}

	m_StaticCamera.reset({ 0.f, 0.f, 3840.f, 2160.f });
	m_MiniCamera.setCenter(m_Player->GetCenter());
	m_MiniCamera.setSize(256.f, 144.f);

	m_PlayerPos.setFillColor(sf::Color(253, 247, 237));
	m_PlayerPos.setPosition(m_Player->getPosition());
	m_PlayerPos.setRadius(8.f);
	m_Sprite.setPosition(m_StaticCamera.getSize().x - m_RenderTexture.getSize().x - 120, 120.f);
}

void MiniMap::Update(float dt)
{
	m_PlayerPos.setPosition(m_Player->getPosition());
	m_MiniCamera.setCenter(m_Player->GetCenter());
}

void MiniMap::Render(sf::RenderTarget& target)
{
	sf::Vector2u tl;
	sf::Vector2u br;
	tl.x = std::max(int((m_MiniCamera.getCenter().x - (m_MiniCamera.getSize().x / 2.f)) / m_TileSize.x), 0);
	tl.y = std::max(int((m_MiniCamera.getCenter().y - (m_MiniCamera.getSize().y / 2.f)) / m_TileSize.y), 0);
	br.x = std::min(int((m_MiniCamera.getCenter().x + (m_MiniCamera.getSize().x / 2.f) + m_TileSize.x) / m_TileSize.x), (int)m_MapSizeInTile.x);
	br.y = std::min(int((m_MiniCamera.getCenter().y + (m_MiniCamera.getSize().y / 2.f) + m_TileSize.y) / m_TileSize.y), (int)m_MapSizeInTile.y);
	if (br.x > tl.x && br.y > tl.y)
	{
		m_RenderTexture.clear(sf::Color::Transparent);
		std::vector<sf::Vertex> drawBuffer((br.x - tl.x) * (br.y - tl.y) * 4);
		size_t offset = 0;

		sf::Vector2u tile;
		for (tile.y = tl.y; tile.y < br.y; ++tile.y)
		{
			for (tile.x = tl.x; tile.x < br.x; ++tile.x)
			{
				sf::Vertex* visibleTile = &m_Map[(tile.y * m_MapSizeInTile.x + tile.x) * 4];

				drawBuffer[offset + 0].position = visibleTile[0].position;
				drawBuffer[offset + 0].color = visibleTile[0].color;

				drawBuffer[offset + 1].position = visibleTile[1].position;
				drawBuffer[offset + 1].color = visibleTile[1].color;

				drawBuffer[offset + 2].position = visibleTile[2].position;
				drawBuffer[offset + 2].color = visibleTile[2].color;

				drawBuffer[offset + 3].position = visibleTile[3].position;
				drawBuffer[offset + 3].color = visibleTile[3].color;
				offset += 4;
			}
		}

		m_RenderTexture.setView(m_MiniCamera);
		m_RenderTexture.draw(drawBuffer.data(), drawBuffer.size(), sf::Quads, m_States);
		m_RenderTexture.draw(m_PlayerPos);
		m_RenderTexture.display();
		m_Sprite.setTexture(m_RenderTexture.getTexture(), true);
		target.setView(m_StaticCamera);
		target.draw(m_Sprite);
	}
}