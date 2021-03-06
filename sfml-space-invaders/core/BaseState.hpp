#ifndef CORE_BASE_STATE_HPP
#define CORE_BASE_STATE_HPP

#include <string>
#include "managers/StateManager.hpp"

class BaseState
{
public:
	BaseState() = delete;
	BaseState(BaseState &) = delete;
	BaseState(StateID state_id, StateManager *state_mgr, SharedContext *context) : id(state_id), context(context),
		state_mgr(state_mgr) {}

	virtual ~BaseState() {}

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void init() = 0;
	virtual void destroy() = 0;

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void cleanup() = 0;
	virtual void reset() = 0;

	StateID getId() const
	{
		return id;
	}
protected:
	StateManager *state_mgr;
	SharedContext *context;

private:
	StateID id;
};

#endif // CORE_BASE_STATE_HPP