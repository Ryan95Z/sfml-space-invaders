#ifndef ENTITIES_PLAYER_HPP
#define ENTITIES_PLAYER_HPP

#include "../core/Sprite.hpp"

class Player : public Sprite
{
public:
	Player(b2World *world);
	Player(b2World *world, glm::vec2 pos);
	virtual ~Player();

	virtual void update(float dt);

	void left();
	void right();
	void stop();
private:
	float velocity;
};

#endif // ENTITIES_PLAYER_HPP