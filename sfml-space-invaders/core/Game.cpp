#include "Game.hpp"

Game::Game()
{
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

	// render stuff here

	window.endDrawing();
}

void Game::update()
{
}

void Game::handleEvents()
{
	window.handleEvents();
}
