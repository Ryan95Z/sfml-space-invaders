#ifndef CORE_CAMERA_HPP
#define CORE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define FOV 45.0f

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 camera_pos);
	~Camera();

	void update(float dt);
	void move(Direction direction);

	glm::mat4 getLookUpMatrix() const;

protected:
	glm::vec3 camera_pos;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
};

#endif // CORE_CAMERA_HPP