#include "Background.hpp"

#include "../core/Window.hpp"

#define BACKGROUND_SIZE glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT)

Background::Background(b2World * world) : StaticSprite(BACKGROUND_SIZE)
{
}

Background::~Background()
{
}

glm::vec3 Background::get3DPosition() const noexcept
{
	return glm::vec3(pos.x, pos.y, 0.0f);
}

void Background::update(float dt)
{
}

void Background::beginContact(SpriteType type)
{
}

void Background::endContact(SpriteType type)
{
}
