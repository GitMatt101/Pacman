#pragma once
#include "../lib.hpp"
#include "geometry.hpp"

struct Hitbox {
	vec3 cornerBot;
	vec3 cornerTop;
};

class Shape {

	public:
		float x;
		float y;
		float xScale;
		float yScale;
		float rotation;
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
		pair<float, float> getScale();
		float getRotation();
		void move(float x, float y);
		void setScale(float x, float y);
		void setRotation(float rotation);
		pair<float, float> getSize();
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

	public:
		Player(vector<Vertex> vertices);
		void setRotation(float rotation);
		int getLives();
		void hit();
		MouthAnimationState getMouthState();
		void setMouthState(MouthAnimationState state);

};