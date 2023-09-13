#pragma once
#include "Core/ResourceManager.h"
#include "Core/Camera.h"
#include "Effects/Transition.h"
#include "Entities/Characters/Other/Player.h"
#include "Hud/Hud.h"
#include "Entities/Weapons/Weapon.h"
#include "UI/Components/LevelLabel.h"
#include "LevelID.h"

class Level
{
public:

	Level();
	virtual ~Level();

	virtual bool OnEnter(float dt) = 0;
	virtual bool OnExit(float dt) = 0;
	virtual void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) = 0;
	virtual void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

protected:

	Camera m_Camera;
	Transition m_Transition;
	LevelLabel m_Label;
	sf::TileMap m_Map;
	sf::DynamicQuadTree<Entity>* m_Tree;
	sf::AStar m_AStar;
	Hud m_Hud;

	Player* m_Player;
};