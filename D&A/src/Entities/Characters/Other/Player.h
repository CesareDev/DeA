#pragma once
#include "Entities/Characters/Character.h"
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
	void RenderWeapon(sf::RenderTarget& target) override;

	void SetCoin(unsigned int coin);
	inline unsigned int GetCoin() const { return m_Coin; }
	inline int GetHealth() const { return m_Health; }

	void SetCurrentWeaponIndex(unsigned int index);
	inline unsigned int GetCurrentWeaponIndex() { return m_WeaponIndex; }
	EntityID GetWeaponID(unsigned int index);
	bool IsAttacking();
	bool AddWeapon(Weapon* weapon);

private:

	void Movement(UpdateArgs args, float dt);
	void UpdateAnimation(float dt);

private:

	const ResourceManager* m_ResourceManager;
	unsigned int m_Coin = 0;

	unsigned int m_WeaponIndex = 0;
	std::vector<std::unique_ptr<Weapon>> m_Weapons;
	bool m_Paused = false; //for stop weapon rotation
};