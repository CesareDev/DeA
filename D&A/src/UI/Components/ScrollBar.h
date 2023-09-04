#pragma once
#include "Core/ResourceManager.h"

class ScrollBar
{
public:

	ScrollBar();
	~ScrollBar();

	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position, unsigned int* value);
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
	bool m_IsDraggable = false;
	unsigned int* m_Value;
};