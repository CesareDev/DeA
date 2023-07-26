#pragma once
#include "Entity.h"

class Ladder : public Entity
{
public:

	Ladder();
	~Ladder();

	// Inherited via Entity
	void Init(const TextureManager& textureManager, const sf::Vector2f& centerPosition) override;
	void Update(UpdateArgs args, float dt) override;
	void Render(sf::RenderTarget& target) override;
	EntityID GetId() const override;

	void SetTeleportLevel(LevelID teleportLevel);

private:

	LevelID m_Teleport = LevelID::Null;
};

