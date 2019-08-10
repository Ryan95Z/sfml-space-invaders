#include <iostream>

#include "core/Game.hpp"


int main()
{
	Game *game = nullptr;

	try {
		game = new Game;
	}
	catch (std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}
	
	while (game->isOpen())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	delete game;
	game = nullptr;
	return 0;
}