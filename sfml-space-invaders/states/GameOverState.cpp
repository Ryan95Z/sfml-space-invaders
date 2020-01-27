#include "GameOverState.hpp"

#include "../core/Window.hpp"

#define TITLE "Game Over"
#define MESSAGE "Try Again!"
#define WON_MESSAGE "You Won!"

GameOverState::GameOverState(StateID id, StateManager *state_mgr, SharedContext * context) : BaseState(id, state_mgr, context)
{
}

GameOverState::~GameOverState()
{
	destroy();
}

void GameOverState::start()
{
}

void GameOverState::stop()
{
}

void GameOverState::init()
{
	bool had_player_one = context->data.has_player_won;
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
	msg.setProjection(proj);
	msg.setScale(0.8f);

	if (had_player_one)
	{
		msg.setString(WON_MESSAGE);
		msg.setColour(glm::vec3(1.0f, 1.0f, 0.0f));
	}
	else
	{
		msg.setString(MESSAGE);
		msg.setColour(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	

	EventManager *event_mgr = context->event_mgr;
	event_mgr->addCallback(SPACE_BAR_EVENT, &GameOverState::backToMenu, this);
}

void GameOverState::destroy()
{
	EventManager *event_mgr = context->event_mgr;
	event_mgr->removeCallback(SPACE_BAR_EVENT);
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

void GameOverState::reset()
{

}

void GameOverState::backToMenu(EventDetails * details)
{
	state_mgr->reigsterStateRemoval();
	state_mgr->reigsterStateRemoval();
}
