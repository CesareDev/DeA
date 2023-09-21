#pragma once
#include "Entities/Characters/Character.h"
#include "Entities/Characters/Other/Spawner.h"

class OrcBoss : public Character
{
public:

	OrcBoss();
	~OrcBoss();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

private:

	Spawner m_Spawner;
	float m_SpawnTime;
	bool m_CanSpawn = false;
};

