#pragma once
#include "Menu.h"
#include "UI/Components/Button.h"

class PauseMenu : public Menu
{
public:

	PauseMenu();
	~PauseMenu();

	// Inherited via Menu
	void Init(const TextureManager& textureManager) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

	void Resume(bool& pauseFlag);

private:

	sf::RectangleShape m_BackGround;

	sf::Sprite m_Frame;
	Button m_ResumeButton;
	Button m_MenuButton;
};

