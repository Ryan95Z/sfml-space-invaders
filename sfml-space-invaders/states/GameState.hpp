#ifndef STATES_GAME_STATE_HPP
#define STATES_GAME_STATE_HPP

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#include <vector>

#define NUM_ALIENS 20

using PositionVector = std::vector<glm::vec2>;
using PositionRemovalVector = std::vector<PositionVector::iterator>;

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
	bool move_left;
	unsigned int game_count;
	glm::vec2 velocity;
	glm::vec2 pos;
	glm::vec2 alien_pos[NUM_ALIENS];
	SpriteRender render;
	PositionVector pvec;
	PositionRemovalVector rvec;
};

#endif // STATES_GAME_STATE_HPP