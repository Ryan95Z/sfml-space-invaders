#ifndef CORE_MANAGERS_EVENT_MANAGER
#define CORE_MANAGERS_EVENT_MANAGER

#include <glm/glm.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

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
};

struct EventDetails
{
	glm::vec2 mouseCoords;
	sf::Keyboard::Key key;
};


struct EventBinding
{
	EventType type;
	sf::Keyboard::Key key;
};


using Bindings = std::unordered_map<std::string, EventBinding *>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventBinding *)>>;
using CallbackQueue = std::vector<std::function<void(EventBinding *)>>;

class EventManager
{
public:
	EventManager();
	EventManager(EventManager &) = delete;
	~EventManager();

	void handleEvents(sf::Event evnt);

	bool addBinding(std::string name, EventType type, sf::Keyboard::Key key);
	
	template <class T>
	bool addCallback(std::string, void(T::*func)(EventDetails *), T *instance)
	{

	}


protected:
	void processCallbacks();

private:
	Bindings bindings;
	Callbacks callbacks;
	Callbacks callback_queue;
};

#endif // CORE_MANAGERS_EVENT_MANAGER