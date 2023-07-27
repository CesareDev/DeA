#pragma once

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();
	
	void Init();

	const sf::Texture& GetTilesetTexture() const;
	const sf::Font& GetFont() const;
	const sf::Image& GetCursoImg() const;
	const sf::Image& GetIcon() const;

private:

	sf::Texture m_TilesetTexture;
	sf::Font m_Font;
	sf::Image m_CursorImg;
	sf::Image m_Icon;
};

