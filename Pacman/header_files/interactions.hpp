#pragma once
#include "shapes.hpp"

/**
* Checks user input and moves the player accordingly
* 
* @param key - The pressed key.
* @param x - The cursor's x position when the key was pressed.
* @param y - The cursor's y position when the key was pressed.
*/
void input(unsigned char key, int x, int y);

/**
* Checks if an entity collided with a wall.
* 
* @param entity - Entity to check collision with.
* @param x - Horizontal movement.
* @param y - Vertical movement.
* @return true if the player collided with a wall, false otherwise
*/
bool checkWallCollision(Entity* entity, float x, float y);

/**
* Checks if the player collided with an entity.
* 
* @param etnity - Entity to check collision with.
* @return true if the player collided with the entity, false otherwise.
*/ 
bool checkCollision(Entity* entity);