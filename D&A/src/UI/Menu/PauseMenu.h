#pragma once
#include "Menu.h"
#include "UI/Components/Button.h"

class PauseMenu : public Menu
{
public:

	PauseMenu();
	~PauseMenu();

	// Inherited via Menu
	void Init(const ResourceManager& resourceManager) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

	bool IsPaused() const;

private:

	bool m_Pause = false;

	sf::RectangleShape m_BackGround;

	sf::Sprite m_Frame;
	Button m_ResumeButton;
	Button m_MenuButton;
};

