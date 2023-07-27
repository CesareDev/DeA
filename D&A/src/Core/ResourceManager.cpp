#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Init()
{
    m_TilesetTexture.loadFromFile("../res/map/tileset.png");
    m_Font.loadFromFile("../res/DungeonFont.ttf");
    m_CursorImg.loadFromFile("../res/cursor64.png");
    m_Icon.loadFromFile("../res/icon.png");
}

const sf::Texture& ResourceManager::GetTilesetTexture() const
{
    return m_TilesetTexture;
}

const sf::Font& ResourceManager::GetFont() const
{
    return m_Font;
}

const sf::Image& ResourceManager::GetCursoImg() const
{
    return m_CursorImg;
}

const sf::Image& ResourceManager::GetIcon() const
{
    return m_Icon;
}
