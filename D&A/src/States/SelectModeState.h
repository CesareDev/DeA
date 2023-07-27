#pragma once
#include "State.h"
#include "UI/Menu/SelectModeMenu.h"

class SelectModeState : public State
{
public:

	SelectModeState();
	~SelectModeState();

	// Inherited via State
	void Init(const ResourceManager& resourceManager) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;

private:

	SelectModeMenu m_Menu;
};

