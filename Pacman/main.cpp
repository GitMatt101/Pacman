#include "lib.hpp"
#include "utils.hpp"
#include "header_files/shapes.hpp"
#include "header_files/initializer.hpp"
#include "header_files/scene_manager.hpp"
#include "header_files/interactions.hpp"

GLuint programID, programID_text;

vector<Shape*> scene;
vector<Shape*> walls;
Player* player;
vector<Entity*> enemies;
vector<Entity*> powerUps;

mat4 projectionMatrix;

GLuint projectionUniform;
GLuint modelUniform;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition((SCREEN_WIDTH - WIDTH) / 2, (SCREEN_HEIGHT - HEIGHT) / 2 - 20);
	glutCreateWindow("Pacman");
	glutDisplayFunc(drawScene);
	glewExperimental = GL_TRUE;
	glewInit();
	initShaders();
	initUniforms();
	initGame();
	initLevel();
	//initTextVAO(&textVAO, &textVBO);
	//initFreetype();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutTimerFunc(17, updateShapes, 0);
	glutTimerFunc(10, updateAnimations, 0);
	glutKeyboardFunc(input);
	glutMainLoop();
}