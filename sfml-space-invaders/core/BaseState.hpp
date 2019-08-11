#ifndef CORE_BASE_STATE_HPP
#define CORE_BASE_STATE_HPP

#include <string>

class BaseState
{
public:
	BaseState() {}
	BaseState(BaseState &) = delete;
	virtual ~BaseState() {}

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void init() = 0;
	virtual void destroy() = 0;

	virtual void update(float dt) = 0;
	virtual void draw() = 0;
};

#endif // CORE_BASE_STATE_HPP