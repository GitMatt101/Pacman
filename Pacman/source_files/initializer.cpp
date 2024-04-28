#include "../header_files/initializer.hpp"
#include "../header_files/shapes.hpp"
#include "../header_files/geometry.hpp"
#include "../header_files/shaders.hpp"

#define VERTEX_FILE "vertexShader_M.glsl"
#define FRAGMENT_FILE "fragmentShader_M.glsl"

#define VERTEX_FILE_TEXT "vertexShader_Text.glsl"
#define FRAGMENT_FILE_TEXT "fragmentShader_Text.glsl"

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern map<int, vector<Shape*>> levels;
extern Shape* player;

void initShaders() {
	char* vertexShader = (char*)VERTEX_FILE;
	char* fragmentShader = (char*)FRAGMENT_FILE;
	programID = createProgram(vertexShader, fragmentShader);
	glUseProgram(programID);

	vertexShader = (char*)VERTEX_FILE_TEXT;
	fragmentShader = (char*)FRAGMENT_FILE_TEXT;
	programID_text = createProgram(vertexShader, fragmentShader);
}

void initGame() {
	vector<Vertex> playerVertices = createCircle(0.5f, 0.5f, 100, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	playerVertices.pop_back();
	player = new Player(playerVertices);

	// TODO: create levels
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