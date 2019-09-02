#include "Alien.hpp"

#define SCALE 30.0f
#define ALIEN_SIZE glm::vec2(50.0f, 50.0f)
#define ALIEN_BODY_DENSITY 1.0f
#define ALINE_MOVE_SPEED 100.0f

Alien::Alien(b2World * world) : Sprite(world, b2_kinematicBody, ALIEN_SIZE, ALIEN_BODY_DENSITY), 
	left(false), tick_count(0) {}

Alien::~Alien() {}

void Alien::update(float dt)
{
	glm::vec2 pos = this->getPosition();
	pos.x += (left) ? (-ALINE_MOVE_SPEED * dt) : (ALINE_MOVE_SPEED * dt);
	this->setPosition(pos);

	++tick_count;
	if (tick_count > 199)
	{
		tick_count = 0;
		left = !left;
	}
}
