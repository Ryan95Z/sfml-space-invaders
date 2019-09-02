#ifndef ENTITES_ALIEN_HPP
#define ENTITES_ALIEN_HPP

#include "../core/Sprite.hpp"

class Alien : public Sprite
{
public:
	Alien() = delete;
	Alien(Alien &) = delete;
	Alien(b2World *world);
	virtual ~Alien();

protected:
	b2World *world;
	b2Body *body;
};

#endif // ENTITES_ALIEN_HPP