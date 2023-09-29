#pragma once
#include "Levels/Level.h"
#include "Entities/Environments/Ladder.h"
#include "Entities/Environments/Message.h"
#include "Entities/Characters/Other/Princess.h"

class Entrance : public Level
{
public:

	Entrance();
	~Entrance();
	
	// Inherited via Level
	void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) override;
	LevelID GetId() const override;
	
	void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) override;
	void Render(sf::RenderTarget& target) override;

private:

	Ladder m_Ladder1;
	Ladder m_Ladder2;
	Ladder m_Ladder3;
	Ladder m_Ladder4;

	Princess m_Princess;
	Message m_StoryMessage;
	Message m_CommandMessage;
};