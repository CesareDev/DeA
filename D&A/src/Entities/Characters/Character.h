#pragma once
#include "Entities/Entity.h"

class Character : public Entity
{
public:

	Character();
	virtual ~Character();

	// Inherited via Entity
	virtual void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override = 0;
	virtual void Update(UpdateArgs args, float dt) override = 0;
	virtual void Render(sf::RenderTarget& target) override = 0;
	virtual void SetPosition(const sf::Vector2f& position) = 0;
	virtual void TakeDamage(unsigned int damage) = 0;
	virtual EntityID GetId() const override = 0;
	EntityType GetType() const override;

	inline bool IsDead() const { return m_IsDead; }
	inline bool IsMoving() const { return m_IsMoving; }

protected:

	float m_ElapsedAnimationTime;
	sf::IntRect m_TextureRect;

	bool m_IsMoving;
	sf::Vector2f m_Velocity;

	int m_Health;
	bool m_IsDead = false;
};

