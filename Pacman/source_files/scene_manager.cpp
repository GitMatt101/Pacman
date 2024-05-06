#include "../header_files/scene_manager.hpp"
#include "../header_files/shapes.hpp"
#include "../header_files/animations.hpp"

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern Player* player;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

void drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (Shape* shape : scene)
	{
		shape->setModel(mat4(1.0));
		shape->setModel(translate(*shape->getModel(), vec3(shape->getPosition().first, shape->getPosition().second, 0.0f)));
		shape->setModel(scale(*shape->getModel(), vec3(shape->getScale().first, shape->getScale().second, 1.0f)));
		shape->setModel(rotate(*shape->getModel(), radians(shape->getRotation()), vec3(0.0f, 0.0f, 1.0f)));
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, value_ptr(*shape->getModel()));
		glBindVertexArray(*shape->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, shape->getVertices()->size());
		glBindVertexArray(0);
	}
	
	glutSwapBuffers();
	glUseProgram(programID);
}

void updateShapes(int value) {
	// TODO: check collision

	if (player->isAlive()) {
		for (Shape* shape : scene)
			shape->updateVAO();
		glutPostRedisplay();
		glutTimerFunc(17, updateShapes, 0);
	} else {
		// TODO: gameover
	}

}

void updateAnimations(int value) {
	switch (player->getMouthState()) {
		case OPENING:
			widenMouth();
			if (player->getVertices()->size() >= 180 + 2)	//TODO: create definition in utils
				player->setMouthState(CLOSING);
			break;
		case CLOSING:
			closeMouth();
			if (player->getVertices()->size() <= 135 + 2)	//TODO: create definition in utils
				player->setMouthState(OPENING);
			break;
		default:
			break;
	}

	glDeleteVertexArrays(1, player->getVAO());
	glDeleteBuffers(1, player->getVerticesVBO());
	glDeleteBuffers(1, player->getColorsVBO());
	player->initVAO();
	player->updateVAO();

	glutTimerFunc(10, updateAnimations, 1);
}