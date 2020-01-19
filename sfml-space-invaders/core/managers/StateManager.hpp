#ifndef CORE_MANAGERS_STATE_MANAGER_HPP
#define CORE_MANAGERS_STATE_MANAGER_HPP

#include <unordered_map>
#include <vector>
#include <functional>

#include "../SharedContext.hpp"

class BaseState;

using StateID = unsigned int;
using StateVector = std::vector<BaseState *>;
using StateFactory = std::unordered_map <StateID, std::function<BaseState * (void)>>;

class StateManager
{
public:
	StateManager() = delete;
	StateManager(StateManager &) = delete;
	StateManager(SharedContext *context);
	~StateManager();

	void update(float dt);
	void render();
	void cleanup();

	bool pushState(StateID state_id);
	StateID popState();
	StateID top() const;

	template <class T>
	bool registerState(StateID state_id)
	{
		// Assign a lambda function to construct the State based on the ID
		factory[state_id] = [state_id, this]() -> BaseState * {
			return new T(state_id, this->context);
		};
		return true;
	}

	void checkNextStates();
	void registerNextState(StateID state_id);
private:
	StateID current_state;
	SharedContext *context;
	std::vector<StateID> next_states;
	StateFactory factory;
	StateVector active_states;
};

#endif // CORE_MANAGERS_STATE_MANAGER_HPP