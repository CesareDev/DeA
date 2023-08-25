#include "pch.h"
#include "Hud.h"

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::Init(const ResourceManager& resourceManager, const Player& player, const sf::TileMap& map)
{
	m_Player = &player;

	m_BarFrame.setTexture(resourceManager.GetTilesetTexture());
	m_BarFrame.setTextureRect({ 360, 128, 64, 32});
	m_BarFrame.setPosition({ 8.f, 8.f });

	m_HealthTail.setTexture(resourceManager.GetTilesetTexture());
	m_HealthTail.setTextureRect({ 424, 144, 3, 3 });
	m_HealthTail.setPosition({ 67.f, 11.f });

	m_ManaTail.setTexture(resourceManager.GetTilesetTexture());
	m_ManaTail.setTextureRect({ 424, 155, 3, 3 });
	m_ManaTail.setPosition({ 67.f, 22.f });

	m_HealthBar.setFillColor(sf::Color(218, 78, 56, 255));
	m_HealthBar.setPosition(8.f, 11.f);
	m_HealthBar.setSize({ 59.f, 3.f });

	m_ManaBar.setFillColor(sf::Color(86, 152, 204, 255));
	m_ManaBar.setPosition(8.f, 22.f);
	m_ManaBar.setSize({ 59.f, 3.f });

	const_cast<sf::Texture&>(resourceManager.GetFont().getTexture(40)).setSmooth(false);
	m_CoinQuantity.setFont(resourceManager.GetFont());
	m_CoinQuantity.setCharacterSize(40);
	m_CoinQuantity.setPosition(80.f, 160.f);
	m_CoinQuantity.setOutlineColor(sf::Color::Black);
	m_CoinQuantity.setOutlineThickness(4.f);
	m_CoinQuantity.setString("0");

	m_StaticCamera.reset({ 0.f, 0.f, GLOBAL::WIN_WIDTH / 5.f, GLOBAL::WIN_HEIGHT / 5.f });

	m_Inv.Init(resourceManager, player);

	m_MiniMap.Init(resourceManager, map, player);
}

void Hud::Update(float dt)
{
	m_Inv.Update(dt);
	m_MiniMap.Update(dt);
}

void Hud::Render(sf::RenderTarget& target)
{
	sf::View currentCam = target.getView();
	target.setView(m_StaticCamera);

	//Bar
	target.draw(m_HealthBar);
	target.draw(m_ManaBar);

	//Tail
	target.draw(m_HealthTail);
	target.draw(m_HealthTail);

	//Frame
	target.draw(m_BarFrame);

	sf::View v({ 0.f, 0.f, 1280, 720 });
	target.setView(v);
	target.draw(m_CoinQuantity);
	m_MiniMap.Render(target);

	target.setView(m_StaticCamera);

	m_Inv.Render(target);

	target.setView(currentCam);
}
