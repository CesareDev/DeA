#pragma once
#include "Core/TextureManager.h"

class CheckBox : public sf::Sprite
{
public:

	CheckBox();
	~CheckBox();

	void Init(const TextureManager& textureManager, const sf::Vector2f& position, bool checked);
	void Update(float dt);
	void Render(sf::RenderTarget& target);
	bool isChecked();
	bool isClicked();

private:

	sf::IntRect m_TextureRect;
	sf::Vector2f m_Position;
	bool m_Checked;
	bool m_Pressed = false;
	bool m_Clicked = false;
};

