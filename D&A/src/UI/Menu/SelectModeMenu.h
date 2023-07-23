#pragma once
#include "Menu.h"
#include "Core/Camera.h"
#include "UI/Components/Button.h"
#include "UI/Components/SaveForm.h"

class SelectModeMenu : public Menu
{
public:

	SelectModeMenu();
	~SelectModeMenu();

	// Inherited via Menu
	void Init(const TextureManager& textureManager) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	void MoveButton(StateID& currentState, float dt);
	float Lerp(float a, float b, float f);

	Camera m_StaticCamera;

	sf::Sprite m_Frame;
	Button m_BackButton;
	Button m_StoryButton;
	Button m_ArenaButton;

	SaveForm m_Save1;
	SaveForm m_Save2;
	SaveForm m_Save3;
	sf::Color m_FadeColor;

	bool m_SelectSave = false;
	bool m_Animation = false;
	float m_DurationTime = 0.f;
	std::vector<sf::Sprite> m_Border;
	sf::SpriteBatch m_Batch;
};

