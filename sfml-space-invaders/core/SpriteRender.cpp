#include "SpriteRender.hpp"

SpriteRender::SpriteRender()
{
	initSpriteRender();
}

SpriteRender::~SpriteRender()
{
	destroySpriteRender();
}

void SpriteRender::drawSprite(glm::vec2 position)
{
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRender::initSpriteRender()
{
	glGenVertexArrays(NUM_VAO, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(NUM_VBO, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void SpriteRender::destroySpriteRender()
{
	glDeleteVertexArrays(NUM_VAO, vao);
	glDeleteBuffers(NUM_VBO, vbo);
}
