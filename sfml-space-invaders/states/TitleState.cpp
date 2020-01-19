#include "TitleState.hpp"

#include "../core/Window.hpp"

#define TITLE "Space Invaders!"
#define INSTRUCTIONS "Press SPACE to start!"

TitleState::TitleState(StateID id, StateManager * state_mgr, SharedContext * context) : BaseState(id, state_mgr, context)
{
}

TitleState::~TitleState()
{
	destroy();
}

void TitleState::start()
{
}

void TitleState::stop()
{
}

void TitleState::init()
{
	Window *window = context->window;
	glm::ivec2 window_size = window->getSize();

	proj = glm::ortho(0.0f, static_cast<GLfloat>(window_size.x), 0.0f, static_cast<GLfloat>(window_size.y));
	arial.loadFromFile(FONT_PATH);

	// Set up the title
	title.setFont(&arial);
	title.setPosition(240.0f, 500.0f);
	title.setString(TITLE);
	title.setColour(glm::vec3(0.0f, 1.0f, 0.0f));
	title.setProjection(proj);

	// Set up the instructions
	instructions.setFont(&arial);
	instructions.setPosition(190.0f, 300.0f);
	instructions.setString(INSTRUCTIONS);
	instructions.setColour(glm::vec3(0.0f, 1.0f, 0.0f));
	instructions.setProjection(proj);

	EventManager *event_mgr = context->event_mgr;

}

void TitleState::destroy()
{
}

void TitleState::update(float dt)
{
}

void TitleState::draw()
{
	title.draw();
	instructions.draw();
}

void TitleState::cleanup()
{
}

void TitleState::reset()
{
}

void TitleState::startGame(EventDetails * details)
{
}
