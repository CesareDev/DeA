#pragma once
#include "Weapon.h"

class MagicSword : public Weapon
{
public:

	MagicSword();
	~MagicSword();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
	void Attack(float dt) override;
};

