#include "Cube.hpp"



#define VERTEX_SHADER "shaders/cube_vertex.glsl"
#define FRAG_SHADER "shaders/cube_frag.glsl"

Cube::Cube() : model(1.0f), view(1.0f), projection(1.0f), shader(nullptr), position(glm::vec3(0.0f, 0.0f, 0.0f))
{
	shader = new Shader(VERTEX_SHADER, FRAG_SHADER);

	glGenVertexArrays(NUM_VAO, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(NUM_VBO, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

	model = glm::mat4(1.0f);
	
	// Second param sets the position in world space
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	view = camera.getLookUpMatrix();
	projection = glm::perspective(glm::radians(FOV), (float)(800 / 800), 1.0f, 100.0f);

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
	model = glm::rotate(model, glm::radians(glm::sin(dt)), glm::vec3(1.0f, 0.0f, 0.0f));
	camera.update(dt);
}

void Cube::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Cube::getPosition() const
{
	return position;
}

void Cube::left(EventDetails * details)
{
	camera.move(Direction::LEFT);
}

void Cube::right(EventDetails * details)
{
	camera.move(Direction::RIGHT);
}

void Cube::up(EventDetails * details)
{
	camera.move(Direction::UP);
}

void Cube::down(EventDetails * details)
{
	camera.move(Direction::DOWN);
}


