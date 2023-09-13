#pragma once

enum class EntityID
{
	Null,

	//Weapon
	Knife,
	RustySword,
	Sword,
	MagicSword,
	GreatHammer,
	Hammer,
	Mace,
	GreatMace,
	Katana,
	GreatSword,
	ColossalSword,
	GoldenSword,
	ColossalGoldenSword,
	GreatAxe,
	Spear,
	Bow,
	Arrow,
	HealthPotion,
	BigHealthPotion,
	DamagePotion,
	BigDamagePotion,

	//Characters
	Player,
	Slug,
	SmallDemon,
	HalfDemon,
	Demon,
	MagicDemon,
	DemonBoss,
	SmallOrc,
	Orc,
	MaskedOrc,
	TribalOrc,
	OrcBoss,
	SmallUndead,
	HalfUndead,
	Undead,
	UndeadSlime,
	UndeadBoss,

	//Env
	Ladder,
	Door,
	Coin,
	Chest,
	Message
};

enum class EntityType
{
	Null,
	Character,
	Weapon,
	Environment
};