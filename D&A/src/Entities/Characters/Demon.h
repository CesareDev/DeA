#pragma once
#include "Character.h"

class Demon : public Character
{
public:

	Demon();
	~Demon();

	// Inherited via Character
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;
	
private:

	float m_FollowElapsedTime;
	bool m_FindPath = false;
};