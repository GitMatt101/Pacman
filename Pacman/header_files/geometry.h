#pragma once
#include "../lib.h"

struct Vertex {
	vec3 coordinates;
	vec4 color;
};

vector<Vertex> createCircle(float rx, float ry, int precision, vec4 color1, vec4 color2);

vector<Vertex> createHeart(float rx, float ry, int precision, vec4 color1, vec4 color2);

vector<Vertex> createRectangle(float width, float height, vec4 color1, vec4 color2);