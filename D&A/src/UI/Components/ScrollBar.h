#pragma once
#include "Core/TextureManager.h"

class ScrollBar
{
public:

	ScrollBar();
	~ScrollBar();

	void Init(const TextureManager& textureManager, const sf::Vector2f& position, unsigned int* value);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

	unsigned int GetValue();

private:

	sf::Sprite m_Bar;
	sf::Sprite m_Slider;
	sf::RectangleShape m_Progress;

	sf::Vector2f m_SliderPosition;
	sf::IntRect m_SliderTextureRect;
	bool m_Pressed = false;
	unsigned int* m_Value;
};