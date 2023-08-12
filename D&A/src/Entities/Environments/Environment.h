#pragma once
#include "Entities/Entity.h"

class Environment : public Entity
{
public:

	Environment();
	virtual ~Environment();

	// Inherited via Entity
	virtual void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override = 0;
	virtual void Update(UpdateArgs args, float dt) override = 0;
	virtual void Render(sf::RenderTarget& target) override = 0;
	virtual void SetPosition(const sf::Vector2f& position) = 0;
	virtual EntityID GetId() const override = 0;
	EntityType GetType() const override;
};