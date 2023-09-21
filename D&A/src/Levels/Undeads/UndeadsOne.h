#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Undeads/SmallUndead.h"
#include "Entities/Characters/Undeads/HalfUndead.h"

class UndeadsOne : public Level
{
public:

	UndeadsOne();
	~UndeadsOne();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;

	SmallUndead m_SmallUndead0;
	SmallUndead m_SmallUndead1;
	HalfUndead m_HalfUndead0;
	HalfUndead m_HalfUndead1;
	HalfUndead m_HalfUndead2;
};

