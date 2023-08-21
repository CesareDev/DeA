#pragma once
#include "Character.h"

class Arrow : public Character
{
public:

	Arrow();
	~Arrow();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

public:

	void Spawn(float angle, const sf::Vector2f& position, float dt);
	void Shoot();
	inline bool IsShooted() { return m_Shooted; }

private:

	bool m_Shooted = false;
	bool m_Stopped = false;
	const sf::Vector2f* m_EnemyPosition = nullptr;
	sf::Vector2f m_HitPosition;
	float m_Angle;
	float m_Alpha = 255.f;
	sf::Vector2f m_HitPoint;
	unsigned int m_Damage;
};

