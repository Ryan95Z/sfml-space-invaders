#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include "../core/BaseState.hpp"
#include "../core/Triangle.hpp"

class GameState : public BaseState
{
public:
	GameState(StateID id);
	virtual ~GameState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();
private:
	Triangle *triangle;
};

#endif // STATES_GAME_STATE_HPP