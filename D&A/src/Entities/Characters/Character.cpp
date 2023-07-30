#include "pch.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

EntityType Character::GetType() const
{
    return EntityType::Character;
}
