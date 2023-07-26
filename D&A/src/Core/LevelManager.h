#pragma once
#include "Core/TextureManager.h"
#include "Levels/Level.h"
#include "Entities/Player.h"

class LevelManager
{
public:

	LevelManager();
	~LevelManager();

	void Init(const TextureManager& textureManager);
	void Update(StateID& currentState, float dt);
	void Render(sf::RenderTarget& target);
	bool IsChanging();

private:

	void ChangeLevel(float dt);

private:

	const TextureManager* m_TextureManager;

	std::unique_ptr<Level> m_CurrentLevel;
	LevelID m_CurrentLevelId;
	LevelID m_OldState;
	bool m_ChangingLevel;

	Player m_Player;
};

