#include "pch.h"
#include "Door.h"

Door::Door()
{
}

Door::~Door()
{
}

void Door::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 368, 560, 48, 16 });
	
	m_BottomPart.setTexture(resourceManager.GetTilesetTexture());
	m_BottomPart.setTextureRect({ 368, 576, 48, 16 });

	m_Bounds.size = { 48.f, 16.f };

	SetPosition(position);
}

void Door::Update(UpdateArgs args, float dt)
{
}

void Door::Render(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Door::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
	m_BottomPart.setPosition(position.x, position.y + 16.f);
	m_Bounds.position = position;
}

EntityID Door::GetId() const
{
	return EntityID::Door;
}

void Door::RenderBottomPart(sf::RenderTarget& target)
{
	target.draw(m_BottomPart);
}