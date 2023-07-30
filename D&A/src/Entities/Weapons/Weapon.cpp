#include "pch.h"
#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

EntityType Weapon::GetType() const
{
    return EntityType::Weapon;
}
