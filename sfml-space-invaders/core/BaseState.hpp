#ifndef CORE_BASE_STATE_HPP
#define CORE_BASE_STATE_HPP

#include <string>
#include "managers/StateManager.hpp"

class BaseState
{
public:
	BaseState(StateID state_id) : id(state_id) {}
	BaseState() = delete;
	BaseState(BaseState &) = delete;

	virtual ~BaseState() {}

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void init() = 0;
	virtual void destroy() = 0;

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	StateID getId() const
	{
		return id;
	}

private:
	StateID id;
};

#endif // CORE_BASE_STATE_HPP