#pragma once
#include "Weapon.h"

class GreatMace : public Weapon
{
public:

	GreatMace();
	~GreatMace();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

protected:

	void Attack(float dt) override;
};

