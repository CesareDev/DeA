#pragma once
#include "Core/ResourceManager.h"
#include "Core/Camera.h"
#include "Effects/Transition.h"
#include "UI/Components/LevelLabel.h"
#include "Hud/Hud.h"
#include "Entities/Characters/Player.h"
#include "LevelID.h"

class Level
{
public:

	Level();
	virtual ~Level();

	virtual bool OnEnter(float dt) = 0;
	virtual bool OnExit(float dt) = 0;
	virtual void Init(const ResourceManager& resourceManager, Player* player, unsigned int entranceIndex) = 0;
	virtual void Update(StateID& currentState, LevelID& currentLevel, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

protected:

	Camera m_Camera;
	Transition m_Transition;
	Player* m_Player;
	LevelLabel m_Label;
	Hud m_Hud;
	sf::TileMap m_Map;
	sf::DynamicQuadTree<Entity> m_Tree;
};