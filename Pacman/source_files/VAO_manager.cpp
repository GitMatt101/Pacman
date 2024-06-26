#include "../header_files/VAO_manager.hpp"

void initShapeVAO(Shape* shape) {
	glGenVertexArrays(1, shape->getVAO());
	glBindVertexArray(*shape->getVAO());
	glGenBuffers(1, shape->getVerticesVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getVerticesVBO());
	glBufferData(GL_ARRAY_BUFFER, shape->getVertices()->size() * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, shape->getColorsVBO());
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getColorsVBO());
	glBufferData(GL_ARRAY_BUFFER, shape->getVertices()->size() * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void updateShapeVAO(Shape* shape) {
	vector<vec3> coordinates;
	vector<vec4> colors;
	for (Vertex vertex : *shape->getVertices()) {
		coordinates.push_back(vertex.coordinates);
		colors.push_back(vertex.color);
	}
	glBindVertexArray(*shape->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getVerticesVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->getVertices()->size() * sizeof(vec3), coordinates.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *shape->getColorsVBO());
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape->getVertices()->size() * sizeof(vec4), colors.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void initTextVAO(GLuint* textVAO, GLuint* textVBO) {
	glGenVertexArrays(1, textVAO);
	glGenBuffers(1, textVBO);
	glBindVertexArray(*textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}