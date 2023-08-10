#pragma once
#include "Core/ResourceManager.h"
#include "Core/Camera.h"
#include "Effects/Transition.h"
#include "UI/Components/LevelLabel.h"
#include "Hud/Hud.h"
#include "LevelID.h"

class Level
{
public:

	Level();
	virtual ~Level();

	virtual bool OnEnter(float dt) = 0;
	virtual bool OnExit(float dt) = 0;
	virtual void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, unsigned int entranceIndex) = 0;
	virtual void Update(StateID& currentState, LevelID& currentLevel, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

protected:

	Camera m_Camera;
	Transition m_Transition;
	LevelLabel m_Label;
	sf::TileMap m_Map;
	sf::DynamicQuadTree<Entity>* m_Tree;
	Weapon* m_Weapon; //Pointer to player's weapon because it needs to be rendered on top of the map
};