#pragma once
#include "State.h"

class MainTitleState : public State
{
public:

	MainTitleState();
	~MainTitleState();

	// Inherited via State
	void Init(const ResourceManager& resourceManager) override;
	bool OnEnter(float dt) override;
	bool OnExit(float dt) override;
	void Update(StateID& currentState, float dt) override;
	void Render(sf::RenderTarget& target) override;
	StateID GetStateID() const override;

private:

	sf::Text m_Title;
	sf::Text m_MusicCredit;
};

