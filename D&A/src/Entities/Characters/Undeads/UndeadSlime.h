#pragma once
#include "Entities/Characters/Other/Player.h"

class UndeadSlime : public Character
{
public:

	UndeadSlime();
	~UndeadSlime();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

private:

	bool m_Poisoned = false;
	float m_PoisonedElapsedTime;
	Player* m_Player;
};

