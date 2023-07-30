#pragma once
#include "Level.h"
#include "Entities/Environments/Ladder.h"

class Underground : public Level
{
public:

	Underground();
	~Underground();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
};

