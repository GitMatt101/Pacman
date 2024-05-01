#include "../header_files/initializer.hpp"
#include "../header_files/shapes.hpp"
#include "../header_files/geometry.hpp"
#include "../header_files/shaders.hpp"
#include "../utils.hpp"

#define VERTEX_FILE "vertexShader_M.glsl"
#define FRAGMENT_FILE "fragmentShader_M.glsl"

#define VERTEX_FILE_TEXT "vertexShader_Text.glsl"
#define FRAGMENT_FILE_TEXT "fragmentShader_Text.glsl"

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern map<int, vector<Shape*>> levels;
extern Player* player;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

void createLevel1();

void initShaders() {
	programID = createProgram((char*)VERTEX_FILE, (char*)FRAGMENT_FILE);
	programID_text = createProgram((char*)VERTEX_FILE_TEXT, (char*)FRAGMENT_FILE_TEXT);

	glUseProgram(programID);
}

void initUniforms() {
	projectionMatrix = ortho(0.0f, float(width), 0.0f, float(height));

	projectionUniform = glGetUniformLocation(programID, "Projection");
	modelUniform = glGetUniformLocation(programID, "Model");
}

void initGame() {
	vector<Vertex> playerVertices = createCircle(1.0f, 1.0f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	for (int i = 0; i < 47; i++)
		playerVertices.pop_back();
	player = new Player(playerVertices);
	player->move((float)width / 2, (float)(height + scoreSpace) / 2);
	player->setRotation(45.0f);

	// TODO: create levels
	createLevel1();
}

void initLevel(int index) {
	// Unsets all VAOs and VBOs
	for (Shape* shape : scene) {
		glDeleteVertexArrays(1, shape->getVAO());
		glDeleteBuffers(1, shape->getVerticesVBO());
		glDeleteBuffers(1, shape->getColorsVBO());
	}
	scene.clear();

	player->initVAO();
	scene.push_back(player);
	for (Shape* wall : levels[index]) {
		wall->initVAO();
		scene.push_back(wall);
	}

	// TODO: add enemies
}

void createLevel1() {
	vector<Shape*> walls;
	Shape* wall;

	float levelHeight = height - scoreSpace;

	// Top wall
	wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale((float)width, NULL);
	wall->move((float)width / 2, (float)height - wall->getSize().second / 2);
	walls.push_back(wall);

	// Bottom wall
	wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale((float)width, NULL);
	wall->move((float)width / 2, wall->getSize().second / 2 + scoreSpace);
	walls.push_back(wall);

	// Top-Left wall
	wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale(NULL, levelHeight / 3);
	wall->move(wall->getSize().first / 2, (float)height - wall->getSize().second / 2);
	walls.push_back(wall);
	// Top-Right wall
	wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale(NULL, levelHeight / 3);
	wall->move((float)width - wall->getSize().first / 2, (float)height - wall->getSize().second / 2);
	walls.push_back(wall);

	// Bottom-Left wall
	wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale(NULL, levelHeight / 3);
	wall->move(wall->getSize().first / 2, wall->getSize().second / 2 + scoreSpace);
	walls.push_back(wall);
	// Bottom-Right wall
	wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	wall->setScale(NULL, levelHeight / 3);
	wall->move((float)width - wall->getSize().first / 2, wall->getSize().second / 2 + scoreSpace);
	walls.push_back(wall);

	// Values used to create the walls around the tunnels
	float distance;	// Distance from the screen's border
	float length;	// Additional length for some walls

	// Left tunnel walls
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move(wall->getSize().first / 2, levelHeight * 2 / 3 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move(wall->getSize().first / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move(wall->getSize().first / 2, levelHeight / 3 - wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move(wall->getSize().first / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		distance = wall->getSize().first;
		length = wall->getSize().second;

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move(distance - wall->getSize().first / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move(distance - wall->getSize().first / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);
	}

	// Right tunnel walls
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width - wall->getSize().first / 2, levelHeight * 2 / 3 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width - wall->getSize().first / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width - wall->getSize().first / 2, levelHeight / 3 - wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width - wall->getSize().first / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		distance = wall->getSize().first;
		length = wall->getSize().second;

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move((float)width - distance + wall->getSize().first / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move((float)width - distance + wall->getSize().first / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);
	}

	// Central Ts
	{
		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width / 2, levelHeight * 5 / 9 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(1.0f, 0.5f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale((float)width / 5, NULL);
		wall->move((float)width / 2, levelHeight * 4 / 9 - wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		length = wall->getSize().second;

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move((float)width / 2, levelHeight * 11 / 18 + wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);

		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight / 9 + length);
		wall->move((float)width / 2, levelHeight * 7 / 18 - wall->getSize().first / 2 + scoreSpace);
		walls.push_back(wall);
	}

	// Dividers
	{
		// Top-Left divider
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + length);
		wall->move((float)width * 3 / 10, levelHeight * 5 / 9 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		// Top-Right divider
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + length);
		wall->move((float)width * 7 / 10, levelHeight * 5 / 9 + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		// Bottom-Left divider
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + length);
		wall->move((float)width * 3 / 10, levelHeight * 2 / 9 - length + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);

		// Bottom-Right divider
		wall = new Shape(createRectangle(0.5f, 1.0f, vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f)));
		wall->setScale(NULL, levelHeight * 2 / 9 + length);
		wall->move((float)width * 7 / 10, levelHeight * 2 / 9 - length + wall->getSize().second / 2 + scoreSpace);
		walls.push_back(wall);
	}

	levels.insert({ 0, walls });
}

void createLevel2() {

}

void createLevel3() {

}

void createLevel4() {

}

void createLevel5() {

}