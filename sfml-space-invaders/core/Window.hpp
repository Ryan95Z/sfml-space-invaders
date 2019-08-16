#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "managers/EventManager.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Window!"

class Window
{
public:
	Window();
	Window(const int width, const int height);
	Window(Window &) = delete;

	~Window();

	void handleEvents();
	void beginDrawing();
	void endDrawing();

	const sf::Window * getWindow() const;

	bool isOpen() const;
private:
	void setUp(const int width, const int height);

	bool isRunning;
	sf::Event evnt;
	sf::Window *window;
	EventManager event_mgr;

	static sf::ContextSettings getSettings();
};

#endif // CORE_WINDOW_HPP