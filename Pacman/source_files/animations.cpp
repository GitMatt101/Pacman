#include "../header_files/animations.hpp"
#include "../header_files/shapes.hpp"
#include "../utils.hpp"

extern Player* player;

static int stepBack = 1;

void widenMouth() {
	float step = 2 * PI / CIRCLE_PRECISION;
	float thetaTop = ((float)player->getVertices()->size() - 135.0f - (float)stepBack) * (-step);
	float thetaBottom = ((float)player->getVertices()->size() - (float)stepBack) * step ;
	player->getVertices()->insert(player->getVertices()->begin() + 1, {
		vec3(CIRCLE_RADIUS * cos(thetaTop), CIRCLE_RADIUS * sin(thetaTop), 0.0f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f)
	});
	player->getVertices()->push_back({
		vec3(CIRCLE_RADIUS * cos(thetaBottom), CIRCLE_RADIUS * sin(thetaBottom), 0.0f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f)
	});
	stepBack++;
}

void closeMouth() {
	player->getVertices()->erase(player->getVertices()->begin() + 1);
	player->getVertices()->pop_back();
	stepBack--;
}