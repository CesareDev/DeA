#pragma once
#include "State.h"
#include "UI/Menu/OptionsMenu.h"

class OptionsMenuState : public State
{
public:

	OptionsMenuState();
	~OptionsMenuState();

	void Init(const TextureManager& textureManger) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;

private:

	OptionsMenu m_Menu;
};

