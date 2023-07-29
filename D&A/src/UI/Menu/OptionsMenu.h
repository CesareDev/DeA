#pragma once
#include "Menu.h"
#include "Core/Camera.h"
#include "UI/Components/Button.h"
#include "UI/Components/ScrollBar.h"
#include "UI/Components/CheckBox.h"

class OptionsMenu : public Menu
{
public:

	OptionsMenu();
	~OptionsMenu();

	// Inherited via Menu
	void Init(const ResourceManager& resourceManager) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Camera m_StaticCamera;

	sf::Text m_Title;
	sf::Text m_MusicText;
	sf::Text m_SoundText;
	sf::Text m_FullScreenText;
	sf::Sprite m_JoystickIcon;
	sf::Text m_MusicValue;
	sf::Text m_SoundValue;

	Button m_BackButton;
	ScrollBar m_MusicScrollBar;
	ScrollBar m_SoundScrollBar;
	CheckBox m_FSCheckBox;
	CheckBox m_JoystickCheckBox;

	std::vector<sf::Sprite> m_Border;
	sf::SpriteBatch m_Batch;
};