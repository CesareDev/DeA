#pragma once

class TextureManager
{
public:
	
	void Init();

	const sf::Texture& GetTilesetTexture() const;
	const sf::Font& GetFont() const;

private:

	sf::Texture m_TilesetTexture;
	sf::Font m_Font;
};

