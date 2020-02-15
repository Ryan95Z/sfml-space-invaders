#ifndef ENTITES_DISPLAY_BULLET_HPP
#define ENTITES_DISPLAY_BULLET_HPP

#include "../core/Sprite.hpp"

class DisplayBullet : public StaticSprite
{
public:
	DisplayBullet(b2World *world);
	virtual ~DisplayBullet();

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);
};

#endif // !ENTITES_DISPLAY_BULLET_HPP