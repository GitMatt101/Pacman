#include "../header_files/interactions.hpp"
#include "../header_files/shapes.hpp"

extern vector<Shape*> walls;
extern Player* player;

void input(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': case 'W':	// UP
			player->setDirection(UP);
			player->setRotation(90.0f);
			break;
		case 'a': case 'A':	// LEFT
			player->setDirection(LEFT);
			player->setRotation(180.0f);
			break;
		case 's': case 'S':	// DOWN
			player->setDirection(DOWN);
			player->setRotation(-90.0f);
			break;
		case 'd': case 'D':	// RIGHT
			player->setDirection(RIGHT);
			player->setRotation(0.0f);
			break;
		default:
			break;
	}
}

bool checkWallCollision(float x, float y) {
	for (Shape* wall : walls) {
		if (player->getHitboxWorldCoordinates().cornerBot.x + x <= wall->getHitboxWorldCoordinates().cornerTop.x
			&& player->getHitboxWorldCoordinates().cornerTop.x + x >= wall->getHitboxWorldCoordinates().cornerBot.x
			&& player->getHitboxWorldCoordinates().cornerBot.y + y <= wall->getHitboxWorldCoordinates().cornerTop.y
			&& player->getHitboxWorldCoordinates().cornerTop.y + y >= wall->getHitboxWorldCoordinates().cornerBot.y)
			return true;
	}
	return false;
}

bool checkEnemyCollision() {
	return false;
}