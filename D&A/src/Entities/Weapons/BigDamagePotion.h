#pragma once
#include "Weapon.h"

class BigDamagePotion : public Weapon
{
public:

	BigDamagePotion();
	~BigDamagePotion();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

	void UpdateAttackZone(UpdateArgs args, float dt);
	void RenderAttackZone(sf::RenderTarget& target);

protected:

	void Attack(float dt) override;

private:

	bool m_Drinked = false;
	sf::CircleShape m_DamageArea;
};

