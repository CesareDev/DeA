#pragma once
#include "Core/TextureManager.h"
#include "Effects/Transition.h"

class State
{
public:

	State();
	virtual ~State();

	virtual void Init(const TextureManager& textureManger) = 0;

	virtual bool OnEnter(float dt) = 0;
	virtual bool OnExit(float dt) = 0;

	virtual void Update(StateID& currentState, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

	virtual StateID GetStateID() const = 0;

protected:

	Transition m_Transition;

};