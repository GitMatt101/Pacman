#pragma once
#include "../lib.hpp"
#include "shaders.hpp"

// Initializes the shaders to fill the background and calculate color interpolation.
void initShaders();

// Initializes the GL uniform variables.
void initUniforms();

// Initializes the game.
void initGame();

// Clears the scene and reloads the player, the walls, the enemies and the power ups.
void initLevel();