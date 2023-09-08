#pragma once
#include "Environment.h"

class Ladder : public Environment
{
public:

	Ladder();
	~Ladder();

	// Inherited via Entity
	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	void SetPosition(const sf::Vector2f& position);
	EntityID GetId() const override;

	void SetTeleportLevel(LevelID teleportLevel, unsigned int teleportEntranceIndex);

private:

	LevelID m_Teleport = LevelID::Null;
	unsigned int m_TeleportEntranceIndex = 0;
};

