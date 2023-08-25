#pragma once

enum class EntityID
{
	Null,

	//Characters
	Player,
	Slug,
	DemonBoss,
	SmallDemon,
	HalfDemon,
	Demon,

	//Env
	Ladder,

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
	GreatAxe,
	Spear,
	Bow,
	Arrow,
	HealthPotion,
	BigHealthPotion,
	DamagePotion,
	BigDamagePotion
};

enum class EntityType
{
	Null,
	Character,
	Weapon,
	Environment
};