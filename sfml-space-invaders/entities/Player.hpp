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

	virtual void beginContact(SpriteType type);
	virtual void endContact(SpriteType type);

	void left();
	void right();
	void stop();

	bool isDead() const;
private:
	void setUpCollision();

	bool is_dead;
	float velocity;
};

#endif // ENTITIES_PLAYER_HPP