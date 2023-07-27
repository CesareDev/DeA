#include "pch.h"
#include "TextureManager.h"

void TextureManager::Init()
{
    m_TilesetTexture.loadFromFile("../res/map/tileset.png");
    m_Font.loadFromFile("../res/DungeonFont.ttf");
}

const sf::Texture& TextureManager::GetTilesetTexture() const 
{
    return m_TilesetTexture;
}

const sf::Font& TextureManager::GetFont() const
{
    return m_Font;
}
