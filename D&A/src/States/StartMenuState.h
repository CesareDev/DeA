#pragma once
#include "State.h"
#include "Core/Camera.h"
#include "UI/Menu/StartMenu.h"

class StartMenuState : public State
{
public:

	StartMenuState();
	~StartMenuState();

	// Inherited via State
	void Init(const TextureManager& textureManger) override;

	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;

	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;

	StateID GetStateID() const override;

private:

	StartMenu m_StartMenu;
};

