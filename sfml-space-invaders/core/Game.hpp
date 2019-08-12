#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "Window.hpp"
#include "managers/StateManager.hpp"

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
	StateManager state_mgr;
	Window window;

	sf::Time elapsed_time;
	sf::Clock clock;
};

#endif // CORE_GAME_HPP