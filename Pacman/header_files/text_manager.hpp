#pragma once
#include "../lib.hpp"
#include <string>

struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	ivec2   size;			// Size of glyph
	ivec2   bearing;		// Offset from baseline to left/top of glyph
	unsigned int offset;	// Horizontal offset to advance to next glyph
};

class TextManager {

	private:
		unsigned int vao;
		unsigned int vbo;
		int programID;

	public:
		TextManager(int programID);
		void initFreetype();
		void renderText(mat4 textProjectionMatrix, string text, float x, float y, float scale, vec4 color);

};