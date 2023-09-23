#pragma once
#include "Entities/Characters/Character.h"

class Princess : public Character
{
public:

	Princess();
	~Princess();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

	void SetPlayer(const Character& player);

private:

	const Character* m_Player;
};

