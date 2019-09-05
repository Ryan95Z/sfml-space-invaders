#include "Projectile.hpp"

#define PROJECTILE_SIZE glm::vec2(25.0f, 25.0f)

Projectile::Projectile(b2World * world) : Sprite(world, b2_dynamicBody, SpriteType::Projectile, PROJECTILE_SIZE, 0.0f)
{
}

Projectile::Projectile(b2World * world, glm::vec2 pos) : Projectile(world)
{
	this->setPosition(pos);
}

Projectile::~Projectile()
{
}

void Projectile::update(float dt)
{
}

void Projectile::beginContact(SpriteType type)
{
}

void Projectile::endContact(SpriteType type)
{
}
