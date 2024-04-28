#include "../header_files/scene_manager.hpp"
#include "../header_files/shapes.hpp"

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern Player* player;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;
extern GLuint resolutionUniform;
extern GLuint backgroundUniform;

void drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//glUniform3f(color1, c1.r, c1.g, c1.b);
	//glUniform3f(color2, c2.r, c2.g, c2.b);

	for (Shape* shape : scene)
	{
		*shape->getModel() = mat4(1.0);
		*shape->getModel() = translate(*shape->getModel(), vec3(shape->getPosition().first, shape->getPosition().second, 0.0f));
		*shape->getModel() = scale(*shape->getModel(), vec3(shape->getScale().first, shape->getScale().second, 1.0f));
		*shape->getModel() = rotate(*shape->getModel(), radians(shape->getRotation()), vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, value_ptr(*shape->getModel()));
		glUniform2f(resolutionUniform, width, height);
		if (shape->isBackgroundComponent())
			glUniform1i(backgroundUniform, 1);
		else
			glUniform1i(backgroundUniform, 0);
		//glUniform1f(currentFrame, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
		glBindVertexArray(*shape->getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, shape->getVertices()->size());
		glBindVertexArray(0);
	}
	//if (player->isAlive() && enemies.size() == 0)
	//	gameOver((char*)"YOU WIN");
	//else if (!player->isAlive())
	//	gameOver((char*)"YOU LOSE");
	//string str = "Enemies left: " + to_string(enemies.size());
	//renderText(programID_text, projectionMatrix, str, textVAO, textVBO, width - 12.0f * str.length(), height - walls[0]->getHeight() * walls[0]->getYScaleValue() * 2 - 10.0f, 0.5f, vec3(1.0f, 0.0f, 0.0f));
	glutSwapBuffers();
	glUseProgram(programID);
}

void updateShapes() {
	// TODO: check collision

	// if player is alive and at least one enemy is alive
	if (player->isAlive()) {
		// if enemies.size() > 0
		for (Shape* shape : scene)
			shape->updateVAO();
		// else change level
	} else {
		// TODO: gameover
	}

}