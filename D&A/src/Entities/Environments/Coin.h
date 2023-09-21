#pragma once
#include "Environment.h"

class Coin : public Environment
{
public:

	Coin();
	~Coin();

	// Inherited via Environment
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

	void SetSpawnY(float y);

private:

	float m_SpawnY;
	bool m_Spawned = true;
	bool m_CanBePicked = false;

	sf::IntRect m_TextureRect;
	float m_ElapsedTime;
};