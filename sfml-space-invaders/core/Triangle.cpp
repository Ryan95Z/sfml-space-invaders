	#include "Triangle.hpp"

Triangle::Triangle() : rotation(0.0f)
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

	GLuint transformLoc = glGetUniformLocation(shader->id(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::update(float dt)
{
	rotation = (float)((int)rotation + 1 % 360);
	trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0f));
}