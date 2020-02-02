#include "Projectile.hpp"
#include <iostream>

#define PROJECTILE_SIZE glm::vec2(15.0f, 15.0f)
#define PROJECTILE_VELOCITY b2Vec2(0.0f, -5.0f)

#define PROJECTILE_COLOUR glm::vec3(1.0f, 0.0f, 0.0f)

Projectile::Projectile(b2World * world) : Sprite(world, b2_dynamicBody, SpriteType::Projectile, PROJECTILE_SIZE, 0.0f),
	is_hidden(false)
{
	setColour(PROJECTILE_COLOUR);
}

Projectile::Projectile(b2World * world, glm::vec2 pos) : Projectile(world)
{
	this->setPosition(pos);
}

Projectile::Projectile(b2World * world, glm::vec2 pos, SpriteType type) : Sprite(world, b2_dynamicBody, type, PROJECTILE_SIZE, 0.0f)
{
	this->setPosition(pos);
}

Projectile::~Projectile() {}

void Projectile::update(float dt)
{
	body->SetLinearVelocity(PROJECTILE_VELOCITY);
}

void Projectile::beginContact(SpriteType type)
{
	if (type == SpriteType::Alien)
	{
		is_hidden = true;
	}
}

void Projectile::endContact(SpriteType type)
{
}

bool Projectile::isHidden() const
{
	return is_hidden;
}
