#include "ExperimentState.hpp"

ExperimentState::ExperimentState(StateID id) : BaseState(id), cube(nullptr)
{
	cube = new Cube;
}

ExperimentState::~ExperimentState()
{
	destroy();
}

void ExperimentState::start()
{
}

void ExperimentState::stop()
{
}

void ExperimentState::init()
{
}

void ExperimentState::destroy()
{
	delete cube;
	cube = nullptr;
}

void ExperimentState::update(float dt)
{
	cube->update(dt);
}

void ExperimentState::draw()
{
	cube->draw();
}
