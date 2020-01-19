#include "StateManager.hpp"

#include "../BaseState.hpp"
#include "../../states/GameState.hpp"
#include "../../states/ExperimentState.hpp"
#include "../../states/GameOverState.hpp"
#include "../../states/TitleState.hpp"
#include "../../states/StateInfo.hpp"

StateManager::StateManager(SharedContext *context) : context(context), has_pop_request(false)
{
	registerState<GameState>(GAME_STATE_ID);
	registerState<ExperimentState>(EXPERIMENT_STATE_ID);
	registerState<GameOverState>(GAME_OVER_STATE_ID);
	registerState<TitleState>(TITLE_STATE_ID);
}

StateManager::~StateManager()
{
	BaseState *state = nullptr;

	// Go through the stack until all states are deleted
	while (!active_states.empty())
	{
		state = active_states.top();
		active_states.pop();
	
		// Stop the states
		state->stop();
		state->destroy();

		delete state;
		state = nullptr;
	}

	factory.clear();
}

void StateManager::update(float dt)
{
	active_states.top()->update(dt);
}

void StateManager::render()
{
	active_states.top()->draw();
}

void StateManager::cleanup()
{
	active_states.top()->cleanup();
}

StateID StateManager::top() const
{
	return active_states.top()->getId();
}

void StateManager::checkNextState()
{
	if (next_states.size() < 1) { return;  }
	pushState(*next_states.begin());
	next_states.erase(next_states.begin());
}

void StateManager::checkStateRemoval()
{
	if (!has_pop_request) { return; }
	popState();
	has_pop_request = false;
}

void StateManager::registerNextState(StateID state_id)
{
	next_states.push_back(state_id);
}

void StateManager::reigsterStateRemoval()
{
	has_pop_request = true;
}

bool StateManager::pushState(StateID state_id)
{
	BaseState *state = factory[state_id]();
	context->event_mgr->setCurrentState(state->getId());
	state->init();
	state->start();
	active_states.push(state);
	return true;
}

StateID StateManager::popState()
{
	BaseState *state = active_states.top();
	active_states.pop();

	// Check that stack will be empty
	// If this is happens then stop the state being popped
	if (active_states.empty()) {
		std::cout << "Cannot pop last state!" << std::endl;
		active_states.push(state);
		return -1;
	}

	StateID id = state->getId();
	state->stop();
	state->destroy();
	delete state;
	state = nullptr;
	updateEventManager();
	return id;
}

void StateManager::updateEventManager()
{
	EventManager *event_mgr = context->event_mgr;
	BaseState *state = active_states.top();
	event_mgr->setCurrentState(state->getId());
}
