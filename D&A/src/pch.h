#pragma once

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <SFML/Graphics.hpp>
#include <SFML/Extensions/DynamicQuadTree.hpp>
#include <SFML/Extensions/Utility.h>
#include <SFML/Extensions/TileMap.h>
#include <SFML/Extensions/SpriteBatch.h>
#include <SFML/Extensions/AStar.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Audio.hpp>

#include "States/StateID.h"
#include "Levels/LevelID.h"

#include "Core/GlobalVariables.h"
#include "Core/SaveVariables.h"
#include "Core/MusicVariables.h"