#pragma once
#include "Core/TextureManager.h"

class Entity : public sf::Circle
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

	virtual void Init(const TextureManager& textureManager) = 0;
	virtual void Update(UpdateArgs args, float dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	inline bool IsDead() const { return m_IsDead; }

protected:

	bool m_IsDead = false;
	TextureManager* m_TextureManager = nullptr;

};

