#include "Sprite.hpp"

#include <iostream>

#define DEFAULT_SPRITE_COLOUR glm::vec3(1.0f, 0.0f, 1.0f)

StaticSprite::StaticSprite(glm::vec2 size) : size(size), texture(nullptr)
{
	sprite_colour = DEFAULT_SPRITE_COLOUR;
}

StaticSprite::~StaticSprite()
{
}

glm::vec2 StaticSprite::getSize() const noexcept
{
	return size;
}

void StaticSprite::setPosition(glm::vec2 pos) noexcept
{
	this->pos = glm::vec3(pos, 0.0f);
}

glm::vec2 StaticSprite::getPosition() const noexcept
{
	return glm::vec2(pos.x, pos.y);
}

glm::vec3 StaticSprite::get3DPosition() const noexcept
{
	return pos;
}

void StaticSprite::setColour(glm::vec3 colour) noexcept
{
	sprite_colour = colour;
}

glm::vec3 StaticSprite::getColour() const noexcept
{
	return sprite_colour;
}

void StaticSprite::setTexture(Texture * texture)
{
	this->texture = texture;
}

Texture * StaticSprite::getTexture()
{
	return texture;
}

bool StaticSprite::hasTexture() const noexcept
{
	return (texture != nullptr);
}


Sprite::Sprite(b2World * world, b2BodyType type, SpriteType sprite_type, glm::vec2 size, float density) : StaticSprite(size),
	world(world), body(nullptr), fixture(nullptr), sprite_type(sprite_type)
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

void Sprite::setPosition(glm::vec2 pos) noexcept
{
	b2Vec2 b2_pos = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	body->SetTransform(b2_pos, body->GetAngle());
}

glm::vec2 Sprite::getPosition() const noexcept
{
	b2Vec2 b2_pos = body->GetPosition();
	return glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
}

glm::vec3 Sprite::get3DPosition() const noexcept
{
	b2Vec2 b2_pos = body->GetPosition();
	return glm::vec3(b2_pos.x * SCALE, b2_pos.y * SCALE, pos.z);
}

SpriteType Sprite::getType() const
{
	return sprite_type;
}