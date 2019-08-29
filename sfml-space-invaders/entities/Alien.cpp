#include "Alien.hpp"

#define SCALE 30.0f
#define ALIEN_SIZE glm::vec2(50.0f, 50.0f)
#define ALIEN_BODY_DENSITY 1.0f

Alien::Alien(b2World * world) : world(world), body(nullptr)
{
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(0.0f / SCALE, 0.0f / SCALE);

	body = world->CreateBody(&body_def);

	b2PolygonShape shape;
	shape.SetAsBox((ALIEN_SIZE.x / 2.0f) / SCALE, (ALIEN_SIZE.y / 2.0f) / SCALE);

	b2FixtureDef fixture_def;
	fixture_def.density = ALIEN_BODY_DENSITY;
	fixture_def.shape = &shape;

	body->CreateFixture(&fixture_def);
}

Alien::~Alien()
{
	if (body != nullptr)
	{
		world->DestroyBody(body);
		body = nullptr;
	}
}

glm::vec2 Alien::getSize() const noexcept
{
	return ALIEN_SIZE;
}

void Alien::setPosition(glm::vec2 pos) const noexcept
{
	b2Vec2 update_pos = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	body->SetTransform(update_pos, body->GetAngle());
}

glm::vec2 Alien::getPosition() const noexcept
{
	b2Vec2 b2_pos = body->GetPosition();
	return glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
}
