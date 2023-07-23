#pragma once
#include "Core/TextureManager.h"

class Menu
{
public:
	 
	Menu();
	virtual ~Menu();

	virtual void Init(const TextureManager& textureManager) = 0;
	virtual void Update(StateID& currentState, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
};

