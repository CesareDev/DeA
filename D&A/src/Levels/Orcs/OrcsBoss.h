#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Orcs/OrcBoss.h"

class OrcsBoss : public Level
{
public:

	OrcsBoss();
	~OrcsBoss();

	// Inherited via Level
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	LevelID GetId() const override;

private:

	Ladder m_Ladder0;
};

