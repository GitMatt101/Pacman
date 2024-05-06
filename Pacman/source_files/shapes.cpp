#include "../header_files/shapes.hpp"
#include "../header_files/VAO_manager.hpp"
#include "../utils.hpp"

#define DEFAULT_SCALE 25.0f
#define DEFAULT_LIVES 3

/*
* -------------------------------------------------------------------------------
*							Shape implementation
* -------------------------------------------------------------------------------
*/

Shape::Shape(vector<Vertex> vertices) {
	this->vertices = vertices;
	this->x = 0.0f;
	this->y = 0.0f;
	this->xScale = DEFAULT_SCALE;
	this->yScale = DEFAULT_SCALE;
	this->rotation = 0;
	this->backgroundComponent = false;

	float xMin = this->vertices[0].coordinates.x;
	float yMin = this->vertices[0].coordinates.y;
	float xMax = this->vertices[0].coordinates.x;
	float yMax = this->vertices[0].coordinates.y;
	for (Vertex vertex : this->vertices)
	{
		if (vertex.coordinates.x < xMin)
			xMin = vertex.coordinates.x;
		else if (vertex.coordinates.x > xMax)
			xMax = vertex.coordinates.x;
		if (vertex.coordinates.y < yMin)
			yMin = vertex.coordinates.y;
		else if (vertex.coordinates.y > yMax)
			yMax = vertex.coordinates.y;
	}
	this->hitbox.cornerBot = vec3(xMin, yMin, 0.0f);
	this->hitbox.cornerTop = vec3(xMax, yMax, 0.0f);
}

void Shape::initVAO() {
	initShapeVAO(this);
}

void Shape::updateVAO() {
	updateShapeVAO(this);
}

GLuint* Shape::getVAO() {
	return &(this->VAO);
}

GLuint* Shape::getVerticesVBO() {
	return &(this->VBO_V);
}

GLuint* Shape::getColorsVBO() {
	return &(this->VBO_C);
}

vector<Vertex>* Shape::getVertices() {
	return &(this->vertices);
}

mat4* Shape::getModel() {
	return &(this->model);
}

void Shape::setModel(mat4 model) {
	this->model = model;
}

pair<float, float> Shape::getPosition() {
	return { this->x, this->y };
}

pair<float, float> Shape::getScale() {
	return {
		this->xScale,
		this->yScale
	};
}

float Shape::getRotation() {
	return this->rotation;
}

void Shape::move(float x, float y) {
	if (x != NULL)
		this->x += x;
	if (y != NULL)
		this->y += y;
}

void Shape::setScale(float x, float y) {
	if (x != NULL)
		this->xScale = x;
	if (y != NULL)
		this->yScale = y;
}

void Shape::setRotation(float rotation) {
	this->rotation = rotation;
}

pair<float, float> Shape::getSize() {
	return {
		abs(hitbox.cornerTop.x - hitbox.cornerBot.x) * xScale,
		abs(hitbox.cornerTop.y - hitbox.cornerBot.y) * yScale
	};
}

Hitbox Shape::getHitbox() {
	return this->hitbox;
}

Hitbox Shape::getHitboxWorldCoordinates() {
	float xBottom = (float)WIDTH / 2 + this->hitbox.cornerBot.x * this->xScale + this->x;
	float yBottom = (float)HEIGHT / 2 + this->hitbox.cornerBot.y * this->yScale + this->y;
	float xTop = (float)WIDTH / 2 + this->hitbox.cornerTop.x * this->xScale + this->x;
	float yTop = (float)HEIGHT / 2 + this->hitbox.cornerTop.y * this->yScale + this->y;
	return {
		vec3(xBottom, yBottom, 0.0f),
		vec3(xTop, yTop, 0.0f)
	};
}

bool Shape::isBackgroundComponent() {
	return this->backgroundComponent;
}

void Shape::changePane() {
	this->backgroundComponent = !this->backgroundComponent;
}



/*
* -------------------------------------------------------------------------------
*							Entity implementation
* -------------------------------------------------------------------------------
*/

Entity::Entity(vector<Vertex> vertices) : Shape(vertices) {
	this->alive = true;
}

bool Entity::isAlive() {
	return this->alive;
}

void Entity::die() {
	this->alive = false;
}



/*
* -------------------------------------------------------------------------------
*							Player implementation
* -------------------------------------------------------------------------------
*/

Player::Player(vector<Vertex> vertices) : Entity(vertices) {
	this->lives = DEFAULT_LIVES;
	this->rotation = 45.0f;
	this->x = (float)WIDTH / 2;
	this->y = (float)(HEIGHT - SCORE_SPACE) / 2;
}

void Player::setRotation(float rotation) {
	this->rotation = 45.0f + rotation;
}

int Player::getLives() {
	return this->lives;
}

void Player::hit() {
	this->lives--;
	if (this->lives == 0)
		this->die();
}