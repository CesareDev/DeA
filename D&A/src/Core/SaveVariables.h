#pragma once
#include "Entities/EntityID.h"
#include "SaveManager.h"

namespace SAVE
{
	inline sf::Vector2f PLAYER_POS = { 0.f, 0.f };
	inline int PLAYER_HEALTH = 100;
	inline unsigned int COIN_NUMBER = 0;
	inline LevelID LEVEL_ID = LevelID::Null;
	inline EntityID WEAPON[8] =
	{
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
		EntityID::Null,
	};
	inline bool ORC_BOSS_DEFEATED = false;
	inline bool UNDEAD_BOSS_DEFEATED = false;
	inline bool DEMON_BOSS_DEFEATED = false;

	inline SaveManager SAVE_MANAGER;
}
