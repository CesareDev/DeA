#include "pch.h"
#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

EntityType Environment::GetType() const
{
    return EntityType::Environment;
}
