#include "GameOverState.hpp"

#include "../core/Window.hpp"

#define TITLE "Game Over"
#define MESSAGE "Try Again!"

GameOverState::GameOverState(StateID id, StateManager *state_mgr, SharedContext * context) : BaseState(id, state_mgr, context)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::start()
{
}

void GameOverState::stop()
{
}

void GameOverState::init()
{
	Window *window = context->window;
	glm::ivec2 window_size = window->getSize();
	proj = glm::ortho(0.0f, static_cast<GLfloat>(window_size.x), 0.0f, static_cast<GLfloat>(window_size.y));
	font.loadFromFile(FONT_PATH);

	// Set up the title
	title.setFont(&font);
	title.setPosition(300.0f, 430.0f);
	title.setString(TITLE);
	title.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	title.setProjection(proj);

	// Set up the message
	msg.setFont(&font);
	msg.setPosition(340.0f, 370.0f);
	msg.setString(MESSAGE);
	msg.setColour(glm::vec3(1.0f, 1.0f, 0.0f));
	msg.setProjection(proj);
	msg.setScale(0.8f);
}

void GameOverState::destroy()
{
}

void GameOverState::update(float dt)
{
}

void GameOverState::draw()
{
	title.draw();
	msg.draw();
}

void GameOverState::cleanup()
{
}
