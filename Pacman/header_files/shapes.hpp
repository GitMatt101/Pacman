#pragma once
#include "../lib.hpp"
#include "geometry.hpp"

/**
* Struct used to model a shape's body as a square.
* 
* @param cornerBot - Bottom-Left corner of the hitbox.
* @param cornerTop - Top-Right corner of the hitbox.
*/
struct Hitbox {
	vec3 cornerBot;
	vec3 cornerTop;
};

// Enum used to keep track of the direction a shape faces.
enum Direction {
	UP, LEFT, DOWN, RIGHT, NONE
};

// Generic shape displayed on the screen.
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
		/**
		* Basic constructor, initializes all the necessary parameters.
		* 
		* @param vertices - Vertices of the shape.
		*/
		Shape(vector<Vertex> vertices);

		// Initializes the shape's VAO.
		void initVAO();

		// Updates the shape's VAO.
		void updateVAO();

		/**
		* Retrieves the shape's VAO.
		* 
		* @return Pointer to the shape's VAO.
		*/
		GLuint* getVAO();

		/**
		* Retrieves the shape's VBO of vertices.
		*
		* @return Pointer to the shape's VBO of vertices.
		*/
		GLuint* getVerticesVBO();

		/**
		* Retrieves the shape's VBO of colors.
		*
		* @return Pointer to the shape's VBO of colors.
		*/
		GLuint* getColorsVBO();

		/**
		* Retrieves the shape's vertices.
		* 
		* @return Pointer to the shape's vector of vertices.
		*/
		vector<Vertex>* getVertices();

		/**
		* Retrieves the shape's model matrix.
		*
		* @return Pointer to the shape's model matrix.
		*/
		mat4* getModel();

		/**
		* Changes the model matrix.
		* 
		* @param model - New model matrix.
		*/
		void setModel(mat4 model);

		/**
		* Retrieves the position of the shape's mid point.
		* 
		* @return A pair containing the coordinates of the shape's mid point.
		*/
		pair<float, float> getPosition();

		/**
		* Retrieves the initial position of the shape's mid point.
		*
		* @return A pair containing the coordinates of the shape's mid point when it was created.
		*/
		pair<float, float> getInitialPosition();

		/**
		* Changes the shape's position. If it's the first time it's called, the initial position is also set.
		* 
		* @param x - Horizontal value on the screen.
		* @param y - Vertical value on the screen.
		*/
		void setPosition(float x, float y);

		/**
		* Moves the shape along the current direction.
		* 
		* @param movement - Amount of pixels the shape has to move.
		*/
		void move(float movement);

		/**
		* Retrievs the scale of the shape.
		* 
		* @return A pair containing the scale values for width and height.
		*/
		pair<float, float> getScale();

		/**
		* Retrievs the size of the shape.
		*
		* @return A pair containing width and height of the shape.
		*/
		pair<float, float> getSize();

		/**
		* Changes the shape's scale.
		*
		* @param x - New horizontal scale.
		* @param y - New vertical scale.
		*/
		void setScale(float x, float y);

		/**
		* Retrieves the shape's rotation angle.
		* 
		* @return The shape's rotation angle.
		*/
		float getRotation();

		/**
		* Changes the shape's rotation angle.
		*
		* @param rotation - New rotation angle.
		*/
		void setRotation(float rotation);

		/**
		* Retrieves the direction the shape is currently facing.
		* 
		* @return Current direction.
		*/
		Direction getDirection();

		/**
		* Changes the shape's direction.
		*
		* @param direction - New direction.
		*/
		void setDirection(Direction direction);

		/**
		* Retrieves the shape's hitbox projected in the (-1, +1) square.
		*
		* @return The shape's hitbox.
		*/
		Hitbox getHitbox();

		/**
		* Retrieves the shape's hitbox projected into world coordinates (pixels on the screen).
		* 
		* @return The shape's hitbox.
		*/
		Hitbox getHitboxWorldCoordinates();

		/**
		* Checks if the shape is part of the background.
		* 
		* @return true if the shape is part of the background, false otherwise.
		*/
		bool isBackgroundComponent();

		// Switches the role of the shape as a background component.
		void changePane();

};

// Class used to model entities that can interact with the player.
class Entity : public Shape {

	private:
		bool alive;

	public:
		/**
		* Basic constructor that extends Shape constructor.
		* 
		* @param vertices - The entity's vertices that create the shape.
		*/
		Entity(vector<Vertex> vertices);

		/**
		* Checks if the entity is still alive.
		* 
		* @return true if it's alive, false otherwise.
		*/
		bool isAlive();

		// Kills the entity.
		void die();

};

// Enum used for pacman's mouth animation
enum MouthAnimationState { OPENING, CLOSING };

class Player : public Entity {

	private:
		int lives;
		MouthAnimationState mouthState;
		bool powerState;

	public:
		/**
		* Basic constructor, extends Entity constructor.
		* 
		* @param vertices - The player's vertices that create the shape.
		*/
		Player(vector<Vertex> vertices);

		/**
		* Changes the player's rotation angle, starting from a 45 degree angle.
		*
		* @param rotation - New rotation angle.
		*/
		void setRotation(float rotation);

		/**
		* Retrieves the number of lives the player has left.
		* 
		* @return Number of lives left.
		*/
		int getLives();

		// Decreases the number of lives. If the lives go down to 0 the player dies.
		void hit();

		/**
		* Retrieves the current state of the mouth animation.
		* 
		* @return Animation state
		*/
		MouthAnimationState getMouthState();

		/**
		* Changes the animation state.
		* 
		* @param state - New animation state.
		*/
		void setMouthState(MouthAnimationState state);

		/**
		* Checks if the player is powered up.
		* 
		* @return true if the player is powered up, false otherwise.
		*/
		bool isPoweredUp();

		/**
		* Changes the player's power state.
		* 
		* @param state - New state.
		*/
		void setPowerState(bool state);

};