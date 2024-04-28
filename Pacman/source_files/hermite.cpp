#include "../header_files/hermite.h"

#define P_VAL 100

#define PHI0(t)  (2.0f * pow(t, 3) - 3.0f * pow(t, 2) + 1.0f)
#define PHI1(t)  (pow(t, 3) - 2.0f * pow(t, 2) + t)
#define PSI0(t)  (-2.0f * pow(t, 3) + 3.0f * pow(t, 2))
#define PSI1(t)  (pow(t, 3) - pow(t, 2))

float dx(int i, vector<float> t, float tens, float bias, float cont, vector<vec3> controlPoints) {
	if (i == 0)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints[i + 1].x - controlPoints[i].x) / (t[i + 1] - t[i]);
	if (i == controlPoints.size() - 1)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints[i].x - controlPoints[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (controlPoints.at(i).x - controlPoints.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints.at(i + 1).x - controlPoints.at(i).x) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (controlPoints.at(i).x - controlPoints.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (controlPoints.at(i + 1).x - controlPoints.at(i).x) / (t[i + 1] - t[i]);
}

float dy(int i, vector<float> t, float tens, float bias, float cont, vector<vec3> controlPoints) {
	if (i == 0)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
	if (i == controlPoints.size() - 1)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints.at(i).y - controlPoints.at(i - 1.0).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (controlPoints.at(i).y - controlPoints.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (controlPoints.at(i).y - controlPoints.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
}

float DX(int i, vector<float> t, vector<vec3> derivativeControlPoints, vector<vec3> polygonalControlPoints) {
	if (derivativeControlPoints.at(i).x == 0)
		return dx(i, t, 0.0f, 0.0f, 0.0f, polygonalControlPoints);
	if (derivativeControlPoints.at(i).x != 0)
		return derivativeControlPoints.at(i).x;
}

float DY(int i, vector<float> t, vector<vec3> derivativeControlPoints, vector<vec3> polygonalControlPoints) {
	if (derivativeControlPoints.at(i).y == 0)
		return dy(i, t, 0.0f, 0.0f, 0.0f, polygonalControlPoints);
	if (derivativeControlPoints.at(i).y != 0)
		return derivativeControlPoints.at(i).y;
}

vector<Vertex> buildCurve(vector<vec3> controlPoints, vec4 color1, vec4 color2) {
	vector<vec3> derivative;
	vector<vec3> polygonal = controlPoints;
	vector<float> steps;
	for (int i = 0; i < polygonal.size(); i++)
		steps.push_back((float)i / (float)(polygonal.size() - 1));

	float p_t = 0, p_b = 0, p_c = 0;
	float passotg = 1.0f / (float)(P_VAL - 1);

	float tgmapp, width;
	int is = 0;

	for (int i = 0; i < controlPoints.size(); i++)
		derivative.push_back(vec3(0.0f, 0.0f, 0.0f));

	vector<Vertex> vertices;
	vertices.push_back({
		vec3(0.0f, 0.0f, 0.0f),
		color1
	});

	for (float tg = 0.0f; tg <= 1.0f; tg += passotg)
	{
		if (tg > steps[is + 1])
			is++;
		width = (steps[is + 1] - steps[is]);
		tgmapp = (tg - steps[is]) / width;

		float x = controlPoints[is].x * PHI0(tgmapp) + DX(is, steps, derivative, polygonal) * PHI1(tgmapp) * width + controlPoints[is + 1].x * PSI0(tgmapp) + DX(is + 1, steps, derivative, polygonal) * PSI1(tgmapp) * width;
		float y = controlPoints[is].y * PHI0(tgmapp) + DY(is, steps, derivative, polygonal) * PHI1(tgmapp) * width + controlPoints[is + 1].y * PSI0(tgmapp) + DY(is + 1, steps, derivative, polygonal) * PSI1(tgmapp) * width;

		vertices.push_back({
			vec3(x, y, 0.0f),
			color1
		});
	}
	vertices.push_back({
		controlPoints[controlPoints.size() - 1],
		color1
	});

	return vertices;
}