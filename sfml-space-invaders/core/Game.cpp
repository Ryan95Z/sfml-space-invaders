#include <iostream>

#include "Game.hpp"


Game::Game() : state_mgr(&context)
{
	context.event_mgr = window.getEventManager();

	state_mgr.pushState(2);
	
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
	state_mgr.render();
	window.endDrawing();
}

void Game::update()
{
	float timestep = 1 / 60.0f;
	float elapased = elapsed_time.asSeconds();
	if (elapased > timestep)
	{
		state_mgr.update(timestep);
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
