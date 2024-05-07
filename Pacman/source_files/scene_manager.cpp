#include "../header_files/scene_manager.hpp"
#include "../header_files/animations.hpp"
#include "../header_files/interactions.hpp"
#include "../utils.hpp"

#define DEFAULT_MOVEMENT 5.0f

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern Player* player;
extern vector<Entity*> enemies;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

/**
* Moves an entity, following the direction it is currently facing.
* 
* @param entity - The entity to be moved.
*/ 
void moveEntity(Entity* entity);

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
	if (player->isAlive()) {
		moveEntity(player);
		for (Entity* enemy : enemies)
			moveEntity(enemy);
		for (Shape* shape : scene)
			shape->updateVAO();
		glutPostRedisplay();
		glutTimerFunc(17, updateShapes, 0);
	} else {
		// TODO: gameover
	}

}

void moveEntity(Entity* entity) {
	switch (entity->direction) {
		case UP:	// UP
			if (!checkWallCollision(entity, 0.0f, DEFAULT_MOVEMENT))
				entity->move(DEFAULT_MOVEMENT);
			// If the entity goes too far up he teleports to the bottom
			if (entity->getPosition().second > (float)HEIGHT)
				entity->setPosition(entity->getPosition().first, SCORE_SPACE);
			break;
		case LEFT:	// LEFT
			if (!checkWallCollision(entity, -DEFAULT_MOVEMENT, 0.0f))
				entity->move(DEFAULT_MOVEMENT);
			// If the entity goes too far left he teleports to the right
			if (entity->getPosition().first < 0.0f)
				entity->setPosition((float)WIDTH, entity->getPosition().second);
			break;
		case DOWN:	// DOWN
			if (!checkWallCollision(entity, 0.0f, -DEFAULT_MOVEMENT))
				entity->move(DEFAULT_MOVEMENT);
			// If the entity goes too far down he teleports to the top
			if (entity->getPosition().second < (float)SCORE_SPACE)
				entity->setPosition(entity->getPosition().first, (float)HEIGHT);
			break;
		case RIGHT:	// RIGHT
			if (!checkWallCollision(entity, DEFAULT_MOVEMENT, 0.0f))
				entity->move(DEFAULT_MOVEMENT);
			// If the entity goes too far right he teleports to the left
			if (entity->getPosition().first > (float)WIDTH)
				entity->setPosition(0.0f, entity->getPosition().second);
			break;
		default:
			break;
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