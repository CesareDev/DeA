#pragma once
#include "TextureManager.h"
#include "States/State.h"

class StateManager
{
public:

	void Init();
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	void ChangeState(float dt);

private:

	TextureManager m_TextureManager;

	std::unique_ptr<State> m_CurrentState;
	StateID m_CurrentStateId;
	StateID m_OldState;
	bool m_ChangingState;
};

