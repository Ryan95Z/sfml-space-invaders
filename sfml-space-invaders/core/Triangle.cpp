	#include "Triangle.hpp"

Triangle::Triangle()
{
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
}
