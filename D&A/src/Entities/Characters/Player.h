#pragma once
#include "Character.h"
#include "Entities/Weapons/Weapon.h"

class Player : public Character
{
public:
	 
	Player();
	~Player();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position);
	EntityID GetId() const override;

	void SetCurrentWeaponIndex(unsigned int index);
	inline unsigned int GetCurrentWeaponIndex() { return m_WeaponIndex; }
	EntityID GetWeaponID(unsigned int index);
	bool IsAttacking();
	void RenderWeapon(sf::RenderTarget& target);	

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);

private:

	unsigned int m_WeaponIndex = 0;
	std::vector<std::unique_ptr<Weapon>> m_Weapons;
	bool m_Paused = false; //for stop weapon rotation
};