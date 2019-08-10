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
	triangle->update(0.0f);
}

void Game::handleEvents()
{
	window.handleEvents();
}
