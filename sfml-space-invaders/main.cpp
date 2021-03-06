#include "core/Game.hpp"

int main()
{
	Game game;	
	while (game.isOpen())
	{
		game.handleEvents();
		game.update();
		game.render();
		game.restartClock();
	}
	return 0;
}