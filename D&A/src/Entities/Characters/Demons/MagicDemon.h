#pragma once
#include "Entities/Characters/Character.h"

class MagicDemon : public Character
{
public:

	MagicDemon();
	~MagicDemon();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	void RenderWeapon(sf::RenderTarget& target) override;
	EntityID GetId() const override;

private:

	sf::CircleShape m_MagicArea;
	bool m_CanMagicAttack = false;
	float m_MagicAttackElapsedTime;
};

