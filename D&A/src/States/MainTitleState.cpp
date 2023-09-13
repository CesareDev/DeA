#include "pch.h"
#include "MainTitleState.h"

MainTitleState::MainTitleState()
{
}

MainTitleState::~MainTitleState()
{
}

void MainTitleState::Init(const ResourceManager& resourceManager)
{
	m_Transition.Init(resourceManager);
	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(150)).setSmooth(false);
	m_Title.setFont(font);
	m_Title.setCharacterSize(150);
	m_Title.setString("Dungeons&Arena");
	int x = (GLOBAL::WIN_WIDTH / 2) - (m_Title.getGlobalBounds().width / 2);
	int y = (GLOBAL::WIN_HEIGHT / 2) - m_Title.getGlobalBounds().height;
	m_Title.setPosition(x, y);


	const_cast<sf::Texture&>(font.getTexture(30)).setSmooth(false);
	m_MusicCredit.setFont(font);
	m_MusicCredit.setString("Music by Marllon Silva (xDeviruchi)\nSound by ChipTone by SFBGames");
	m_MusicCredit.setCharacterSize(30);
	int cx = GLOBAL::WIN_WIDTH - m_MusicCredit.getGlobalBounds().width - 40.f;
	int cy = GLOBAL::WIN_HEIGHT- m_MusicCredit.getGlobalBounds().height - 40.f;
	m_MusicCredit.setPosition(cx, cy);

	MUSIC::GAME_TITLE_SOUND->play();
}

bool MainTitleState::OnEnter(float dt)
{
    return m_Transition.FadeIn(dt, 3.f);
}

bool MainTitleState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt);
}

void MainTitleState::Update(StateID& currentState, float dt)
{
	currentState = StateID::StartMenuState;
}

void MainTitleState::Render(sf::RenderTarget& target)
{
	target.draw(m_Title);
	target.draw(m_MusicCredit);
	m_Transition.Render(target);
}

StateID MainTitleState::GetStateID() const
{
    return StateID::MainTitleState;
}
