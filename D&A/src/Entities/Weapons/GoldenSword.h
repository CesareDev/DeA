#pragma once
#include "Weapon.h"
#include "DamagePotion.h"

class GoldenSword : public Weapon
{
public:

	GoldenSword();
	~GoldenSword();
		
	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
	void Attack(float dt) override;

private:

	DamagePotion m_Potion;

	bool m_Pressed = false;
	float m_ChargingTime;
	float m_RedChannel;
};

