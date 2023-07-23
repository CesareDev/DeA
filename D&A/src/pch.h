#pragma once

#ifdef DEBUG
#include <iostream>
#endif // DEBUG


#include <SFML/Graphics.hpp>
#include <SFML/Extensions/DynamicQuadTree.hpp>
#include <SFML/Extensions/Shapes.h>
#include <SFML/Extensions/TileMap.h>
#include <SFML/Extensions/SpriteBatch.h>

#include "States/StateID.h"
#include "Level/LevelID.h"

static unsigned int WIN_WIDTH = 1280;
static unsigned int WIN_HEIGHT = 720;

static unsigned int SOUND_VOLUME = 0;
static unsigned int MUSIC_VOLUME = 0;

static bool FULLSCREEN = false;