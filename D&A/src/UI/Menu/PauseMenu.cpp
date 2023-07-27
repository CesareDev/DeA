#include "pch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu()
	: Menu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init(const ResourceManager& resourceManager)
{
	m_BackGround.setPosition(0.f, 0.f);
	m_BackGround.setSize(sf::Vector2f(GLOBAL::WIN_WIDTH, GLOBAL::WIN_HEIGHT));
	m_BackGround.setFillColor(sf::Color(0.f, 0.f, 0.f, 128.f));

	m_Frame.setTexture(resourceManager.GetTilesetTexture());
	m_Frame.setTextureRect({ 946, 318, 78, 76 });
	m_Frame.setPosition(89.f, 37.f);
	m_ResumeButton.Init(resourceManager, { 773, 291, 52, 22 }, { 102.f, 48.f });
	m_MenuButton.Init(resourceManager, { 776, 315, 45, 22 }, { 105.5f, 80.f });
}

void PauseMenu::Update(StateID& currentState, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !m_Pause)
		m_Pause = true;
	else if (m_ResumeButton.isClicked())
		m_Pause = false;
	else if (m_MenuButton.isClicked())
		currentState = StateID::StartMenuState;
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	if (m_Pause)
	{
		target.draw(m_BackGround);

		sf::View prevView = target.getView();
		sf::View zoom({ 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });
		target.setView(zoom);

		target.draw(m_Frame);
		m_ResumeButton.Render(target);
		m_MenuButton.Render(target);

		target.setView(prevView);
	}
}

bool PauseMenu::IsPaused() const
{
	return m_Pause;
}
