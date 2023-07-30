#pragma once
#include "Core/ResourceManager.h"
#include "Levels/Level.h"
#include "Entities/Characters/Player.h"

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
	LevelID m_OldState;
	bool m_ChangingLevel;

	Player m_Player;
	sf::DynamicQuadTree<Entity> m_Tree;
};

