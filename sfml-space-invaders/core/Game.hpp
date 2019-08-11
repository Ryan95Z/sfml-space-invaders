#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "Window.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"

class Game
{
public:
	Game();
	~Game();

	bool isOpen() const;

	void render();
	void update();
	void handleEvents();
	void restartClock();
private:
	Triangle *triangle;
	Window window;

	sf::Time elapsed_time;
	sf::Clock clock;
};

#endif // CORE_GAME_HPP