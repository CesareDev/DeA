#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Init()
{
    m_TilesetTexture.loadFromFile("../res/map/tileset.png");
    m_Font.loadFromFile("../res/ico-font/DungeonFont.ttf");
    m_CursorImg.loadFromFile("../res/ico-font/cursor.png");
    m_Icon.loadFromFile("../res/ico-font/icon.png");

    m_ClickSoundBuffer.loadFromFile("../res/sound-music/click.wav");
    m_ClickSound.setBuffer(m_ClickSoundBuffer);
    m_GameTitleSoundBuffer.loadFromFile("../res/sound-music/gametitle.wav");
    m_GameTitleSound.setBuffer(m_GameTitleSoundBuffer);
    m_GameOverSoundBuffer.loadFromFile("../res/sound-music/gameover.wav");
    m_GameOverSound.setBuffer(m_GameOverSoundBuffer);
    m_DamageSoundBuffer.loadFromFile("../res/sound-music/damage.wav");
    m_DamageSound.setBuffer(m_DamageSoundBuffer);
    m_PlayerDamageSoundBuffer.loadFromFile("../res/sound-music/playerdamage.wav");
    m_PlayerDamageSound.setBuffer(m_PlayerDamageSoundBuffer);
    m_MainMenuMusic.openFromFile("../res/sound-music/menumusic.wav");
    m_MainMenuMusic.setLoop(true);

    m_GameTitleSound.setVolume(GLOBAL::MUSIC_VOLUME);
    m_GameOverSound.setVolume(GLOBAL::MUSIC_VOLUME);
    m_MainMenuMusic.setVolume(GLOBAL::MUSIC_VOLUME);
    m_ClickSound.setVolume(GLOBAL::SOUND_VOLUME);
    m_DamageSound.setVolume(GLOBAL::SOUND_VOLUME);
    m_PlayerDamageSound.setVolume(GLOBAL::SOUND_VOLUME);

    MUSIC::GAME_TITLE_SOUND = &m_GameTitleSound;
    MUSIC::GAME_OVER_SOUND = &m_GameOverSound;
    MUSIC::MAIN_MENU_MUSIC = &m_MainMenuMusic;
    MUSIC::CLICK_SOUND = &m_ClickSound;
    MUSIC::DAMAGE_SOUND = &m_DamageSound;
    MUSIC::PLAYER_DAMAGE_SOUND = &m_PlayerDamageSound;
}

const sf::Texture& ResourceManager::GetTilesetTexture() const
{
    return m_TilesetTexture;
}

const sf::Font& ResourceManager::GetFont() const
{
    return m_Font;
}

const sf::Image& ResourceManager::GetCursoImg() const
{
    return m_CursorImg;
}

const sf::Image& ResourceManager::GetIcon() const
{
    return m_Icon;
}