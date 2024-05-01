#include "../header_files/initializer.hpp"
#include "../header_files/shapes.hpp"
#include "../header_files/geometry.hpp"
#include "../header_files/shaders.hpp"

#define VERTEX_FILE "vertexShader_M.glsl"
#define FRAGMENT_FILE "fragmentShader_M.glsl"

#define VERTEX_FILE_TEXT "vertexShader_Text.glsl"
#define FRAGMENT_FILE_TEXT "fragmentShader_Text.glsl"

extern const int width;
extern const int height;

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern map<int, vector<Shape*>> levels;
extern Player* player;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

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
	vector<Vertex> playerVertices = createCircle(0.5f, 0.5f, 180, vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
	for (int i = 0; i < 47; i++)
		playerVertices.pop_back();
	player = new Player(playerVertices);
	player->move((float)width / 2, (float)height / 2);
	player->setRotation(45.0f);

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