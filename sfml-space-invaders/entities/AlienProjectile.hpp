#ifndef ENTITIES_ALIEN_PROJECTILE_HPP
#define ENTITIES_ALIEN_PROJECTILE_HPP

#include "Projectile.hpp"

class AlienProjectile : public Projectile
{
public:
	AlienProjectile(b2World *world);
	AlienProjectile(b2World *world, glm::vec2 pos);

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
};

#endif // !ENTITIES_ALIEN_PROJECTILE_HPP