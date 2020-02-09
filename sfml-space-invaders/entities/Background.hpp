#ifndef ENTITIES_BACKGROUND_HPP
#define ENTITIES_BACKGROUND_HPP

#include "../core/Sprite.hpp"

class Background : public StaticSprite
{
public:
	Background(b2World *world);
	virtual ~Background();

	virtual glm::vec3 get3DPosition() const noexcept;

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);
private:

};

#endif // ENTITIES_BACKGROUND_HPP