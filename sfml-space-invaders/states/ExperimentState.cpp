#include "ExperimentState.hpp"

#include "../core/managers/EventManager.hpp"

ExperimentState::ExperimentState(StateID id, SharedContext *context) : BaseState(id, context), cube(nullptr)
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
	EventManager *event_mgr = context->event_mgr;
	event_mgr->addBinding("name", EventType::KeyPressed, sf::Keyboard::S);
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
