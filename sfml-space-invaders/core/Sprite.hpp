#ifndef CORE_SPRITE_HPP
#define CORE_SPRITE_HPP

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#define SCALE 30.0f

class Sprite
{
public:
	Sprite(b2World *world, b2BodyType type, glm::vec2 size, float density);
	virtual ~Sprite();

	virtual glm::vec2 getSize() const noexcept;

	virtual void setPosition(glm::vec2 pos) const noexcept;
	virtual glm::vec2 getPosition() const noexcept;

protected:
	b2World *world;
	b2Body *body;
	glm::vec2 size;
};

#endif // CORE_SPRITE_HPP