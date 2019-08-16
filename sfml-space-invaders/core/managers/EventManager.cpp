#include "EventManager.hpp"

#include <iostream>

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	while (bindings.begin() != bindings.end())
	{
		std::cout << "Removing: " << bindings.begin()->first << std::endl;
		delete bindings.begin()->second;
		bindings.erase(bindings.begin());
	}
}

void EventManager::handleEvents(sf::Event evnt)
{
	EventType type = (EventType) evnt.type;
	if (type == EventType::KeyPressed)
	{
		std::cout << ((int) type) << std::endl;
	}
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

}
