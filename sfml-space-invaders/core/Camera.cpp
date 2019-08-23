#include "Camera.hpp"

#define MOVE_SPEED 2.0f

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
	time = dt;
}

void Camera::move(Direction direction)
{
	float speed = time * MOVE_SPEED;
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
}

glm::mat4 Camera::getLookUpMatrix() const
{
	return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

void Camera::setUp()
{
	camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

