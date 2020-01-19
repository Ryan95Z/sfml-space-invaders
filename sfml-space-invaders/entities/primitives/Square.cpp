#include "Square.hpp"

#define VERTEX_SHADER "shaders/square_vertex.glsl"
#define FRAG_SHADER "shaders/frag.glsl"

Square::Square() : shader(nullptr), model(1.0f), view(1.0f), proj(1.0f)
{
	shader = new Shader(VERTEX_SHADER, FRAG_SHADER);

	// Create the Vertex Array Object
	glGenVertexArrays(NUM_VAOs, vao);
	glBindVertexArray(vao[0]);

	// Create the Vertex Buffer Object
	glGenBuffers(NUM_VBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// Create the Element Buffer Objects
	glGenBuffers(NUM_EBOs, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}

Square::~Square()
{
	// Destroy the buffers
	glDeleteVertexArrays(NUM_VAOs, vao);
	glDeleteBuffers(NUM_VBOs, vbo);
	glDeleteBuffers(NUM_EBOs, ebo);

	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}

void Square::draw()
{
	glUseProgram(shader->id());

	modelLoc = glGetUniformLocation(shader->id(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	projLoc = glGetUniformLocation(shader->id(), "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(vao[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::mat4(1.0f);
}

void Square::update(float dt)
{
	proj = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);
	model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f));
	model = glm::scale(model, glm::vec3(50.0f, 50.0f, 0.0f));
}
