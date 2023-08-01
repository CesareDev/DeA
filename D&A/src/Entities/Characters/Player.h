#pragma once
#include "Character.h"
#include "Entities/Weapons/Mace.h"

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
	const sf::Vector2f& GetCenter() const override;
	const sf::Rectangle& GetBounds() const override;
	EntityID GetId() const override;

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);

private:

	Mace mace;
};

