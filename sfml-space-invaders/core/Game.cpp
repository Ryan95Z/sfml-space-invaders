#include <iostream>

#include "Game.hpp"


Game::Game()
{
	triangle = new Triangle;
}

Game::~Game()
{
}

bool Game::isOpen() const
{
	return window.isOpen();
}

void Game::render()
{
	window.beginDrawing();

	triangle->draw();

	window.endDrawing();
}

void Game::update()
{
	float timestep = 1 / 60.0f;
	float elapased = elapsed_time.asSeconds();
	if (elapased > timestep)
	{
		triangle->update(elapased);
		elapsed_time -= sf::seconds(timestep);
	}
}

void Game::handleEvents()
{
	window.handleEvents();
}

void Game::restartClock()
{
	elapsed_time += clock.restart();
}
