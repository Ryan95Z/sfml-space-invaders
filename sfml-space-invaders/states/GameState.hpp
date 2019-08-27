#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#define NUM_ALIENS 20

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

protected:
	void left(EventDetails *details);
	void right(EventDetails *details);
	void stop(EventDetails *details);
	void fire(EventDetails *details);

private:
	glm::vec2 velocity;
	glm::vec2 pos;
	glm::vec2 alien_pos[NUM_ALIENS];
	SpriteRender render;
};

#endif // STATES_GAME_STATE_HPP