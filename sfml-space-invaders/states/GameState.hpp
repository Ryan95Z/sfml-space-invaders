#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include <Box2D/Box2D.h>
#include <vector>

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#include "../entities/Alien.hpp"
#include "../entities/Player.hpp"
#include "../entities/Projectile.hpp"


#define NUM_ALIENS 20

using PositionVector = std::vector<glm::vec2>;
using PositionRemovalVector = std::vector<PositionVector::iterator>;


using AlienVector = std::vector<Alien *>;
using ProjectileVector = std::vector<Projectile *>;
using ProjectileRemovalVector = std::vector<ProjectileVector::iterator>;


class GameState : public BaseState
{
public:
	GameState() = delete;
	GameState(GameState &) = delete;
	GameState(StateID id, SharedContext *context);
	virtual ~GameState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
protected:
	void left(EventDetails *details);
	void right(EventDetails *details);
	void stop(EventDetails *details);
	void fire(EventDetails *details);

private:
	b2World *world;
	Player *player;
	AlienVector aliens;
	SpriteRender render;
	ProjectileVector bullets;
	ProjectileRemovalVector removal;

	/*bool move_left;
	unsigned int game_count;
	glm::vec2 velocity;
	glm::vec2 pos;
	glm::vec2 alien_pos[NUM_ALIENS];
	SpriteRender render;
	PositionVector pvec;
	PositionRemovalVector rvec;*/
};

#endif // STATES_GAME_STATE_HPP