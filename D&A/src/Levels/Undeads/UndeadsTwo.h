#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Undeads/SmallUndead.h"
#include "Entities/Characters/Undeads/HalfUndead.h"
#include "Entities/Characters/Undeads/Undead.h"
#include "Entities/Characters/Undeads/UndeadSlime.h"

class UndeadsTwo : public Level
{
public:

	UndeadsTwo();
	~UndeadsTwo();

	// Inherited via Level
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	LevelID GetId() const override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;
};

