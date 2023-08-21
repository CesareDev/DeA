#pragma once
#include <queue>

#include "Weapon.h"
#include "Entities/Characters/Arrow.h"

class Bow : public Weapon
{
public:

	Bow();
	~Bow();

	// Inherited via Weapon
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

protected:

	void Attack(float dt) override;

private:

	bool m_MousePressed = false;
	const ResourceManager* m_ResourceManager;
	std::queue<Arrow> m_ArrowsQueue;
};

