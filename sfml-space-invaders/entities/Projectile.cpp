#include "Projectile.hpp"

#define PROJECTILE_SIZE glm::vec2(25.0f, 25.0f)

Projectile::Projectile(b2World * world) : Sprite(world, b2_dynamicBody, PROJECTILE_SIZE, 1.0f)
{
}

Projectile::~Projectile()
{
}

void Projectile::update(float dt)
{
}
