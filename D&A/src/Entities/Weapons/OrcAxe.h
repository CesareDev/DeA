#pragma once
#include "Weapon.h"

class OrcAxe : public Weapon
{
public:

	OrcAxe();
	~OrcAxe();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
	void Attack(float dt) override;

	void StartAttack();
	void SetAxeAngle(const sf::Vector2f& playerPosition);
};

