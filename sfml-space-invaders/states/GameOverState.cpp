#include "GameOverState.hpp"

GameOverState::GameOverState(StateID id, SharedContext * context) : BaseState(id, context)
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
	proj = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(800));
	font.loadFromFile(FONT_PATH);
	text.setFont(&font);

	text.setPosition(400.0f, 400.0f);
	text.setString("Hello World");
	text.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	text.setProjection(proj);
}

void GameOverState::destroy()
{
}

void GameOverState::update(float dt)
{
}

void GameOverState::draw()
{
	text.draw();
}

void GameOverState::cleanup()
{
}


