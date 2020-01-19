#ifndef CORE_GUI_FONT_HPP
#define CORE_GUI_FONT_HPP

#include <map>
#include <string>
#include <exception>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint texture_id;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};

using Characters = std::map<GLchar, Character>;

class NoFontException : public std::runtime_error
{
public:
	NoFontException(std::string msg) : std::runtime_error(msg) {}

	virtual const char * what() const throw()
	{
		return std::runtime_error::what();
	}
};

class Font
{
public:
	Font(Font &) = delete;
	Font();
	~Font();

	bool loadFromFile(std::string path);
	bool hasFontBeenLoaded() const;

	Characters getCharacters() const;

private:
	bool has_font;
	FT_Library ft;
	FT_Face face;
	Characters char_set;

};

#endif // !CORE_GUI_FONT_HPP