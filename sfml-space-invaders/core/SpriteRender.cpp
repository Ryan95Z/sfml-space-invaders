#include "SpriteRender.hpp"

#define VERTEX_SHADER "shaders/square_vertex.glsl"
#define FRAG_SHADER "shaders/square.frag"

#include <iostream>

SpriteRender::SpriteRender() : model(1.0f), proj(1.0f), shader(nullptr), texture_shader(nullptr)
{
	initSpriteRender();
}

SpriteRender::~SpriteRender()
{
	destroySpriteRender();
}

void SpriteRender::drawSprite(glm::vec2 position, glm::vec2 size, glm::vec3 colour)
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	
	// Set the origin to be the middle of the object
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));

	proj = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);

	// Activate the sprite shader
	glUseProgram(shader->id());

	// Get the shader variable locations
	modelLoc = glGetUniformLocation(shader->id(), "model");
	projLoc = glGetUniformLocation(shader->id(), "proj");
	colourLoc = glGetUniformLocation(shader->id(), "spriteColour");

	// Set the shader data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniform3f(colourLoc, colour.x, colour.y, colour.z);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRender::drawSprite(glm::vec2 position, glm::vec2 size, glm::vec3 colour, Texture * texture)
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));

	// Set the origin to be the middle of the object
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));

	proj = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);

	// Activate the sprite shader
	glUseProgram(shader->id());

	// Get the shader variable locations
	modelLoc = glGetUniformLocation(shader->id(), "model");
	projLoc = glGetUniformLocation(shader->id(), "proj");
	colourLoc = glGetUniformLocation(shader->id(), "spriteColour");

	// Set the shader data
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniform3f(colourLoc, colour.x, colour.y, colour.z);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRender::drawSprite(Sprite * sprite)
{
	if (sprite->hasTexture())
	{
		drawSprite(sprite->getPosition(), sprite->getSize(), sprite->getColour(), sprite->getTexture());;
	}
	else
	{
		drawSprite(sprite->getPosition(), sprite->getSize(), sprite->getColour());
	}
	
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

	shader = new Shader(VERTEX_SHADER, FRAG_SHADER);
}

void SpriteRender::destroySpriteRender()
{
	glDeleteVertexArrays(NUM_VAO, vao);
	glDeleteBuffers(NUM_VBO, vbo);

	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}

	if (texture_shader != nullptr)
	{
		delete texture_shader;
		texture_shader = nullptr;
	}
}
