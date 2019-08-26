#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include "../core/BaseState.hpp"

#include "../core/SpriteRender.hpp"


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
private:
	SpriteRender render;
};

#endif // STATES_GAME_STATE_HPP