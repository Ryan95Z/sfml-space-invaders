#include "ExperimentState.hpp"


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
	event_mgr->addBinding("left", EventType::KeyPressed, sf::Keyboard::A);
	event_mgr->addCallback("left", &Cube::left, cube);

	event_mgr->addBinding("right", EventType::KeyPressed, sf::Keyboard::D);
	event_mgr->addCallback("right", &Cube::right, cube);

	event_mgr->addBinding("up", EventType::KeyPressed, sf::Keyboard::W);
	event_mgr->addCallback("up", &Cube::up, cube);

	event_mgr->addBinding("down", EventType::KeyPressed, sf::Keyboard::S);
	event_mgr->addCallback("down", &Cube::down, cube);


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

void ExperimentState::cleanup() {}

void ExperimentState::testCallback(EventDetails * details)
{
	std::cout << "Hello World\n";
}

