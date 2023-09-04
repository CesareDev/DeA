#pragma once
#include "Environment.h"

class Door : public Environment
{
public:

	Door();
	~Door();

	// Inherited via Environment
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position) override;
	EntityID GetId() const override;

	void RenderBottomPart(sf::RenderTarget& target);

private:

	sf::Sprite m_BottomPart;
};

