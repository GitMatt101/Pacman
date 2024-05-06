#include "../header_files/interactions.hpp"
#include "../header_files/shapes.hpp"
#include "../utils.hpp"
#include <typeinfo>

#define DEFAULT_MOVEMENT 10.0f

extern vector<Shape*> walls;
extern Player* player;

void input(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': case 'W':	// UP
			if (!checkWallCollision(0.0f, DEFAULT_MOVEMENT))
				player->move(0.0f, DEFAULT_MOVEMENT);
			// If the player goes too far up he teleports to the bottom
			if (player->getPosition().second > (float)HEIGHT)
				player->move(0.0f, -player->getPosition().second + SCORE_SPACE);
			player->setRotation(90.0f);
			break;
		case 'a': case 'A':	// LEFT
			if (!checkWallCollision(-DEFAULT_MOVEMENT, 0.0f))
				player->move(-DEFAULT_MOVEMENT, 0.0f);
			// If the player goes too far left he teleports to the right
			if (player->getPosition().first < 0.0f)
				player->move((float)WIDTH, 0.0f);
			player->setRotation(180.0f);
			break;
		case 's': case 'S':	// DOWN
			if (!checkWallCollision(0.0f, -DEFAULT_MOVEMENT))
				player->move(0.0f, -DEFAULT_MOVEMENT);
			// If the player goes too far down he teleports to the top
			if (player->getPosition().second < (float)SCORE_SPACE)
				player->move(0.0f, (float)HEIGHT);
			player->setRotation(-90.0f);
			break;
		case 'd': case 'D':	// RIGHT
			if (!checkWallCollision(DEFAULT_MOVEMENT, 0.0f))
				player->move(DEFAULT_MOVEMENT, 0.0f);
			// If the player goes too far right he teleports to the left
			if (player->getPosition().first > (float)WIDTH)
				player->move(-player->getPosition().first, 0.0f);
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
		{
			printf("%f\t%f\n", wall->getHitboxWorldCoordinates().cornerBot.x, wall->getHitboxWorldCoordinates().cornerBot.y);
			printf("%f\t%f\n", wall->getHitboxWorldCoordinates().cornerTop.x, wall->getHitboxWorldCoordinates().cornerTop.y);
			return true;
		}
	}
	return false;
}

bool checkEnemyCollision() {
	return false;
}