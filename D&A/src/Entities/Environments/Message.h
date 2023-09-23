#pragma once
#include "Environment.h"

class Message : public Environment
{
public:

	Message();
	~Message();

	// Inherited via Environment
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

	void SetText(const std::string& text, bool autoRead = false);
	void RenderText(sf::RenderTarget& target);

private:

	bool m_Pressed = false;
	bool m_Clicked = false;
	bool m_Interact = false;
	bool m_AutoRead = false;
	bool m_PlayerCanInteract = false;

	sf::Text m_Text;
	sf::Text m_PressSpaceText;
	sf::RectangleShape m_TextFrame;
};

