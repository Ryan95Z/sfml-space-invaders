#include "GameState.hpp"

#include <iostream>

GameState::GameState(StateID id, SharedContext *context) : BaseState(id, context) {}

GameState::~GameState() {}

void GameState::start() {}

void GameState::stop() {}

void GameState::init() {}

void GameState::destroy() {}

void GameState::update(float dt)
{
	s.update(dt);
}

void GameState::draw()
{
	s.draw();
}
