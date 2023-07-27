#pragma once
#include "Menu.h"
#include "Core/Camera.h"
#include "UI/Components/Button.h"

class StartMenu : public Menu
{
public:

	StartMenu();
	~StartMenu();

	// Inherited via Menu
	void Init(const ResourceManager& resourceManager) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Camera m_StaticCamera;

	sf::Sprite m_Frame;
	Button m_PlayButton;
	Button m_OptionsButton;
	Button m_ExitButton;

	std::vector<sf::Sprite> m_Border;
	sf::SpriteBatch m_Batch;
};

