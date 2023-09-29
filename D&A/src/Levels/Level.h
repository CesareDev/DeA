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

	virtual bool OnEnter(float dt);
	virtual bool OnExit(float dt);
	virtual void Init(const ResourceManager& resourceManager, sf::DynamicQuadTree<Entity>& tree, Player& player, int entranceIndex) = 0;
	virtual LevelID GetId() const = 0;

	virtual void Update(StateID& currentState, LevelID& currentLevel, int& entranceIndex, float dt);
	virtual void Render(sf::RenderTarget& target);
	virtual void InitEnemies(const ResourceManager& resourceManager);

	void DeleteCoins();
protected:

	Camera m_Camera;
	Transition m_Transition;
	LevelLabel m_Label;
	Hud m_Hud;

	sf::TileMap m_Map;
	sf::DynamicQuadTree<Entity>* m_Tree;
	sf::AStar m_AStar;

	std::vector<std::unique_ptr<Entity>> m_Enemies;
	Player* m_Player;
};