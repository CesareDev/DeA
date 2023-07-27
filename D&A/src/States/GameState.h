#pragma once
#include "State.h"
#include "Core/LevelManager.h"
#include "UI/Menu/PauseMenu.h"

class GameState : public State
{
public:

	GameState();
	~GameState();

	// Inherited via State
	void Init(const ResourceManager& resourceManager) override;
	
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	
	StateID GetStateID() const override;

private:
	
	LevelManager m_LevelManager;
	PauseMenu m_PauseMenu;
};

