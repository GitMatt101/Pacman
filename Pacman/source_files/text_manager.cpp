#include "../header_files/text_manager.hpp"
#include "../header_files/VAO_manager.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

map<GLchar, Character> characters;

TextManager::TextManager(int programID) {
	initTextVAO(&this->vao, &this->vbo);
	this->programID = programID;
}

void TextManager::initFreetype() {
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		exit(-1);
	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		exit(-1);
	else {
		FT_Set_Pixel_Sizes(face, 0, 48);			// set size to load glyphs as
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);		// disable byte-alignment restriction

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				continue;
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			characters.insert(pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextManager::renderText(mat4 textProjectionMatrix, string text, float x, float y, float scale, vec4 color) {
	glUseProgram(programID);	// activate corresponding render state
	glUniform3f(glGetUniformLocation(programID, "textColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projectionText"), 1, GL_FALSE, value_ptr(textProjectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->vao);

	string::const_iterator index;
	for (index = text.begin(); index != text.end(); index++)
	{
		Character ch = characters[*index];
		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		glBindTexture(GL_TEXTURE_2D, ch.textureID);	// render glyph texture over quad
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);	// render quad
		x += (ch.offset >> 6) * scale;		// bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}