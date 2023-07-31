#include "pch.h"
#include "Knife.h"

Knife::Knife()
{
}

Knife::~Knife()
{
}

void Knife::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
	setTexture(resourceManager.GetTilesetTexture());
	setTextureRect({ 293, 18, 6, 13 });
	setOrigin(3.f, 24.f);

	SetPosition(position);
}

void Knife::Update(UpdateArgs args, float dt)
{
	for (auto it = args.qTree.begin(); it != args.qTree.end(); ++it)
	{
		if (it->obj->GetId() == EntityID::Player)
		{
			m_PlayerCenter = it->obj->GetCenter();
			SetPosition(m_PlayerCenter);
		}
	}
	setRotation(m_Angle + 90.f);
}

void Knife::Render(sf::RenderTarget& target)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((sf::RenderWindow&)target);
	sf::Vector2f mpos = target.mapPixelToCoords(pixelPos);
	m_Angle = atan2f(mpos.y - m_PlayerCenter.y, mpos.x - m_PlayerCenter.x) * 180 / acos(-1.f);

	target.draw(*this);
}

void Knife::SetPosition(const sf::Vector2f& position)
{
	setPosition(position);
}

const sf::Vector2f& Knife::GetCenter() const
{
	return getPosition();
}

const sf::Rectangle& Knife::GetBounds() const
{
	return { 0.f, 0.f, 0.f , 0.f };
}

EntityID Knife::GetId() const
{
	return EntityID::Knife;
}