#pragma once
#include "Character.h"

class Player : public Character
{
public:
	 
	Player();
	~Player();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& centerPosition) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	EntityID GetId() const override;

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);
};

