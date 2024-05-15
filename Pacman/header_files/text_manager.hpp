#pragma once
#include "../lib.hpp"
#include <string>

/**
* Struct used to model a character to display on the screen.
* 
* @param textureID - ID handle of the glyph texture.
* @param size - Size of the glyph.
* @param bearing - Offset from baseline to top-left of glyph.
* @param offset - Horizontal offset to advance to the next glyph.
*/
struct Character {
	unsigned int textureID;
	ivec2 size;
	ivec2 bearing;
	unsigned int offset;
};

// Class used to display text on screen.
class TextManager {

	private:
		unsigned int vao;
		unsigned int vbo;
		int programID;

	public:
		/**
		* Basic constructor, initializes the program ID, text VAO and text VBO.
		* 
		* @param programID - The program's ID.
		*/
		TextManager(int programID);

		// Inits Freetype library, loading all characters with a font.
		void initFreetype();

		/**
		* Displays text on the screen.
		* 
		* @param textProjectionMatrix - The projection matrix used by shader file.
		* @param text - Text to be displayed.
		* @param x - Horizontal position of the text.
		* @param y - Vertical position of the text.
		* @param scale - Size of the text.
		* @param color - Color of the text.
		*/
		void renderText(mat4 textProjectionMatrix, string text, float x, float y, float scale, vec4 color);

};