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
	unsigned int tw = map.getTileSize().x;
	unsigned int th = map.getTileSize().y;
	unsigned int w = map.getMapSize().x / tw;
	unsigned int h = map.getMapSize().y / th;

	m_RenderTexture.create(map.getMapSize().x, map.getMapSize().y);

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

	m_StaticCamera.reset({ 0.f, 0.f, 3840, 2160 });

	m_PlayerPos.setFillColor(sf::Color(253, 247, 237));
	m_PlayerPos.setPosition(m_Player->getPosition());
	m_PlayerPos.setRadius(8.f);
	m_Sprite.setPosition(3840.f - map.getMapSize().x - 120.f, 120.f);
}

void MiniMap::Update(float dt)
{
	m_PlayerPos.setPosition(m_Player->getPosition());
}

void MiniMap::Render(sf::RenderTarget& target)
{
	m_RenderTexture.clear();
	m_States.blendMode = sf::BlendNone;
	m_RenderTexture.draw(m_Map.data(), m_Map.size(), sf::Quads, m_States);
	m_RenderTexture.draw(m_PlayerPos);
	m_RenderTexture.display();

	m_Sprite.setTexture(m_RenderTexture.getTexture());
	target.setView(m_StaticCamera);
	target.draw(m_Sprite);
}