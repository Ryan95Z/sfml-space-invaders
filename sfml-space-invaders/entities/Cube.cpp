#include "Cube.hpp"



#define VERTEX_SHADER "shaders/cube_vertex.glsl"
#define FRAG_SHADER "shaders/cube_frag.glsl"

Cube::Cube() : model(1.0f), view(1.0f), projection(1.0f), shader(nullptr)
{
	shader = new Shader(VERTEX_SHADER, FRAG_SHADER);

	glGenVertexArrays(NUM_VAO, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(NUM_VBO, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	/*view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/
	view = camera.getLookUpMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float) (800 / 800), 1.0f, 100.0f);	
}

Cube::~Cube()
{
	if (shader != nullptr)
	{
		delete shader;
		nullptr;
	}
}

void Cube::draw()
{
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shader->id());

	view = camera.getLookUpMatrix();

	// Get the model, view and projection uniform locations
	modelLoc = glGetUniformLocation(shader->id(), "model");
	viewLoc = glGetUniformLocation(shader->id(), "view");
	projLoc = glGetUniformLocation(shader->id(), "projection");

	// load the model matrix into the shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	
	// load the view matrix into the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// load the projection matrix into the shader
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::update(float dt)
{

}


