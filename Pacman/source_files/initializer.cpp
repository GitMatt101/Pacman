#include "../header_files/initializer.hpp"
#include "../header_files/shapes.hpp"
#include "../header_files/geometry.hpp"
#include "../header_files/shape_reader.hpp"
#include "../header_files/shaders.hpp"
#include "../utils.hpp"
#include<ctime>

#define VERTEX_FILE "vertexShader_M.glsl"
#define FRAGMENT_FILE "fragmentShader_M.glsl"

#define VERTEX_FILE_TEXT "vertexShader_Text.glsl"
#define FRAGMENT_FILE_TEXT "fragmentShader_Text.glsl"

#define ENEMY_FILE "enemy.txt"

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern vector<Shape*> walls;
extern Player* player;
extern vector<Entity*> enemies;
extern vector<Entity*> powerUps;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

// Creates the level, positioning walls and enemies.
void createLevel();

// Updates all enemies' direction to make their movement random.
void updateEnemiesDirection(int);

void initShaders() {
	programID = createProgram((char*)VERTEX_FILE, (char*)FRAGMENT_FILE);
	programID_text = createProgram((char*)VERTEX_FILE_TEXT, (char*)FRAGMENT_FILE_TEXT);

	glUseProgram(programID);
}

void initUniforms() {
	projectionMatrix = ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);

	projectionUniform = glGetUniformLocation(programID, "Projection");
	modelUniform = glGetUniformLocation(programID, "Model");
}

