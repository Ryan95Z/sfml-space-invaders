#include "Alien.hpp"
#include <iostream>

#define SCALE 30.0f
#define ALIEN_SIZE glm::vec2(35.0f, 35.0f)
#define ALIEN_BODY_DENSITY 1.0f
#define ALINE_MOVE_SPEED 75.0f
#define TICK_COUNT_LIMIT 110

Alien::Alien(b2World * world) : Sprite(world, b2_kinematicBody, SpriteType::Alien, ALIEN_SIZE, ALIEN_BODY_DENSITY),
	left(false), is_hidden(false), tick_count(0) {}

Alien::Alien(b2World * world, glm::vec2 pos) : Alien(world)
{
	this->setPosition(pos);
}

Alien::~Alien() {}

void Alien::update(float dt)
{
	glm::vec2 pos = this->getPosition();
	pos.x += (left) ? (-ALINE_MOVE_SPEED * dt) : (ALINE_MOVE_SPEED * dt);
	
	// Determine if the Alien should change direction
	// and move down the screen towards the player
	++tick_count;
	if (tick_count > TICK_COUNT_LIMIT)
	{
		pos.y += ALINE_MOVE_SPEED * dt;
		tick_count = 0;
		left = !left;
	}

	this->setPosition(pos);
}

void Alien::beginContact(SpriteType type)
{
	if (type == SpriteType::Projectile)
	{
		is_hidden = true;
	}
}

void Alien::endContact(SpriteType type) {}

bool Alien::isHidden() const
{
	return is_hidden;
}
