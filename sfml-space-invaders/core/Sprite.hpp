#ifndef CORE_SPRITE_HPP
#define CORE_SPRITE_HPP

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#include "Texture.hpp"

#define SCALE 30.0f

enum class SpriteType
{
	Alien = 1,
	Player,
	Projectile,
	AlienProjectile,
	Background
};

enum SpriteCategory
{
	ALIEN = 0x001,
	PLAYER = 0x002,
	PROJECTILE = 0x003,
	ALIEN_PROJECTILE = 0x004
};

class StaticSprite
{
public:
	StaticSprite(glm::vec2 size);
	virtual ~StaticSprite();

	virtual void update(float dt) = 0;

	virtual glm::vec2 getSize() const noexcept;

	virtual void setPosition(glm::vec2 pos) noexcept;
	virtual glm::vec2 getPosition() const noexcept;
	virtual glm::vec3 get3DPosition() const noexcept;

	virtual void setColour(glm::vec3 colour) noexcept;
	virtual glm::vec3 getColour() const noexcept;

	virtual void setTexture(Texture * texture);
	virtual Texture * getTexture();
	bool hasTexture() const noexcept;

protected:
	glm::vec3 pos;
	glm::vec2 size;
	glm::vec3 sprite_colour;

private:
	Texture *texture;
};

class Sprite : public StaticSprite
{
public:
	Sprite(b2World *world, b2BodyType body_type, SpriteType sprite_type, glm::vec2 size, float density);
	virtual ~Sprite();

	virtual void setPosition(glm::vec2 pos) noexcept;
	virtual glm::vec2 getPosition() const noexcept;
	virtual glm::vec3 get3DPosition() const noexcept;

	virtual void beginContact(SpriteType type) = 0;
	virtual void endContact(SpriteType type) = 0;

	SpriteType getType() const;
protected:
	b2World *world;
	b2Body *body;
	b2Fixture *fixture;

private:
	SpriteType sprite_type;
};

#endif // CORE_SPRITE_HPP