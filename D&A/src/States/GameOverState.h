#pragma once
#include "State.h"

class GameOverState : public State
{
public:

	GameOverState();
	~GameOverState();

	// Inherited via State
	void Init(const ResourceManager& resourceManager) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;

private:

	float m_ElapsedTime;
	sf::Text m_GameOverText;
};

