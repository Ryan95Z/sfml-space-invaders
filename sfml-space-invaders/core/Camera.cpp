#include "Camera.hpp"

Camera::Camera() : camera_pos(glm::vec3(0.0f, 0.0f, 3.0f))
{
	setUp();
}

Camera::Camera(glm::vec3 camera_pos) : camera_pos(camera_pos)
{
	setUp();
}

Camera::~Camera()
{
}

void Camera::update(float dt)
{
}

void Camera::move(Direction direction)
{
	float speed = 0.55;
	if (direction == Direction::LEFT)
	{
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * speed;
	}

	if (direction == Direction::RIGHT)
	{
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * speed;
	}

	if (direction == Direction::UP)
	{
		camera_pos += speed * camera_front;
	}

	if (direction == Direction::DOWN)
	{
		camera_pos -= speed * camera_front;
	}

	logger.vec3(camera_pos);
}

glm::mat4 Camera::getLookUpMatrix() const
{
	return glm::lookAt(camera_pos, camera_front, camera_up);
}

void Camera::setUp()
{
	camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

