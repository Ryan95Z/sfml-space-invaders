#ifndef CORE_TRIANGLE_HPP
#define CORE_TRIANGLE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "Shader.hpp"

#define NUM_VAOs 1
#define NUM_VBOs 1

#define VERTEX_SHADER "shaders/vertex.glsl"
#define FRAG_SHADER "shaders/frag.glsl"

class Triangle
{
public:
	Triangle();
	Triangle(Triangle &) = delete;
	~Triangle();

	void draw();
private:
	float verticies[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	Shader *shader;
	GLuint vao[NUM_VAOs];
	GLuint vbo[NUM_VBOs];
};


#endif // CORE_TRIANGLE_HPP