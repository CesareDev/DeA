#pragma once
#include "Core/ResourceManager.h"
#include "EntityID.h"

class Entity : public sf::Sprite
{
protected:

	struct UpdateArgs
	{
		sf::DynamicQuadTree<Entity>& qTree;
		sf::TileMap& tileMap;
		StateID& currentState;
		LevelID& currentLevel;
	};

public:

	Entity();
	virtual ~Entity();

	virtual void Init(const ResourceManager& resourceManager, const sf::Vector2f& position) = 0;
	virtual void Update(UpdateArgs args, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void SetPosition(const sf::Vector2f& position) = 0;
	inline const sf::Vector2f& GetCenter() const { return m_Center; }
	inline const sf::Rectangle& GetBounds() const { return m_Bounds; }
	virtual EntityID GetId() const = 0;
	virtual EntityType GetType() const = 0;

protected:

	sf::Vector2f m_Center;
	sf::Rectangle m_Bounds;
};

