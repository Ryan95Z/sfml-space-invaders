#include "Camera.hpp"

Camera::Camera() : camera_pos(glm::vec3(0.0f, 0.0f, 3.0f))
{
}

Camera::Camera(glm::vec3 camera_pos) : camera_pos(camera_pos)
{
}

Camera::~Camera()
{
}

void Camera::update(float dt)
{
}

void Camera::move(Direction direction)
{
	float speed = 0.05;
	if (direction == Direction::LEFT)
	{

	}

	if (direction == Direction::RIGHT)
	{

	}

	if (direction == Direction::UP)
	{

	}

	if (direction == Direction::DOWN)
	{

	}
}

glm::mat4 Camera::getLookUpMatrix() const
{
	return glm::lookAt(camera_pos, camera_front, camera_up);
}

