#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"

class UndeadsBoss : public Level
{
public:

	UndeadsBoss();
	~UndeadsBoss();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
};

