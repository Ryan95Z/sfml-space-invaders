#ifndef ENTITIES_FLOOR_HPP
#define ENTITIES_FLOOR_HPP

#include "../core/Sprite.hpp"

class Floor : public Sprite
{
public:
	Floor(b2World *world);
	Floor(b2World *world, glm::vec2 size);
	virtual ~Floor();

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);
};

#endif // ENTITIES_FLOOR_HPP