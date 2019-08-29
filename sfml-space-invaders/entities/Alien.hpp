#ifndef ENTITES_ALIEN_HPP
#define ENTITES_ALIEN_HPP

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

class Alien
{
public:
	Alien() = delete;
	Alien(Alien &) = delete;
	Alien(b2World *world);
	~Alien();

	glm::vec2 getSize() const noexcept;

	void setPosition(glm::vec2 pos) const noexcept;
	glm::vec2 getPosition() const noexcept;
protected:
	b2World *world;
	b2Body *body;
};

#endif // ENTITES_ALIEN_HPP