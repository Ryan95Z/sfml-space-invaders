#ifndef CORE_MANAGERS_EVENT_MANAGER
#define CORE_MANAGERS_EVENT_MANAGER

#include <glm/glm.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <functional>
#include <unordered_map>

// Define the Events that will be supported based on SFML's existing events
enum class EventType
{
	Closed = sf::Event::Closed,
	Resized = sf::Event::Resized,
	LostFocus = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	TextEntered = sf::Event::TextEntered,
	KeyPressed = sf::Event::KeyPressed,
	KeyReleased = sf::Event::KeyReleased,
	MouseWheelScrolled = sf::Event::MouseWheelScrolled,
	MouseButtonPressed = sf::Event::MouseButtonReleased,
	MouseButtonReleased = sf::Event::MouseButtonReleased,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	MouseMoved = sf::Event::MouseMoved
};

struct EventDetails
{
	std::string name;
	glm::vec2 mouseCoords;
	sf::Keyboard::Key key;
};


struct EventBinding
{
	EventType type;
	sf::Keyboard::Key key;
};


using Bindings = std::unordered_map<std::string, EventBinding *>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails *)>>;
using EventQueue = std::vector<EventDetails>;

class EventManager
{
public:
	EventManager();
	EventManager(EventManager &) = delete;
	~EventManager();

	void handleEvents(sf::Event evnt);
	bool addBinding(std::string name, EventType type, sf::Keyboard::Key key);
	
	template <class T>
	bool addCallback(std::string name, void(T::*func)(EventDetails *), T *instance)
	{
		Bindings::iterator b_itr = bindings.find(name);
		Callbacks::iterator c_itr = callbacks.find(name);

		if (b_itr == bindings.end())
		{
			std::cout << "Not binding assigned to " << name << std::endl;
			return false;
		}

		if (c_itr != callbacks.end())
		{
			std::cout << name << " has already been registered as a callback\n";
			return false;
		}
		auto callback = std::bind(func, instance, std::placeholders::_1);
		callbacks.emplace(name, callback);
		return true;
	}
private:
	void processCallbacks();

	Bindings bindings;
	Callbacks callbacks;
	EventQueue event_queue;
};

#endif // CORE_MANAGERS_EVENT_MANAGER