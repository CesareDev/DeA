#include "pch.h"
#include "WinState.h"

WinState::WinState()
{
}

WinState::~WinState()
{
}

void WinState::Init(const ResourceManager& resourceManager)
{
	m_Transition.Init(resourceManager);

	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(200)).setSmooth(false);
	m_TheEndText.setFont(font);
	m_TheEndText.setCharacterSize(200);
	m_TheEndText.setColor(sf::Color::White);
	m_TheEndText.setString("The End");

	int x = 640 - int(m_TheEndText.getGlobalBounds().width / 2.f);
	int y = 360 - int(m_TheEndText.getGlobalBounds().height);

	m_TheEndText.setPosition({ (float)x, (float)y });

	if (MUSIC::MAIN_MUSIC->getStatus() == sf::SoundSource::Playing)
		MUSIC::MAIN_MUSIC->stop();
	MUSIC::WIN_SOUND->play();
}

bool WinState::OnEnter(float dt)
{
	return m_Transition.FadeIn(dt);
}

bool WinState::OnExit(float dt)
{
	return m_Transition.FadeOut(dt);
}

void WinState::Update(StateID& currentState, float dt)
{
	m_ElapsedTime += dt;
	if (m_ElapsedTime > 4.f)
	{
		SAVE::SAVE_MANAGER.DeleteSave(SAVE::SAVE_MANAGER.GetSaveIndex());
		currentState = StateID::SelectModeState;
	}
}

void WinState::Render(sf::RenderTarget& target)
{
	sf::View v({ 0.f, 0.f, 1280.f, 720.f });
	target.setView(v);
	target.draw(m_TheEndText);
	m_Transition.Render(target);
}

StateID WinState::GetStateID() const
{
	return StateID::WinState;
}
