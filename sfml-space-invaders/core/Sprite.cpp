#include "Sprite.hpp"

#include <iostream>

#define DEFAULT_SPRITE_COLOUR glm::vec3(1.0f, 0.0f, 1.0f)

Sprite::Sprite(b2World * world, b2BodyType type, SpriteType sprite_type, glm::vec2 size, float density) : 
	world(world), body(nullptr), fixture(nullptr), sprite_type(sprite_type), size(size)
{
	b2BodyDef body_def;
	body_def.type = type;
	body_def.position = b2Vec2(0.0f, 0.0f);

	body = world->CreateBody(&body_def);
	
	b2PolygonShape shape;
	shape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);

	b2FixtureDef fixture_def;
	fixture_def.density = density;
	fixture_def.shape = &shape;

	fixture = body->CreateFixture(&fixture_def);

	body->SetUserData((void *) this);

	// Set the sprite's default colour
	sprite_colour = DEFAULT_SPRITE_COLOUR;
}

Sprite::~Sprite()
{
	if ((fixture != nullptr) && (body != nullptr))
	{
		body->DestroyFixture(fixture);
	}

	if ((world != nullptr) && (body != nullptr))
	{
		world->DestroyBody(body);
	}
}

glm::vec2 Sprite::getSize() const noexcept
{
	return size;
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

void Sprite::setColour(glm::vec3 colour) noexcept
{
	sprite_colour = colour ;
}

glm::vec3 Sprite::getColour() const noexcept
{
	return sprite_colour;
}

SpriteType Sprite::getType() const
{
	return sprite_type;
}
