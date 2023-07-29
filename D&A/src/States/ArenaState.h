#pragma once
#include "State.h"
#include "Entities/Characters/Player.h"
#include "Core/Camera.h"
#include "UI/Menu/PauseMenu.h"

class ArenaState : public State
{
public:

	ArenaState();
	~ArenaState();

	// Inherited via State
	void Init(const ResourceManager& resourceManager) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;

private:

	PauseMenu m_PauseMenu;
	Transition m_Transition;

	Player* m_Player;
	Camera m_Camera;
	sf::TileMap m_Arena;
	sf::DynamicQuadTree<Entity> m_Tree;
};

