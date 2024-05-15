#version 330 core
in vec4 color;
out vec4 fragColor;

uniform vec2 resolution;
uniform float scoreSpace;
uniform int background;
uniform vec3 color1;
uniform vec3 color2;
uniform float time;

bool isInRectangle(float left, float right, float bottom, float top, float thickness, float x, float y) {
	float animationValue = thickness;
	if (!(x > left - cos(time) * animationValue - thickness && x < right + cos(time) * animationValue + thickness))
		return false;
	if (!(y > bottom - cos(time) * animationValue - thickness && y < top + cos(time) * animationValue + thickness))
		return false;
	if ((x > left && x < right) && (y > bottom && y < top))
		return false;
	return true;
}
   
void main()
{
	if (background == 0)
		fragColor = color;
	else {
		float numberOfStripes = 20.0f;
		vec2 ndc = vec2 ((gl_FragCoord.x / resolution.x - 0.5) * 2, ((gl_FragCoord.y - scoreSpace) / resolution.y - 0.5) * 2);
		float step = 1 / numberOfStripes;
		for (int i = 0; i < numberOfStripes; i+=2) {
			if (isInRectangle(-i * step, i * step, -i * step, i * step, step, ndc.x, ndc.y)) {
				fragColor = vec4(color1, 1.0f);
				break;
			}
			else
				fragColor = vec4(color2, 1.0f);
		}
	}
}