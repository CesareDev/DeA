#include "pch.h"
#include "Hud.h"

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::Init(const ResourceManager& resourceManager, const Player& player)
{
	m_Player = &player;

	m_HealthBarFrame.setTexture(resourceManager.GetTilesetTexture());
	m_HealthBarFrame.setTextureRect({ 360, 144, 64, 9 });
	m_HealthBarFrame.setPosition({ 8.f, 8.f });

	m_BarTail.setTexture(resourceManager.GetTilesetTexture());
	m_BarTail.setTextureRect({ 424, 144, 3, 3 });
	m_BarTail.setPosition({ 67.f, 11.f });

	m_HealthBar.setFillColor(sf::Color(218, 78, 56, 255));
	m_HealthBar.setPosition(8.f, 11.f);
	m_HealthBar.setSize({ 59.f, 3.f });

	m_StaticCamera.reset({ 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });
}

void Hud::Update(float dt)
{
}

void Hud::Render(sf::RenderTarget& target)
{
	sf::View currentCam = target.getView();
	target.setView(m_StaticCamera);

	target.draw(m_HealthBar);
	target.draw(m_BarTail);
	target.draw(m_HealthBarFrame);

	target.setView(currentCam);
}

void Hud::SetHealth(unsigned int m_Health)
{
}
