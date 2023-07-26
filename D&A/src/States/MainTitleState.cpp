#include "pch.h"
#include "MainTitleState.h"

MainTitleState::MainTitleState()
{
}

MainTitleState::~MainTitleState()
{
}

void MainTitleState::Init(const TextureManager& textureManger)
{
	m_Transition.Init(textureManger);
	const auto& font = textureManger.GetFont();
	const_cast<sf::Texture&>(font.getTexture(150)).setSmooth(false);
	m_Title.setFont(font);
	m_Title.setCharacterSize(150);
	m_Title.setString("Dungeons&Arena");
	int x = (GLOBAL::WIN_WIDTH / 2) - (m_Title.getGlobalBounds().width / 2);
	int y = (GLOBAL::WIN_HEIGHT / 2) - m_Title.getGlobalBounds().height;
	m_Title.setPosition(x, y);
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
	m_Transition.Render(target);
}

StateID MainTitleState::GetStateID() const
{
    return StateID::MainTitleState;
}
