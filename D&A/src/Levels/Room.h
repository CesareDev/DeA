#pragma once
#include "Level.h"

class Room : public Level
{
public:

	Room();
	~Room();

	// Inherited via Level
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Init(const TextureManager& textureManager, Player* player, unsigned int entranceIndex) override;
	void Update(StateID& currentState, LevelID& currentLevel, float dt) override;
	void Render(sf::RenderTarget& target) override;
};

