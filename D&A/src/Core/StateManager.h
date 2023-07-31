#pragma once
#include "ResourceManager.h"
#include "States/State.h"

class StateManager
{
public:

	void Init(const ResourceManager& resourceManager);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	void ChangeState(float dt);

private:

	const ResourceManager* m_ResourceManager;

	std::unique_ptr<State> m_CurrentState;
	StateID m_CurrentStateId;
	StateID m_OldStateId;
	bool m_ChangingState;
};

