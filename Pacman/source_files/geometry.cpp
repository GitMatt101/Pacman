#include "../header_files/geometry.hpp"
#include "../utils.hpp"

vector<Vertex> createCircle(float rx, float ry, int precision, vec4 color1, vec4 color2) {
	float step = 2 * PI / precision;
	vector<Vertex> vertices;
	vertices.push_back({
		vec3(0.0f, 0.0f, 0.0f),
		color1
	});
	for (int i = 0; i <= precision + 2; i++) {
		float angle = (float)i * step;
		vertices.push_back({
			vec3(rx * cos(angle), ry * sin(angle), 0.0f),
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
		float angle = (float)i * step;
		float x = rx * 16 * pow(sin(angle), 3);
		float y = ry * (13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle));
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

vector<Vertex> createAstroid(float rx, float ry, int precision, vec4 color1, vec4 color2) {
	float step = 2 * PI / precision;
	vector<Vertex> vertices;
	vertices.push_back({
		vec3(0.0f, 0.0f, 0.0f),
		vec4(color1)
		});
	for (int i = 0; i <= precision + 2; i++) {
		float angle = (float)i * step;
		float x = rx * pow(cos(angle), 3);
		float y = ry * pow(sin(angle), 3);
		vertices.push_back({
			vec3(x, y, 0.0f),
			color2
		});
	}
	return vertices;
}