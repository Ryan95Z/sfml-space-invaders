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

}

void GameState::draw()
{
	render.drawSprite(glm::vec2(100.0f, 100.0f));
	render.drawSprite(glm::vec2(300.0f, 100.0f));
}
