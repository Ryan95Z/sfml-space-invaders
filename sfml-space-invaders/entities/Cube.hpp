#ifndef ENTITIES_CUBE_HPP
#define ENTITIES_CUBE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <SFML/OpenGL.hpp>

#include "../core/objects/GObject.hpp"
#include "../core/Shader.hpp"
#include "../core/Camera.hpp"

#include "../core/managers/EventManager.hpp"

#define NUM_VAO 1
#define NUM_VBO 1
#define NUM_POINTS 108

class Cube : public GObject
{
public:
	Cube();
	~Cube();

	virtual void draw();
	virtual void update(float dt);
	
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;

	void left(EventDetails *details);
	void right(EventDetails *details);
	void up(EventDetails *details);
	void down(EventDetails *details);

protected:
	glm::vec3 position;

private:
	float rotation;
	Camera camera;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	
	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projLoc;

	Shader *shader;
	GLuint vao[NUM_VAO];
	GLuint vbo[NUM_VBO];
	float vertices[NUM_POINTS] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
};

#endif // ENTITIES_CUBE_HPP