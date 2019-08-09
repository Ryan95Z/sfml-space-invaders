#ifndef CORE_TRIANGLE_HPP
#define CORE_TRIANGLE_HPP

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

#define NUM_VAOs 1
#define NUM_VBOs 1

class Triangle
{
public:
	Triangle();
	~Triangle();

	void draw();
private:
	float verticies[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint vao[NUM_VAOs];
	GLuint vbo[NUM_VBOs];
};


#endif // CORE_TRIANGLE_HPP