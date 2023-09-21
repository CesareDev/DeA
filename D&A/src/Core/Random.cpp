#include "pch.h"
#include "Random.h"

Random::Random()
{
	srand((unsigned)time(NULL));
}

Random::~Random()
{
}