void initGame() {
	srand(time(NULL));
	vector<Vertex> playerVertices = createCircle(CIRCLE_RADIUS, CIRCLE_RADIUS, CIRCLE_PRECISION, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	for (int i = 0; i < 47; i++)
		playerVertices.pop_back();
	player = new Player(playerVertices);
	createLevel();
}

void initLevel() {
	createLevel();
	// Unsets all VAOs and VBOs
	for (Shape* shape : scene) {
		glDeleteVertexArrays(1, shape->getVAO());
		glDeleteBuffers(1, shape->getVerticesVBO());
		glDeleteBuffers(1, shape->getColorsVBO());
		shape->setPosition(shape->getInitialPosition().first, shape->getInitialPosition().second);
	}
	scene.clear();

	player->initVAO();
	scene.push_back(player);
	for (Shape* wall : walls) {
		wall->initVAO();
		scene.push_back(wall);
	}

	for (Entity* enemy : enemies) {
		enemy->initVAO();
		enemy->setDirection(static_cast<Direction>(rand() % 4));
		scene.push_back(enemy);
	}
	glutTimerFunc(500, updateEnemiesDirection, 2);

	for (Entity* powerUp : powerUps) {
		powerUp->initVAO();
		scene.push_back(powerUp);
	}
}

void updateEnemiesDirection(int) {
	for (Entity* enemy: enemies)
		enemy->setDirection(static_cast<Direction>(rand() % 4));
	glutTimerFunc(rand() % 1500, updateEnemiesDirection, 2);
}

void createLevel() {
	walls.clear();
	Shape* wall;

	float levelHeight = HEIGHT - SCORE_SPACE;
	float thickness = (new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f))))->getSize().second;

	// Border walls
	{
		// Top
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH, NULL);
		wall->setPosition((float)WIDTH / 2, (float)HEIGHT - wall->getSize().second / 2);
		walls.push_back(wall);

		// Bottom
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH, NULL);
		wall->setPosition((float)WIDTH / 2, wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Top-Left
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 3);
		wall->setPosition(wall->getSize().first / 2, (float)HEIGHT - wall->getSize().second / 2);
		walls.push_back(wall);
		// Top-Right
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 3);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, (float)HEIGHT - wall->getSize().second / 2);
		walls.push_back(wall);

		// Bottom-Left
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 3);
		wall->setPosition(wall->getSize().first / 2, wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);
		// Bottom-Right
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 3);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	float distance;	// Distance from the screen's border

	// Left tunnel walls
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition(wall->getSize().first / 2, levelHeight * 2 / 3 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition(wall->getSize().first / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition(wall->getSize().first / 2, levelHeight / 3 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition(wall->getSize().first / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		distance = wall->getSize().first;

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition(distance - wall->getSize().first / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition(distance - wall->getSize().first / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	// Right tunnel walls
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, levelHeight * 2 / 3 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, levelHeight / 3 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH - wall->getSize().first / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		distance = wall->getSize().first;

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH - distance + wall->getSize().first / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH - distance + wall->getSize().first / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	// Central Ts
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	// Corner Ls
	{
		// Top-Left
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + thickness);
		wall->setPosition((float)WIDTH * 3 / 10, levelHeight * 5 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);
		
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 5 + thickness / 2, levelHeight * 7 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Top-Right
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + thickness);
		wall->setPosition((float)WIDTH * 7 / 10, levelHeight * 5 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH * 4 / 5 - thickness / 2, levelHeight * 7 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Bottom-Left
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + thickness);
		wall->setPosition((float)WIDTH * 3 / 10, levelHeight * 2 / 9 - thickness + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 5 + thickness / 2, levelHeight * 2 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Bottom-Right divider
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + thickness);
		wall->setPosition((float)WIDTH * 7 / 10, levelHeight * 2 / 9 - thickness + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH * 4 / 5 - thickness / 2, levelHeight * 2 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	// Cups
	{
		// Top cup
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight * 7 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH * 2 / 5 + thickness / 2, levelHeight * 13 / 18 + wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH * 3 / 5 - thickness / 2, levelHeight * 13 / 18 + wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Bottom cup
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH / 5, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight * 2 / 9 - wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH * 2 / 5 + thickness / 2, levelHeight * 5 / 18 - wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + thickness);
		wall->setPosition((float)WIDTH * 3 / 5 - thickness / 2, levelHeight * 5 / 18 - wall->getSize().first / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}

	// Dividers
	{
		// Top
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH * 4 / 5 - thickness, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight * 8 / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);

		// Bottom
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)WIDTH * 4 / 5 - thickness, NULL);
		wall->setPosition((float)WIDTH / 2, levelHeight / 9 + wall->getSize().second / 2 + SCORE_SPACE);
		walls.push_back(wall);
	}



	enemies.clear();
	Entity* enemy = new Entity(createHermiteShapeFromFile((char*)ENEMY_FILE, vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	enemy->setPosition((float)WIDTH / 15, levelHeight * 17 / 18 + SCORE_SPACE);
	enemies.push_back(enemy);

	enemy = new Entity(createHermiteShapeFromFile((char*)ENEMY_FILE, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	enemy->setPosition((float)WIDTH * 14 / 15, levelHeight * 17 / 18 + SCORE_SPACE);
	enemies.push_back(enemy);

	enemy = new Entity(createHermiteShapeFromFile((char*)ENEMY_FILE, vec4(0.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	enemy->setPosition((float)WIDTH / 15, levelHeight / 18 + SCORE_SPACE);
	enemies.push_back(enemy);

	enemy = new Entity(createHermiteShapeFromFile((char*)ENEMY_FILE, vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f)));
	enemy->setPosition((float)WIDTH * 14 / 15, levelHeight / 18 + SCORE_SPACE);
	enemies.push_back(enemy);



	powerUps.clear();
	Entity* powerUp = new Entity(createAstroid(1.0f, 1.0f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	powerUp->setPosition((float)WIDTH / 2, levelHeight * 13 / 18 + SCORE_SPACE);
	powerUps.push_back(powerUp);

	powerUp = new Entity(createAstroid(1.0f, 1.0f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	powerUp->setPosition((float)WIDTH / 2, levelHeight * 17 / 18 + SCORE_SPACE);
	powerUps.push_back(powerUp);

	powerUp = new Entity(createAstroid(1.0f, 1.0f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	powerUp->setPosition((float)WIDTH / 2, levelHeight * 5 / 18 + SCORE_SPACE);
	powerUps.push_back(powerUp);

	powerUp = new Entity(createAstroid(1.0f, 1.0f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	powerUp->setPosition((float)WIDTH / 2, levelHeight / 18 + SCORE_SPACE);
	powerUps.push_back(powerUp);
}