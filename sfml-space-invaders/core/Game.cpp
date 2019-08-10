#include <GL/glew.h>
#include <iostream>
#include "Game.hpp"

Game::Game()
{
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("GLEW failed to initialise!");
	}
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
