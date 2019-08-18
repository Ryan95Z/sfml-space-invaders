#include "EventManager.hpp"

EventManager::EventManager() {}

EventManager::~EventManager()
{
	while (bindings.begin() != bindings.end())
	{
		std::cout << "Removing: " << bindings.begin()->first << std::endl;
		delete bindings.begin()->second;
		bindings.erase(bindings.begin());
	}
	callbacks.clear();
	event_queue.clear();
}

void EventManager::handleEvents(sf::Event evnt)
{
	EventBinding *binding = nullptr;
	sf::Keyboard::Key key = evnt.key.code;
	EventType type = (EventType) evnt.type;
	Bindings::iterator b_itr = bindings.begin();

	// Go through all the bindings
	for (auto binding_pair : bindings)
	{
		EventDetails details;
		details.name = binding_pair.first;
		binding = binding_pair.second;

		// If a binding type matches the event type
		if (binding->type == type)
		{
			if ((type == EventType::KeyPressed || type == EventType::KeyReleased) && key == binding->key)
			{
				details.key = key;
				event_queue.emplace_back(details);
				continue;
			}

			if (type == EventType::MouseMoved)
			{
				glm::vec2 coords = glm::vec2(evnt.mouseMove.x, evnt.mouseMove.x);
				details.mouseCoords = coords;
				event_queue.emplace_back(details);
			}
		}
	}

	// Execute all the callbacks
	processCallbacks();
}

bool EventManager::addBinding(std::string name, EventType type, sf::Keyboard::Key key)
{
	EventBinding *binding = nullptr;
	Bindings::iterator b_itr = bindings.find(name);
	if (b_itr != bindings.end())
	{
		std::cout << name << " is already in use as a binding\n";
		return false;
	}
	binding = new EventBinding;
	binding->type = type;
	binding->key = key;
	bindings.emplace(name, binding);
	std::cout << "Size of bindings: " << bindings.size() << std::endl;
	return true;
}

void EventManager::processCallbacks()
{
	Callbacks::iterator c_itr = callbacks.end();
	for (EventDetails details : event_queue)
	{
		c_itr = callbacks.find(details.name);

		// Check that the callback exists
		if (c_itr == callbacks.end())
		{
			std::cout << "Missing callback: " << details.name << std::endl;
			continue;
		}

		// Execute the callback
		c_itr->second(&details);
	}
	event_queue.clear();
}
