#pragma once
#include "Weapon.h"

class Knife : public Weapon
{
public:

	Knife();
	~Knife();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& centerPosition) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	EntityID GetId() const override;
};

