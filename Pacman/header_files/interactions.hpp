#pragma once

/**
* Checks user input and moves the player accordingly
* 
* @param key - The pressed key.
* @param x - The cursor's x position when the key was pressed.
* @param y - The cursor's y position when the key was pressed.
*/
void input(unsigned char key, int x, int y);

// Checks if the player collided with a wall.
bool checkWallCollision();

// Checks if the player collided with an enemy.
bool checkEnemyCollision();