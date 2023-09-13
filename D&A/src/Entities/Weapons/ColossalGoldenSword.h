#pragma once
#include "Weapon.h"
#include "BigDamagePotion.h"

class ColossalGoldenSword : public Weapon
{
public:

	ColossalGoldenSword();
	~ColossalGoldenSword();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
	void Attack(float dt) override;

private:

	BigDamagePotion m_Potion;

	bool m_Pressed = false;
	float m_ChargingTime;
	float m_RedChannel;

	bool m_PlaySound = false;
};

