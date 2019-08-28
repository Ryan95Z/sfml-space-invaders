#ifndef STATES_EXPERIMENT_STATE_HPP
#define STATES_EXPERIMENT_STATE_HPP

#include "../core/BaseState.hpp"
#include "../entities/Cube.hpp"

#include "../core/managers/EventManager.hpp"

class ExperimentState : public BaseState
{
public:
	ExperimentState(StateID id, SharedContext *context);
	virtual ~ExperimentState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
private:
	void testCallback(EventDetails *details);

	Cube *cube;
};

#endif // STATES_EXPERIMENT_STATE_HPP