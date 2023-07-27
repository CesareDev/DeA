#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	 
	Player();
	~Player();

	// Inherited via Entity
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& centerPosition) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	EntityID GetId() const override;

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);

private:

	bool m_IsMoving;
	float m_ElapsedAnimationTime;
	sf::IntRect m_TextureRect;

	sf::Vector2f m_Velocity;
};

