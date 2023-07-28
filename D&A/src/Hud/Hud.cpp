#include "pch.h"
#include "Hud.h"

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::Init(const ResourceManager& resourceManager, const Player* player)
{
	m_Player = player;
}

void Hud::Update(float dt)
{
}

void Hud::Render(sf::RenderTarget& target)
{
	const auto& currView = target.getView();
	target.setView(target.getDefaultView());
	sf::CircleShape c;
	c.setPosition(100.f, 100.f);
	c.setRadius(50.f);
	c.setFillColor(sf::Color::Red);
	target.draw(c);
	target.setView(currView);
}
