#include "pch.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu()
	: Menu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init(const TextureManager& textureManager)
{
	m_BackGround.setPosition(0.f, 0.f);
	m_BackGround.setSize(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT));
	m_BackGround.setFillColor(sf::Color(0.f, 0.f, 0.f, 128.f));

	m_Frame.setTexture(textureManager.GetTilesetTexture());
	m_Frame.setTextureRect({ 946, 318, 78, 76 });
	m_Frame.setPosition(89.f, 37.f);
	m_ResumeButton.Init(textureManager, { 773, 291, 52, 22 }, { 102.f, 48.f });
	m_MenuButton.Init(textureManager, { 776, 315, 45, 22 }, { 105.5f, 80.f });
}

void PauseMenu::Update(StateID& currentState, float dt)
{
	if (m_MenuButton.isClicked())
		currentState = StateID::StartMenuState;
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(m_BackGround);

	sf::View prevView = target.getView();
	sf::View zoom({ 0.f, 0.f, WIN_WIDTH / 5.f, WIN_HEIGHT / 5.f });
	target.setView(zoom);

	target.draw(m_Frame);
	m_ResumeButton.Render(target);
	m_MenuButton.Render(target);

	target.setView(prevView);
}

void PauseMenu::Resume(bool& pauseFlag)
{
	if (m_ResumeButton.isClicked())
		pauseFlag = false;
}
