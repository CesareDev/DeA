#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Characters/Orcs/SmallOrc.h"
#include "Entities/Characters/Orcs/Orc.h"

class OrcsOne : public Level
{
public:

	OrcsOne();
	~OrcsOne();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder0;
	Ladder m_Ladder1;

	SmallOrc m_SmallOrc0;
	SmallOrc m_SmallOrc1;
	SmallOrc m_SmallOrc2;
	Orc m_Orc0;
	Orc m_Orc1;
};