#pragma once
#include "geometry.hpp"

/**
* Reads the control points from a file and creates a Hermite curve.
* 
* @param fileName - Name of the file containing the control points.
* @param color1 - Primary color.
* @param color2 - Secondary color.
* @return The vertices of the Hermite curve.
*/
vector<Vertex> createHermiteShapeFromFile(char* fileName, vec4 color1, vec4 color2);