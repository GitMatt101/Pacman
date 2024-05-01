#include "lib.hpp"
#include "header_files/shapes.hpp"
#include "header_files/initializer.hpp"
#include "header_files/scene_manager.hpp"

const int width = 800;
const int height = 800;

GLuint programID, programID_text;

vector<Shape*> scene;
map<int, vector<Shape*>> levels;
Player* player;

mat4 projectionMatrix;

GLuint projectionUniform;
GLuint modelUniform;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Pacman");
	glutDisplayFunc(drawScene);
	glewExperimental = GL_TRUE;
	glewInit();
	initShaders();
	initUniforms();
	initGame();
	initLevel(0);
	//initTextVAO(&textVAO, &textVBO);
	//initFreetype();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutTimerFunc(17, updateShapes, 0);
	//glutKeyboardFunc(keyboard);
	//glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();
}