#include "pch.h"
#include "Undead.h"

Undead::Undead()
{
}

Undead::~Undead()
{
}

void Undead::Init(const ResourceManager& resourceManager, const sf::Vector2f& position)
{
}

void Undead::Update(UpdateArgs args, float dt)
{
}

void Undead::Render(sf::RenderTarget& target)
{
}

void Undead::SetPosition(const sf::Vector2f& position)
{
}

EntityID Undead::GetId() const
{
	return EntityID::Undead;
}
