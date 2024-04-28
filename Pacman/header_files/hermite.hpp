#pragma once
#include "../lib.hpp"
#include "geometry.hpp"

#define PHI0(t)  (2.0f * pow(t, 3) - 3.0f * pow(t, 2) + 1.0f)
#define PHI1(t)  (pow(t, 3) - 2.0f * pow(t, 2) + t)
#define PSI0(t)  (-2.0f * pow(t, 3) + 3.0f * pow(t, 2))
#define PSI1(t)  (pow(t, 3) - pow(t, 2))

float dx(int i, vector<float> t, float tens, float bias, float cont, vector<vec3> controlPoints);

float dy(int i, vector<float> t, float tens, float bias, float cont, vector<vec3> controlPoints);

float DX(int i, vector<float> t, vector<vec3> derivativeControlPoints, vector<vec3> polygonalControlPoints);

float DY(int i, vector<float> t, vector<vec3> derivativeControlPoints, vector<vec3> polygonalControlPoints);

vector<Vertex> buildCurve(vector<vec3> controlPoints, vec4 color1, vec4 color2);