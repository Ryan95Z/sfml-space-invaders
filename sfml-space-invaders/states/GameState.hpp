#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include <Box2D/Box2D.h>
#include <vector>
#include <random>

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#include "../core/gui/Font.hpp"
#include "../core/gui/Text.hpp"

#include "../entities/Alien.hpp"
#include "../entities/Player.hpp"
#include "../entities/Projectile.hpp"
#include "../listeners/ContactListener.hpp"

using AlienVector = std::vector<Alien *>;
using ProjectileVector = std::vector<Projectile *>;


class GameState : public BaseState
{
public:
	GameState() = delete;
	GameState(GameState &) = delete;
	GameState(StateID id, StateManager *state_mgr, SharedContext *context);
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
	void enemyFire(Alien *alien);
	void setScreenText();

	bool is_game_over;
	unsigned int score;
	glm::ivec2 window_size;
	b2World *world;
	Player *player;
	Font font;
	Text score_txt;
	Text lives_txt;
	SpriteRender render;
	AlienVector aliens;
	AlienVector graveyard;
	ProjectileVector bullets;
	ProjectileVector alien_bullets;
	ProjectileVector spent_bullets;
	GameContactListener listener;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> *dist;
};

#endif // STATES_GAME_STATE_HPP