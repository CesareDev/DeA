#pragma once
#include "Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Slug.h"

class Hub : public Level
{
public:

	Hub();
	~Hub();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
	Slug slug;
};

