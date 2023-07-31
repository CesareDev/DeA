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
	const sf::Vector2f& GetCenter() const override = 0;
	virtual const sf::Rectangle& GetBounds() const override = 0;
	virtual EntityID GetId() const override = 0;
	EntityType GetType() const override;

protected:

	float m_RecoveryTime;
	unsigned int m_AttackPower;
};