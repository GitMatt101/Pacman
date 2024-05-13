#pragma once
#include "../lib.hpp"
#include "geometry.hpp"

struct Hitbox {
	vec3 cornerBot;
	vec3 cornerTop;
};

enum Direction {
	UP, LEFT, DOWN, RIGHT, NONE
};

class Shape {

	public:
		float x;
		float y;
		float xScale;
		float yScale;
		float rotation;
		float initialX;
		float initialY;
		Direction direction;
		Hitbox hitbox;
		GLuint VAO;
		GLuint VBO_V;
		GLuint VBO_C;
		vector<Vertex> vertices;
		mat4 model;
		bool backgroundComponent;

	public:
		Shape(vector<Vertex> vertices);
		void initVAO();
		void updateVAO();
		GLuint* getVAO();
		GLuint* getVerticesVBO();
		GLuint* getColorsVBO();
		vector<Vertex>* getVertices();
		mat4* getModel();
		void setModel(mat4 model);
		pair<float, float> getPosition();
		pair<float, float> getInitialPosition();
		void setPosition(float x, float y);
		void move(float movement);
		pair<float, float> getScale();
		pair<float, float> getSize();
		void setScale(float x, float y);
		float getRotation();
		void setRotation(float rotation);
		Direction getDirection();
		void setDirection(Direction direction);
		Hitbox getHitbox();
		Hitbox getHitboxWorldCoordinates();
		bool isBackgroundComponent();
		void changePane();

};

class Entity : public Shape {

	private:
		bool alive;

	public:
		Entity(vector<Vertex> vertices);
		bool isAlive();
		void die();

};

enum MouthAnimationState { OPENING, CLOSING };

class Player : public Entity {

	private:
		int lives;
		MouthAnimationState mouthState;
		bool powerState;

	public:
		Player(vector<Vertex> vertices);
		void setRotation(float rotation);
		int getLives();
		void hit();
		MouthAnimationState getMouthState();
		void setMouthState(MouthAnimationState state);
		bool isPoweredUp();
		void setPowerState(bool state);

};