#pragma once
#include "Environment.h"

class Chest : public Environment
{
public:

	Chest();
	~Chest();

	// Inherited via Environment
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
};

