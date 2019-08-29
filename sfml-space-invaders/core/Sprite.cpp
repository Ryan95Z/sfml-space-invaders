#include "Sprite.hpp"

Sprite::Sprite(b2World * world) : world(world), body(nullptr)
{
}

Sprite::~Sprite()
{
	if ((world != nullptr) && (body != nullptr))
	{
		world->DestroyBody(body);
	}
}

void Sprite::setPosition(glm::vec2 pos) const noexcept
{
	b2Vec2 b2_pos = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	body->SetTransform(b2_pos, body->GetAngle());
}

glm::vec2 Sprite::getPosition() const noexcept
{
	b2Vec2 b2_pos = body->GetPosition();
	return glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
}
