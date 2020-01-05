#include <iostream>
#include <fstream>
#include "Font.hpp"

#define ASCII_NUM_CHARS 128

Font::Font() : has_font(false)
{
}

Font::~Font()
{
}

bool Font::loadFromFile(std::string path)
{
	std::fstream file(path);
	if (!file.good())
	{
		std::cout << "Font file does not exist!\n";
		return false;
	}

	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Error: Freetype could not be initialized\n";
		return false;
	}

	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		std::cout << "Error: Could not load font file\n";
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < ASCII_NUM_CHARS; ++c)
	{
		// load the character
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Error: Could not load character glyph\n";
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		char_set.insert(std::pair<GLchar, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_FreeType(ft);
	FT_Done_Face(face);
	has_font = true;
	return true;
}

bool Font::hasFontBeenLoaded() const
{
	return has_font;
}

Characters Font::getCharacters() const
{
	if (!has_font)
	{
		throw new NoFontException("A font file was not provided!");
	}
	return Characters();
}
