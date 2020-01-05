#include "TextRenderer.hpp"

#include <glm/gtc/type_ptr.hpp>

#define NUM_VAO 1
#define NUM_VBO 1

TextRenderer::TextRenderer() : font_shader(nullptr)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
	if (font_shader != nullptr)
	{
		delete font_shader;
		font_shader = nullptr;
	}
}

void TextRenderer::render(TextDetails &details)
{
	glm::vec3 colour = details.colour;
	GLuint projLoc = glGetUniformLocation(font_shader->id(), "projection");
	GLuint colourLoc = glGetUniformLocation(font_shader->id(), "textColor");

	glUseProgram(font_shader->id());
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(details.projection));
	glUniform3f(colourLoc, colour.x, colour.y, colour.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator c;
	Characters char_set = details.char_set;
	for (c = details.text.begin(); c != details.text.end(); ++c)
	{
		Character ch = char_set[*c];
		GLfloat xpos = details.pos.x + ch.bearing.x * details.scale;
		GLfloat ypos = details.pos.y - (ch.size.y - ch.bearing.y) *  details.scale;

		GLfloat w = ch.size.x *  details.scale;
		GLfloat h = ch.size.y *  details.scale;

		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		details.pos.x += (ch.advance >> 6) *  details.scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
