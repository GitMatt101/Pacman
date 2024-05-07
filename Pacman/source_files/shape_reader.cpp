#include "../header_files/shape_reader.hpp"
#include "../header_files/hermite.hpp"

vector<Vertex> createHermiteShapeFromFile(char* fileName, vec4 color1, vec4 color2) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
		perror("ERROR: COULD NOT OPEN THE FILE");

	vector<vec3> data;
	float x, y, z;
	for (int row = 0; fscanf(file, "%f %f %f", &x, &y, &z) == 3; row++)
		data.push_back(vec3(x, y, z));

	fclose(file);

	return buildCurve(data, color1, color2);
}