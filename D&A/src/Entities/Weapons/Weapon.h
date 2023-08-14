#pragma once
#include "Core/ResourceManager.h"
#include "Entities/Entity.h"

class Weapon : public Entity
{
public:

	Weapon();
	virtual ~Weapon();

	virtual void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override = 0;
	virtual void Update(UpdateArgs args, float dt) override = 0;
	virtual void Render(sf::RenderTarget& target) override = 0;
	virtual void SetPosition(const sf::Vector2f& position) = 0;
	virtual EntityID GetId() const override = 0;
	EntityType GetType() const override;

protected:

	virtual void Attack(float dt) = 0;

protected:

	float m_Angle;
	float m_AttackAngle;
	float m_ElapsedTime;
	bool m_IsAttacking;
	bool m_CanHit;
	std::vector<sf::Vector2f> m_HitPoints;
};