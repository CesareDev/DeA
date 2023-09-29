#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"

#include "Entities/Characters/Orcs/SmallOrc.h"
#include "Entities/Characters/Orcs/Orc.h"
#include "Entities/Characters/Orcs/MaskedOrc.h"
#include "Entities/Characters/Orcs/TribalOrc.h"

class OrcsTwo : public Level
{
public:

	OrcsTwo();
	~OrcsTwo();

	// Inherited via Level
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	LevelID GetId() const override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;
};

