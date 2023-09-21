#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Demons/SmallDemon.h"
#include "Entities/Characters/Demons/HalfDemon.h"
#include "Entities/Characters/Demons/Demon.h"

class DemonsOne : public Level
{
public:

	DemonsOne();
	~DemonsOne();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;

	SmallDemon m_SmallDemons[8];
	SmallDemon m_HalfDemons[10];
	Demon m_Demon0;
	Demon m_Demon1;
	Demon m_Demon2;
};

