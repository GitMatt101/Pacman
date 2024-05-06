#include "../header_files/animations.hpp"
#include "../header_files/shapes.hpp"

#define PI 3.14159265358979323846

extern Player* player;

static int stepBack = 1;

void widenMouth() {
	float step = 2 * PI / 180;
	float thetaTop = ((float)player->getVertices()->size() - 135.0f - (float)stepBack) * (-step);
	float thetaBottom = ((float)player->getVertices()->size() - (float)stepBack) * step ;
	player->getVertices()->insert(player->getVertices()->begin() + 1, {
		vec3(1.0f * cos(thetaTop), 1.0f * sin(thetaTop), 0.0f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f)
	});
	player->getVertices()->push_back({
		vec3(1.0f * cos(thetaBottom), 1.0f * sin(thetaBottom), 0.0f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f)
	});
	stepBack++;
}

void closeMouth() {
	player->getVertices()->erase(player->getVertices()->begin() + 1);
	player->getVertices()->pop_back();
	stepBack--;
}