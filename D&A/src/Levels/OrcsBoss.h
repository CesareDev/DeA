#pragma once
#include "Level.h"
#include "Entities/Environments/Ladder.h"

#include "Entities/Characters/Orcs/OrcBoss.h"

class OrcsBoss : public Level
{
public:

	OrcsBoss();
	~OrcsBoss();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
	OrcBoss o;
};

