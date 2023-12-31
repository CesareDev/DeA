#pragma once
#include "Entities/Characters/Character.h"
#include "Entities/Weapons/OrcAxe.h"

class TribalOrc : public Character
{
public:

	TribalOrc();
	~TribalOrc();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	void RenderWeapon(sf::RenderTarget& target) override;
	EntityID GetId() const override;


private:

	OrcAxe m_Axe;
};

