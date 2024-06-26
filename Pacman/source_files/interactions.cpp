#include "../header_files/interactions.hpp"
#include "../header_files/shapes.hpp"

extern vector<Shape*> walls;
extern Player* player;
extern vector<Entity*> enemies;

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

bool checkWallCollision(Entity* entity, float x, float y) {
	for (Shape* wall : walls) {
		if (entity->getHitboxWorldCoordinates().cornerBot.x + x <= wall->getHitboxWorldCoordinates().cornerTop.x
			&& entity->getHitboxWorldCoordinates().cornerTop.x + x >= wall->getHitboxWorldCoordinates().cornerBot.x
			&& entity->getHitboxWorldCoordinates().cornerBot.y + y <= wall->getHitboxWorldCoordinates().cornerTop.y
			&& entity->getHitboxWorldCoordinates().cornerTop.y + y >= wall->getHitboxWorldCoordinates().cornerBot.y)
			return true;
	}
	return false;
}

bool checkCollision(Entity* entity) {
	if (player->getHitboxWorldCoordinates().cornerBot.x <= entity->getHitboxWorldCoordinates().cornerTop.x
		&& player->getHitboxWorldCoordinates().cornerTop.x >= entity->getHitboxWorldCoordinates().cornerBot.x
		&& player->getHitboxWorldCoordinates().cornerBot.y <= entity->getHitboxWorldCoordinates().cornerTop.y
		&& player->getHitboxWorldCoordinates().cornerTop.y >= entity->getHitboxWorldCoordinates().cornerBot.y)
		return true;
	else
		return false;
}