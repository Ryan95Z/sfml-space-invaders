#ifndef ENTITIES_PROJECTILE_HPP
#define ENTITIES_PROJECTILE_HPP

#include "../core/Sprite.hpp"

class Projectile : public Sprite
{
public:
	Projectile(b2World *world);
	Projectile(b2World *world, glm::vec2 pos);
	virtual ~Projectile();

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);

	bool isHidden() const;
private:
	bool is_hidden;
};

#endif // ENTITIES_PROJECTILE_HPP