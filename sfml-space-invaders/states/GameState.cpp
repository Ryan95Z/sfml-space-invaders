#include "GameState.hpp"

#include <iostream>

GameState::GameState(StateID id) : BaseState(id), triangle(nullptr)
{
	triangle = new Triangle;
}

GameState::~GameState()
{
	destroy();
}

void GameState::start() {}

void GameState::stop() {}

void GameState::init() {}

void GameState::destroy()
{
	if (triangle != nullptr)
	{
		delete triangle;
		triangle = nullptr;
	}
}

void GameState::update(float dt)
{
	triangle->update(dt);
}

void GameState::draw()
{
	triangle->draw();
}
