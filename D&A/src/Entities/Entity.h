#pragma once
#include "Core/TextureManager.h"
#include "EntityID.h"

class Entity : public sf::Circle
{
protected:

	struct UpdateArgs
	{
		sf::DynamicQuadTree<Entity>& qTree;
		sf::TileMap& tileMap;
		StateID& currentState;
		LevelID* currentLevel = nullptr;
	};

public:

	Entity();
	virtual ~Entity();

	virtual void Init(const TextureManager& textureManager, const sf::Vector2f& position) = 0;
	virtual void Update(UpdateArgs args, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual EntityID GetId() const = 0;
	inline bool IsDead() const { return m_IsDead; }

protected:

	bool m_IsDead = false;
};

