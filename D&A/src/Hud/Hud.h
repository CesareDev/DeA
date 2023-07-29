#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Player.h"

class Hud
{
public:

	Hud();
	~Hud();

	void Init(const ResourceManager& resourceManager, const Player* player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	const Player* m_Player;
};