#ifndef CORE_SPRITE_RENDER_HPP
#define CORE_SPRITE_RENDER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define NUM_VAO 1
#define NUM_VBO 1

#define VERTICES 30

class SpriteRender
{
public:
	SpriteRender();
	~SpriteRender();

	void drawSprite(glm::vec2 position);

private:
	void initSpriteRender();
	void destroySpriteRender();

	glm::mat4 model;
	glm::mat4 proj;
	GLuint vao[NUM_VAO];
	GLuint vbo[NUM_VBO];

	float vertices[VERTICES] = {
		// Pos				// Tex
		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 0.0f
	};
};

#endif // CORE_SPRITE_RENDER_HPP