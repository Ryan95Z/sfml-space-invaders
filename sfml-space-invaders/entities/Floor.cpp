#include "Floor.hpp"

#define DEFAULT_SIZE glm::vec2(800.0f, 50.0f)

Floor::Floor(b2World * world) : Sprite(world, b2_staticBody, SpriteType::Projectile, DEFAULT_SIZE, 0.0f) {}

Floor::Floor(b2World * world, glm::vec2 size) : Sprite(world, b2_staticBody, SpriteType::Projectile, size, 0.0f) {}

Floor::~Floor() {}

void Floor::update(float dt)
{
}

void Floor::beginContact(SpriteType type)
{
}

void Floor::endContact(SpriteType type)
{
}
