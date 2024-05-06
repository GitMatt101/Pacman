#include "../header_files/interactions.hpp"
#include "../header_files/shapes.hpp"
#include "../utils.hpp"

#define DEFAULT_MOVEMENT 10.0f

extern Player* player;

void input(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': case 'W':	// UP
			player->move(NULL, DEFAULT_MOVEMENT);
			// If the player goes too far up he teleports to the bottom
			if (player->getPosition().second > (float)HEIGHT)
				player->move(NULL, -player->getPosition().second + SCORE_SPACE);
			player->setRotation(90.0f);
			break;
		case 'a': case 'A':	// LEFT
			player->move(-DEFAULT_MOVEMENT, NULL);
			// If the player goes too far left he teleports to the right
			if (player->getPosition().first < 0.0f)
				player->move((float)WIDTH, NULL);
			player->setRotation(180.0f);
			break;
		case 's': case 'S':	// DOWN
			player->move(NULL, -DEFAULT_MOVEMENT);
			// If the player goes too far down he teleports to the top
			if (player->getPosition().second < (float)SCORE_SPACE)
				player->move(NULL, (float)HEIGHT);
			player->setRotation(-90.0f);
			break;
		case 'd': case 'D':	// RIGHT
			player->move(DEFAULT_MOVEMENT, NULL);
			// If the player goes too far right he teleports to the left
			if (player->getPosition().first > (float)WIDTH)
				player->move(-player->getPosition().first, NULL);
			player->setRotation(0.0f);
			break;
		default:
			break;
	}
}

bool checkWallCollision() {
	return false;
}

bool checkEnemyCollision() {
	return false;
}