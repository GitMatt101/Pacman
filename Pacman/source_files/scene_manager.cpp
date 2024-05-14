#include "../header_files/scene_manager.hpp"
#include "../header_files/animations.hpp"
#include "../header_files/interactions.hpp"
#include "../header_files/initializer.hpp"
#include "../header_files/text_manager.hpp"
#include "../utils.hpp"

#define DEFAULT_MOVEMENT 5.0f

#define POWERUP_COUNTDOWN 1500

extern GLuint programID;
extern GLuint programID_text;

extern vector<Shape*> scene;
extern Player* player;
extern vector<Entity*> enemies;
extern vector<Entity*> powerUps;
extern vector<Shape*> lives;

extern mat4 projectionMatrix;

extern GLuint projectionUniform;
extern GLuint modelUniform;

extern TextManager* textManager;

/**
* Moves an entity, following the direction it is currently facing.
* 
* @param entity - The entity to be moved.
*/ 
void moveEntity(Entity* entity);

// Checks if the player hit an enemy, if he did he loses one life and the level is reset.
void checkPlayerHit();

// Checks if the player ate a power.
void checkPowerUpEaten();

// Used to count down the power up duration.
void powerUpCountdown(int);

/**
* Removes an entity from a vector.
* 
* @param entity - Entity to be removed.
* @param vector - Vector to remove the entity from.
*/
void removeEntityFromVector(Entity* entity, vector<Entity*>* entityVector);

// Lose a life, removing it from the scene.
void loseLife();

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
	if (!player->isAlive())
		textManager->renderText(projectionMatrix, "GAME OVER", (float)WIDTH / 2 - 145.0f, (float)HEIGHT / 2, 1.0f, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	glutSwapBuffers();
	glUseProgram(programID);
}

void updateShapes(int) {
	if (player->isAlive()) {
		moveEntity(player);
		for (Entity* enemy : enemies) {
			if (enemy->isAlive())
				moveEntity(enemy);
			else
				removeEntityFromVector(enemy, &enemies);
		}
		for (Entity* powerUp : powerUps) {
			if (powerUp->isAlive())
				moveEntity(powerUp);
			else
				removeEntityFromVector(powerUp, &powerUps);
		}
		for (Shape* shape : scene)
			shape->updateVAO();
		glutPostRedisplay();
		glutTimerFunc(17, updateShapes, 0);
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
	checkPowerUpEaten();
	checkPlayerHit();
}

void updateAnimations(int) {
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

	glutTimerFunc(10, updateAnimations, 0);
}

void checkPlayerHit() {
	if (!player->isAlive())
		return;
	for (Entity* enemy : enemies) {
		if (checkCollision(enemy)) {
			if (player->isPoweredUp()) {
				enemy->die();
			} else {
				player->hit();
				loseLife();
				if (player->isAlive())
					initLevel();
			}
		}
	}
}

void checkPowerUpEaten() {
	for (Entity* powerUp : powerUps) {
		if (checkCollision(powerUp)) {
			player->setPowerState(true);
			powerUp->die();
			glutTimerFunc(1, powerUpCountdown, 0);
		}
	}
}

void powerUpCountdown(int) {
	static int elapsedTime = 0;
	if (!player->isPoweredUp())
		return;
	if (elapsedTime >= POWERUP_COUNTDOWN) {
		elapsedTime = 0;
		player->setPowerState(false);
	} else {
		elapsedTime++;
		glutTimerFunc(17, powerUpCountdown, 0);
	}
}

void loseLife() {
	Shape* life = lives[lives.size() - 1];
	vector<Shape*>::iterator sceneIndex = find(scene.begin(), scene.end(), life);
	lives.erase(lives.end() - 1);
	scene.erase(sceneIndex);
	glDeleteVertexArrays(1, life->getVAO());
	glDeleteBuffers(1, life->getVerticesVBO());
	glDeleteBuffers(1, life->getColorsVBO());
	delete(life);
}

void removeEntityFromVector(Entity* entity, vector<Entity*>* entityVector) {
	vector<Entity*>::iterator vectorIndex = find(entityVector->begin(), entityVector->end(), entity);
	vector<Shape*>::iterator sceneIndex = find(scene.begin(), scene.end(), entity);
	entityVector->erase(vectorIndex);
	scene.erase(sceneIndex);
	glDeleteVertexArrays(1, entity->getVAO());
	glDeleteBuffers(1, entity->getVerticesVBO());
	glDeleteBuffers(1, entity->getColorsVBO());
	delete(entity);
}