#ifndef CORE_GUI_TEXT_RENDERER_HPP
#define CORE_GUI_TEXT_RENDERER_HPP

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "Font.hpp"
#include "../Shader.hpp"

struct TextDetails
{
	GLfloat scale;
	std::string text;
	glm::fvec2 pos;
	glm::vec3 colour;
	glm::mat4 projection;
	Characters char_set;
};

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();

	void render(TextDetails &details);

	static TextRenderer & getInstance();
private:
	GLuint vao;
	GLuint vbo;
	Shader *font_shader;
};

#endif // CORE_GUI_TEXT_RENDERER_HPP