#pragma once
#include "Core/ResourceManager.h"

class Menu
{
public:
	 
	Menu();
	virtual ~Menu();

	virtual void Init(const ResourceManager& resourceManager) = 0;
	virtual void Update(StateID& currentState, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
};

