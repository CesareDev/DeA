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

float Weapon::Lerp(float a, float b, float f)
{
    return a + f * (b - a);
}
