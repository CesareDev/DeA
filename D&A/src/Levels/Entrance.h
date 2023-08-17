#pragma once
#include "Level.h"
#include "Entities/Characters/Slug.h"
#include "Entities/Characters/DemonBoss.h"

class Entrance : public Level
{
public:

	Entrance();
	~Entrance();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Slug slug1;
	Slug slug2;
	DemonBoss demon;
};

