#pragma once
#include "Core/TextureManager.h"

class Button : public sf::Sprite
{

public:
	Button();
	~Button();

	void Init(const TextureManager& textureManager, const sf::IntRect& textureRect, const sf::Vector2f& position);
	bool isClicked();
	void Move(float offsetX, float offsetY);
	void SetPosition(float x, float y);
	const sf::Vector2f& GetPosition();
	void Render(sf::RenderTarget& target);

private:
	
	bool m_Clicked = false;
	bool m_Pressed = false;
	sf::Vector2f m_Position;
	sf::IntRect m_TextureRect;
};
