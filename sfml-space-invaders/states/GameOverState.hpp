#ifndef STATES_GAME_OVER_STATE_HPP
#define STATES_GAME_OVER_STATE_HPP

#include "../core/BaseState.hpp"

class GameOverState : public BaseState
{
public:
	GameOverState() = delete;
	GameOverState(GameOverState &) = delete;
	GameOverState(StateID id, SharedContext *context);
	virtual ~GameOverState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
};

#endif // STATES_GAME_OVER_STATE_HPP