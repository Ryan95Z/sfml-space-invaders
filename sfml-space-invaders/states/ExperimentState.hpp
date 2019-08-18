#ifndef STATES_EXPERIMENT_STATE_HPP
#define STATES_EXPERIMENT_STATE_HPP

#include "../core/BaseState.hpp"
#include "../entities/Cube.hpp"

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
private:
	Cube *cube;
};

#endif // STATES_EXPERIMENT_STATE_HPP