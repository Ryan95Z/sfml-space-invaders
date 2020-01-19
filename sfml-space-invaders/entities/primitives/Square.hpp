#ifndef ENTITIES_PRIMITIVES_SQUARE_HPP
#define ENTITIES_PRIMITIVES_SQUARE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../core/Shader.hpp"
#include "../../core/objects/GObject.hpp"

#define NUM_VERTICIES 12
#define NUM_INDICIES 6

#define NUM_VAOs 1
#define NUM_VBOs 1
#define NUM_EBOs 1

class Square : public GObject
{
public:
	Square();
	~Square();

	virtual void draw();
	virtual void update(float dt);

private:
	glm::vec2 pos;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;

	float verticies[NUM_VERTICIES] = {
		0.5f, 0.5f, 0.0f,		// top right
		0.5f, -0.5f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		// bottom left
		-0.5f, 0.5f, 0.0f		// top left
	};

	unsigned int indicies[NUM_INDICIES] = {
		0, 1, 3,	// first triangle
		1, 2, 3		// second triangle
	};

	GLuint modelLoc;
	GLuint projLoc;
	GLuint vao[NUM_VAOs];
	GLuint vbo[NUM_VBOs];
	GLuint ebo[NUM_EBOs];

	Shader *shader;
};

#endif // ENTITIES_PRIMITIVES_SQUARE_HPP