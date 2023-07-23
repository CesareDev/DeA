#pragma once
#include "Core/TextureManager.h"
#include "Entities/Player.h"

class Hud
{
public:

	Hud();
	~Hud();

	void Init(const TextureManager& textureManager, const Player* player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	const Player* m_Player;
};