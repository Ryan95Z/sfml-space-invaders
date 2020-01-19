#ifndef STATES_TITLE_STATE_HPP
#define STATES_TITLE_STATE_HPP

#include "../core/BaseState.hpp"

class TitleState : public BaseState
{
public:
	TitleState(StateID id, StateManager *state_mgr, SharedContext *context);
	virtual ~TitleState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
	virtual void reset();

};

#endif // !STATES_TITLE_STATE_HPP