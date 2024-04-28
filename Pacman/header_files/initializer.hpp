#pragma once
#include "../lib.hpp"
#include "shaders.hpp"

// Initializes the shaders to fill the background and calculate color interpolation.
void initShaders();

// Initializes the game.
void initGame();

/**
* Clears the scene, reloads the player and loads the new level.
* 
* @param index - The index of the level to be loaded.
*/
void initLevel(int index);