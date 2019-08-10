	#include "Triangle.hpp"

Triangle::Triangle()
{
	shader = new Shader(VERTEX_SHADER, FRAG_SHADER);

	glGenVertexArrays(NUM_VAOs, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(NUM_VBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
}

Triangle::~Triangle()
{
	glDeleteBuffers(NUM_VBOs, vbo);
	glDeleteVertexArrays(NUM_VAOs, vao);

	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
	
}

void Triangle::draw()
{
	glUseProgram(shader->id());

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
