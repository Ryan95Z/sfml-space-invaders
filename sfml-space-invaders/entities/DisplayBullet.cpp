#include "DisplayBullet.hpp"

#define BULLET_SIZE glm::vec2(35.0f, 35.0f)

DisplayBullet::DisplayBullet(b2World * world) : StaticSprite(BULLET_SIZE)
{
}

DisplayBullet::~DisplayBullet()
{
}

void DisplayBullet::update(float dt)
{
}

void DisplayBullet::beginContact(SpriteType type)
{
}

void DisplayBullet::endContact(SpriteType type)
{
}
