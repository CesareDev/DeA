#include "pch.h"
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::Init(const ResourceManager& resourceManager)
{
	m_StaticCamera.Init({ 0.f, 0.f }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f }, { 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Border.resize(96);
	m_Batch.Create(&resourceManager.GetTilesetTexture());

	for (int i = 0; i < m_Border.size(); ++i)
	{
		m_Border[i].setTexture(resourceManager.GetTilesetTexture());

		if (i == 0)
		{
			m_Border[i].setPosition(i, i);
			m_Border[i].setTextureRect({ 528, 40, 8, 8 });
		}
		else if (i < 31 && i > 0)
		{
			m_Border[i].setPosition(i * 8.f, 0.f);
			m_Border[i].setTextureRect({ 552, 40, 8, 8 });
		}
		else if (i == 31)
		{
			m_Border[i].setPosition(i * 8, 0.f);
			m_Border[i].setTextureRect({ 560, 40, 8, 8 });
		}
		else if (i < 48 && i > 31)
		{
			m_Border[i].setPosition(31 * 8, (i - 31) * 8);
			m_Border[i].setTextureRect({ 560, 48, 8, 8 });
		}
		else if (i == 48)
		{
			m_Border[i].setPosition(31 * 8, (i - 31) * 8);
			m_Border[i].setTextureRect({ 560, 56, 8, 8 });
		}
		else if (i < 79 && i > 48)
		{
			m_Border[i].setPosition((79 - i) * 8, 17 * 8);
			m_Border[i].setTextureRect({ 552, 56, 8, 8 });
		}
		else if (i == 79)
		{
			m_Border[i].setPosition((79 - i) * 8, 17 * 8);
			m_Border[i].setTextureRect({ 528, 56, 8, 8 });
		}
		else if (i > 79)
		{
			m_Border[i].setPosition(0.f, (96 - i) * 8);
			m_Border[i].setTextureRect({ 528, 48, 8, 8 });
		}
	}

	m_BackButton.Init(resourceManager, { 776, 357, 16, 16 }, { 16.f, 16.f });

	const auto& font = resourceManager.GetFont();
	const_cast<sf::Texture&>(font.getTexture(120)).setSmooth(false);
	const_cast<sf::Texture&>(font.getTexture(100)).setSmooth(false);
	const_cast<sf::Texture&>(font.getTexture(80)).setSmooth(false);

	m_Title.setFont(font);
	m_Title.setCharacterSize(120);
	m_Title.setString("Options");
	int x = (GLOBAL::WIN_WIDTH / 2.f) - (m_Title.getGlobalBounds().width / 2.f);
	m_Title.setPosition(x, 60.f);

	m_MusicText.setFont(font);
	m_MusicText.setCharacterSize(100);
	m_MusicText.setPosition(80, 200);
	m_MusicText.setString("Music");

	m_SoundText.setFont(font);
	m_SoundText.setCharacterSize(100);
	m_SoundText.setPosition(80, 320);
	m_SoundText.setString("Sound");

	m_FullScreenText.setFont(font);
	m_FullScreenText.setCharacterSize(100);
	m_FullScreenText.setPosition(80, 440);
	m_FullScreenText.setString("Fullscreen");

	m_JoystickIcon.setTexture(resourceManager.GetTilesetTexture());
	m_JoystickIcon.setPosition(16.f, 114.f);
	m_JoystickIcon.setTextureRect({ 880, 410, 24, 15 });

	float scrollx = ((m_MusicText.getGlobalBounds().left + m_MusicText.getGlobalBounds().width) / 5.f) + 8.f;
	int mscrolly = m_MusicText.getGlobalBounds().top;
	int sscrolly = m_SoundText.getGlobalBounds().top;

	m_MusicScrollBar.Init(resourceManager, { scrollx, mscrolly / 5.f}, &GLOBAL::MUSIC_VOLUME);
	m_SoundScrollBar.Init(resourceManager, { scrollx, sscrolly / 5.f}, &GLOBAL::SOUND_VOLUME);

	m_MusicValue.setFont(font);
	m_MusicValue.setCharacterSize(80);
	m_MusicValue.setString(std::to_string(m_MusicScrollBar.GetValue()));
	m_MusicValue.setPosition(1040, mscrolly);

	m_SoundValue.setFont(font);
	m_SoundValue.setCharacterSize(80);
	m_SoundValue.setString(std::to_string(m_SoundScrollBar.GetValue()));
	m_SoundValue.setPosition(1040, sscrolly);

	float cx = ((m_FullScreenText.getGlobalBounds().left + m_FullScreenText.getGlobalBounds().width) / 5.f) + 8.f;
	float cy = m_FullScreenText.getGlobalBounds().top / 5.f;
	m_FSCheckBox.Init(resourceManager, { cx, cy}, GLOBAL::FULLSCREEN);

	float jx = ((m_JoystickIcon.getPosition().x + m_JoystickIcon.getGlobalBounds().width) + 8.f);
	float jy = m_JoystickIcon.getPosition().y;
	m_JoystickCheckBox.Init(resourceManager, { jx, jy }, GLOBAL::JOYSTICK_AVAILABLE);
}

void OptionsMenu::Update(StateID& currentState, float dt)
{
	if (m_BackButton.isClicked())
		currentState = StateID::StartMenuState;
	m_MusicScrollBar.Update(dt);
	m_SoundScrollBar.Update(dt);
	m_MusicValue.setString(std::to_string(GLOBAL::MUSIC_VOLUME));
	m_SoundValue.setString(std::to_string(GLOBAL::SOUND_VOLUME));

	MUSIC::CLICK_SOUND->setVolume(GLOBAL::SOUND_VOLUME);
	MUSIC::GAME_OVER_SOUND->setVolume(GLOBAL::MUSIC_VOLUME);
	MUSIC::GAME_TITLE_SOUND->setVolume(GLOBAL::MUSIC_VOLUME);
	MUSIC::MAIN_MENU_MUSIC->setVolume(GLOBAL::MUSIC_VOLUME);
	MUSIC::DAMAGE_SOUND->setVolume(GLOBAL::SOUND_VOLUME);
	MUSIC::PLAYER_DAMAGE_SOUND->setVolume(GLOBAL::SOUND_VOLUME);
	MUSIC::ATTACK_SOUND->setVolume(GLOBAL::SOUND_VOLUME);
	MUSIC::REGEN_SOUND->setVolume(GLOBAL::SOUND_VOLUME);
}

void OptionsMenu::Render(sf::RenderTarget& target)
{
	target.setView(m_StaticCamera);

	m_Batch.Begin(96);
	for (const auto& s : m_Border)
		m_Batch.Submit(s);
	m_Batch.Render(target);

	m_BackButton.Render(target);
	m_MusicScrollBar.Render(target);
	m_SoundScrollBar.Render(target);
	m_FSCheckBox.Render(target);
	m_JoystickCheckBox.Render(target);

	sf::View view({ 0.f, 0.f, (float)GLOBAL::WIN_WIDTH, (float)GLOBAL::WIN_HEIGHT });

	target.setView(view);

	target.draw(m_Title);
	target.draw(m_MusicText);
	target.draw(m_MusicValue);
	target.draw(m_SoundText);
	target.draw(m_SoundValue);
	target.draw(m_FullScreenText);

	target.setView(m_StaticCamera);

	target.draw(m_JoystickIcon);

	if (m_FSCheckBox.isClicked())
	{
		if (m_FSCheckBox.isChecked())
		{
			((sf::RenderWindow&)target).create(sf::VideoMode::getFullscreenModes()[0], "D&A", sf::Style::Fullscreen);
			GLOBAL::FULLSCREEN = true;
		}
		else
		{
			((sf::RenderWindow&)target).create(sf::VideoMode(GLOBAL::WIN_WIDTH, GLOBAL::WIN_HEIGHT), "D&A", sf::Style::Default);
			GLOBAL::FULLSCREEN = false;
		}
	}

	GLOBAL::JOYSTICK_AVAILABLE = sf::Joystick::isConnected(0);
	m_JoystickCheckBox.SetChecked(GLOBAL::JOYSTICK_AVAILABLE);
}
