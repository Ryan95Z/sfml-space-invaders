#include "Window.hpp"

#include <iostream>

Window::Window() : isRunning(true), window(nullptr)
{
	setUp(WINDOW_WIDTH, WINDOW_HEIGHT);
}

Window::Window(const int width, const int height) : isRunning(true), window(nullptr)
{
	setUp(width, height);
}

Window::~Window()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}
}

void Window::handleEvents()
{
	while (window->pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
		{
			isRunning = false;
		}
	}
}

void Window::beginDrawing()
{
	window->setActive(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_BUFFER);
}

void Window::endDrawing()
{
	window->display();
}

const sf::Window * Window::getWindow() const
{
	return window;
}

bool Window::isOpen() const
{
	return isRunning;
}

void Window::setUp(const int width, const int height)
{
	window = new sf::Window(sf::VideoMode(width, height), WINDOW_TITLE, sf::Style::Default, Window::getSettings());
	glViewport(0, 0, width, height);
	window->setVerticalSyncEnabled(true);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initalise\n";
		exit(EXIT_FAILURE);
	}

	event_mgr.addBinding("name", EventType::KeyPressed, sf::Keyboard::S);
}

sf::ContextSettings Window::getSettings()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	return settings;
}
