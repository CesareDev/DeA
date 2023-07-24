#pragma once
#include "State.h"

class ArenaState : public State
{
public:

	ArenaState();
	~ArenaState();

	// Inherited via State
	void Init(const TextureManager& textureManger) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;
};

