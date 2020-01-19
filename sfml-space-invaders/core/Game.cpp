#include <iostream>

#include "Game.hpp"


Game::Game() : state_mgr(&context), delta_time(0.0f), last_frame(0.0f), current_frame(0.0f)
{
	// Set up the shared context
	context.window = &window;
	context.event_mgr = window.getEventManager();

	// Push the initial game state
	state_mgr.registerNextState(1);	
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
	current_frame = elapsed_time.asSeconds();
	state_mgr.update(delta_time);
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
}

void Game::handleEvents()
{
	// Check that there are new states to add
	state_mgr.checkNextState();

	// Handle incoming events
	window.handleEvents();
}

void Game::restartClock()
{
	state_mgr.cleanup();
	elapsed_time += clock.restart();

	// Check that there are states to remove
	state_mgr.checkStateRemoval();
}
