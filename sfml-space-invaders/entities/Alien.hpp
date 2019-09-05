#ifndef ENTITES_ALIEN_HPP
#define ENTITES_ALIEN_HPP

#include "../core/Sprite.hpp"

class Alien : public Sprite
{
public:
	Alien() = delete;
	Alien(Alien &) = delete;
	Alien(b2World *world);
	Alien(b2World *world, glm::vec2 pos);
	virtual ~Alien();

	virtual void update(float dt);

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);
private:
	int tick_count;
	bool left;
};

#endif // ENTITES_ALIEN_HPP