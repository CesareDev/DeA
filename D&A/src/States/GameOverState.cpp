#include "pch.h"
#include "GameOverState.h"

GameOverState::GameOverState()
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::Init(const ResourceManager& resourceManager)
{
    m_Transition.Init(resourceManager);

	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(200)).setSmooth(false);
	m_GameOverText.setFont(font);
	m_GameOverText.setCharacterSize(200);
	m_GameOverText.setColor(sf::Color::Red);
	m_GameOverText.setString("Game Over");

	int x = 640 - int(m_GameOverText.getGlobalBounds().width / 2.f);
	int y = 360 - int(m_GameOverText.getGlobalBounds().height);

	m_GameOverText.setPosition({ (float)x, (float)y });

	if (MUSIC::MAIN_MENU_MUSIC->getStatus() == sf::SoundSource::Playing)
		MUSIC::MAIN_MENU_MUSIC->stop();
	MUSIC::GAME_OVER_SOUND->play();
}

bool GameOverState::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt);
}

bool GameOverState::OnExit(float dt)
{
    return m_Transition.FadeOut(dt);
}

void GameOverState::Update(StateID& currentState, float dt)
{		
	m_ElapsedTime += dt;
	if (m_ElapsedTime > 2.5f)
		currentState = StateID::SelectModeState;
}

void GameOverState::Render(sf::RenderTarget& target)
{
	sf::View v({ 0.f, 0.f, 1280.f, 720.f });
	target.setView(v);
	target.draw(m_GameOverText);
    m_Transition.Render(target);
}

StateID GameOverState::GetStateID() const
{
    return StateID::GameOverState;
}
