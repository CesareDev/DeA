#pragma once
#include "Character.h"
#include "Entities/Weapons/GreatAxe.h"

class Player : public Character
{
public:
	 
	Player();
	~Player();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position);
	void TakeDamage(unsigned int damage) override;
	EntityID GetId() const override;

	Weapon* GetWeapon();

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);

private:

	GreatAxe sword;
};