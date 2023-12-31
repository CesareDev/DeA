#pragma once
#include "Core/ResourceManager.h"
#include "Levels/Level.h"
#include "Entities/Characters/Other/Player.h"

class LevelManager
{
public:

	LevelManager();
	~LevelManager();

	void Init(const ResourceManager& resourceManager);
	void Update(StateID& currentState, float dt);
	void Render(sf::RenderTarget& target);
	bool IsChanging();

private:

	void ChangeLevel(float dt);

private:

	const ResourceManager* m_ResourceManager;

	std::unique_ptr<Level> m_CurrentLevel;
	LevelID m_CurrentLevelId;
	LevelID m_OldLevelId;
	int m_EntranceIndex;
	bool m_ChangingLevel;
	bool m_Initialized;

	Player m_Player;
	sf::DynamicQuadTree<Entity> m_Tree;
};

