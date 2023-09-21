#include "pch.h"
#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::DeleteCoins()
{
	for (auto it = m_Tree->begin(); it != m_Tree->end(); ++it)
		if (it->obj->GetId() == EntityID::Coin)
			delete it->obj;
}
