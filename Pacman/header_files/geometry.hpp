#pragma once
#include "../lib.hpp"

/**
* Structure used for shapes' vertices.
* 
* @param coordinates - Position of the vertex.
* @param color - Color of the vertex.
*/
struct Vertex {
	vec3 coordinates;
	vec4 color;
};

/**
* Creates a circle.
*
* @param rx - Horizontal radius of the circle.
* @param ry - Vertical radius of the circle.
* @param precision - Number of vertices to create.
* @param color1 - Primary color.
* @param color2 - Secondary color.
* @returns A vector of vertices that create a circle.
*/
vector<Vertex> createCircle(float rx, float ry, int precision, vec4 color1, vec4 color2);

/**
* Creates a heart.
*
* @param rx - Horizontal radius of the heart.
* @param ry - Vertical radius of the heart.
* @param precision - Number of vertices to create.
* @param color1 - Primary color.
* @param color2 - Secondary color.
* @returns A vector of vertices that create a heart.
*/
vector<Vertex> createHeart(float rx, float ry, int precision, vec4 color1, vec4 color2);

/**
* Creates an Astroid.
*
* @param width - Width of the rectangle.
* @param height - Height of the rectangle.
* @param color1 - Primary color.
* @param color2 - Secondary color.
* @returns A vector of vertices that create a rectangle.
*/
vector<Vertex> createRectangle(float width, float height, vec4 color1, vec4 color2);

/**
* Creates an astroid.
* 
* @param rx - Horizontal radius of the astroid.
* @param ry - Vertical radius of the astroid.
* @param precision - Number of vertices to create.
* @param color1 - Primary color.
* @param color2 - Secondary color.
* @returns A vector of vertices that create an astroid.
*/
vector<Vertex> createAstroid(float rx, float ry, int precision, vec4 color1, vec4 color2);