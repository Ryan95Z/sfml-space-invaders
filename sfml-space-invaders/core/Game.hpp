#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "Window.hpp"
#include "SharedContext.hpp"
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
	float delta_time;
	float last_frame;
	float current_frame;

	Window window;
	SharedContext context;
	StateManager state_mgr;

	sf::Time elapsed_time;
	sf::Clock clock;
};

#endif // CORE_GAME_HPP