#ifndef CORE_MANAGERS_STATE_MANAGER_HPP
#define CORE_MANAGERS_STATE_MANAGER_HPP


#include <unordered_map>
#include <vector>
#include <functional>

class BaseState;

using StateID = unsigned int;
using StateVector = std::vector<BaseState *>;
using StateFactory = std::unordered_map <StateID, std::function<BaseState * (void)>>;

class StateManager
{
public:
	StateManager();
	~StateManager();

	void update(float dt);
	void render();

	bool pushState(StateID state_id);
	StateID popState();
	StateID top() const;

	template <class T>
	bool registerState(StateID state_id)
	{
		factory[state_id] = []() ->
		{
			return new T;
		}
		return true;
	}
private:
	StateFactory factory;
	StateVector active_states;
};

#endif // CORE_MANAGERS_STATE_MANAGER_HPP