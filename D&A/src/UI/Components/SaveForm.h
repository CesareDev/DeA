#pragma once
#include "Core/ResourceManager.h"

class SaveForm : public sf::Sprite
{
public:
	
	SaveForm();
	~SaveForm();

	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position, unsigned int saveNumber);
	bool isClicked();
	void Render(sf::RenderTarget& target);

	void Move(float offsetX, float offsetY);
	const sf::Vector2f& GetPosition();
	void SetPosition(float x, float y);
	const sf::Text& GetText();

private:

	bool m_Clicked = false;
	bool m_Pressed = false;
	sf::Vector2f m_Position;
	sf::IntRect m_TextureRect;

	sf::Vector2f m_TextPosition;
	sf::Text m_Text;
};
