#include "../header_files/geometry.h"

#define PI 3.14159265358979323846

vector<Vertex> createCircle(float rx, float ry, int precision, vec4 color1, vec4 color2) {
	float step = 2 * PI / precision;
	vector<Vertex> vertices;
	vertices.push_back({
		vec3(0.0f, 0.0f, 0.0f),
		color1
	});
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		vertices.push_back({
			vec3(rx * cos(theta_i), ry * sin(theta_i), 0.0f),
			color2
		});
	}
	return vertices;
}

vector<Vertex> createHeart(float rx, float ry, int precision, vec4 color1, vec4 color2) {
	float step = 2 * PI / precision;
	vector<Vertex> vertices;
	vertices.push_back({
		vec3(0.0f, 0.0f, 0.0f),
		vec4(color1)
	});
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		float x = rx * 16 * pow(sin(theta_i), 3);
		float y = ry * (13 * cos(theta_i) - 5 * cos(2 * theta_i) - 2 * cos(3 * theta_i) - cos(4 * theta_i));
		vertices.push_back({
			vec3(x, y, 0.0f),
			color2
		});
	}
	return vertices;
}

vector<Vertex> createRectangle(float width, float height, vec4 color1, vec4 color2) {
	vector<Vertex> vertices;
	vertices.push_back({
		vec3(width / 2, -height / 2, 0.0f),
		color1
	});
	vertices.push_back({
		vec3(width / 2, height / 2, 0.0f),
		color2
	});
	vertices.push_back({
		vec3(-width / 2, height / 2, 0.0f),
		color1
	});
	vertices.push_back({
		vec3(-width / 2, -height / 2, 0.0f),
		color2
	});
	return vertices;
}