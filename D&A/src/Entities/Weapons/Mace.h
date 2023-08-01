#pragma once
#include "Weapon.h"

class Mace : public Weapon
{
public:

	Mace();
	~Mace();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position);
	const sf::Vector2f& GetCenter() const override;
	const sf::Rectangle& GetBounds() const override;
	EntityID GetId() const override;

protected:

	void Attack(float dt) override;
};

