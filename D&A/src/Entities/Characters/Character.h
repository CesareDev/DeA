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
	virtual EntityID GetId() const override = 0;
	EntityType GetType() const override;

	void TakeDamage(unsigned int damage);
	inline bool IsVulnerable() const { return m_Vulnerable; }
	inline bool IsDead() const { return m_IsDead; }
	inline bool IsMoving() const { return m_IsMoving; }

protected:

	void DamageAnimation(float dt);
	void DeathAnimation(float dt);

protected:

	float m_ElapsedAnimationTime;
	sf::IntRect m_TextureRect;

	bool m_IsMoving;
	sf::Vector2f m_Velocity;

	int m_Health;
	bool m_IsDead = false;

	float m_VulnerableTime;
	float m_IntervalTime;
	bool m_Vulnerable = true;

	sf::Text m_DamageTaken;
};

