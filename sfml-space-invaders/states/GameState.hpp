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
#include "../listeners/ContactListender.hpp"

using AlienVector = std::vector<Alien *>;
using ProjectileVector = std::vector<Projectile *>;


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
	SpriteRender render;
	AlienVector aliens;
	AlienVector graveyard;
	ProjectileVector bullets;
	ProjectileVector spent_bullets;
	GameContactListener listener;
};

#endif // STATES_GAME_STATE_HPP