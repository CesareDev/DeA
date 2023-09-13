#pragma once

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();
	
	void Init();

	const sf::Texture& GetTilesetTexture() const;
	const sf::Font& GetFont() const;
	const sf::Image& GetCursoImg() const;
	const sf::Image& GetIcon() const;

private:

	sf::Texture m_TilesetTexture;
	sf::Font m_Font;
	sf::Image m_CursorImg;
	sf::Image m_Icon;

	sf::SoundBuffer m_ClickSoundBuffer;
	sf::Sound m_ClickSound;

	sf::SoundBuffer m_GameTitleSoundBuffer;
	sf::Sound m_GameTitleSound;

	sf::SoundBuffer m_GameOverSoundBuffer;
	sf::Sound m_GameOverSound;

	sf::SoundBuffer m_DamageSoundBuffer;
	sf::Sound m_DamageSound;

	sf::SoundBuffer m_PlayerDamageSoundBuffer;
	sf::Sound m_PlayerDamageSound;

	sf::SoundBuffer m_AttackSoundBuffer;
	sf::Sound m_AttackSound;

	sf::SoundBuffer m_RegenSoundBuffer;
	sf::Sound m_RegenSound;


	sf::Music m_MainMenuMusic;
};