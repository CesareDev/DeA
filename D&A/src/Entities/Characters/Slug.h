#pragma once
#include "Character.h"

class Slug : public Character
{
public:

	Slug();
	~Slug();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	const sf::Vector2f& GetCenter() const override;
	const sf::Rectangle& GetBounds() const override;
	void TakeDamage(unsigned int damage) override;
	EntityID GetId() const override;

private:

	float m_VulnerableTime;
	bool m_Vulnerable;

	sf::Text m_DamageTaken;
};

