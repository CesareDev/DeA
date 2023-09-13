#pragma once
#include "Entities/Characters/Character.h"

class MaskedOrc : public Character
{
public:

	MaskedOrc();
	~MaskedOrc();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
};

