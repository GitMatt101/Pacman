#pragma once
#include "../lib.hpp"

// Draws the shapes on the screen.
void drawScene();

/**
* Updates the position and state of all the shapes in the scene.
* 
* @param value - The callback id
*/
void updateShapes(int value);

/**
* Updates the animations of the shapes.
*
* @param value - The callback id
*/
void updateAnimations(int value);