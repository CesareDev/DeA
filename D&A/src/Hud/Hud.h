#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Characters/Player.h"

class Hud
{
public:

	Hud();
	~Hud();

	void Init(const ResourceManager& resourceManager, const Player& player);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

	void SetHealth(unsigned int m_Health);

private:

	const Player* m_Player;
	
	sf::View m_StaticCamera;
	sf::Sprite m_HealthBarFrame;
	sf::Sprite m_BarTail;
	sf::RectangleShape m_HealthBar;
};