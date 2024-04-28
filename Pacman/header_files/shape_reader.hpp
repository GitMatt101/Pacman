#pragma once
#include "geometry.hpp"

void create_shape_from_file(char* fileName, Shape* shape, Shape* d);

vector<vec3> readPolygonVertices(char* fileName);