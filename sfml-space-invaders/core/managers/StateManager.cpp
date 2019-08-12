#include "StateManager.hpp"

#include "../BaseState.hpp"
#include "../../states/GameState.hpp"
#include "../../states/StateInfo.hpp"

StateManager::StateManager()
{
	registerState<GameState>(GAME_STATE_ID);
}

StateManager::~StateManager()
{
	BaseState *state = nullptr;

	// Remove any active states
	while (active_states.begin() != active_states.end())
	{
		state = *active_states.begin();

		// Clean up the memory used by the state
		state->stop();
		state->destroy();
		
		// Deallocate the state from memory
		delete state;
		state = nullptr;
		active_states.erase(active_states.begin());
	}

	active_states.clear();
	factory.clear();
}

void StateManager::update(float dt)
{
	(*active_states.begin())->update(dt);
}

void StateManager::render()
{
	(*active_states.begin())->draw();
}

bool StateManager::pushState(StateID state_id)
{
	BaseState *state = factory[state_id]();
	state->init();
	state->start();
	active_states.push_back(state);
	return true;
}

StateID StateManager::popState()
{
	BaseState *state = *active_states.begin();
	StateID id = state->getId();
	state->stop();
	state->destroy();
	delete state;
	state = nullptr;
	active_states.erase(active_states.begin());
	return id;
}

StateID StateManager::top() const
{
	return (*active_states.begin())->getId();
}
