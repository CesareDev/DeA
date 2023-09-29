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
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	LevelID GetId() const override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;
};

