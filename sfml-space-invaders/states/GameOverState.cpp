#include "GameOverState.hpp"

#include "../core/Window.hpp"

#include "StateInfo.hpp"

#define TITLE "Game Over"
#define SCORE "Score: "

GameOverState::GameOverState(StateID id, StateManager *state_mgr, SharedContext * context) : BaseState(id, state_mgr, context),
	background(nullptr)
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
	Window *window = context->window;
	TextureManager *texture_mgr = context->texture_mgr;
	glm::ivec2 window_size = window->getSize();
	std::string score_str = SCORE + std::to_string(context->data.score);
	proj = glm::ortho(0.0f, static_cast<GLfloat>(window_size.x), 0.0f, static_cast<GLfloat>(window_size.y));
	font.loadFromFile(FONT_PATH);

	// Set up the title
	title.setFont(&font);
	title.setPosition(250.0f, 448.0f);
	title.setScale(1.5f);
	title.setString(TITLE);
	title.setColour(glm::vec3(1.0f, 0.0f, 0.0f));
	title.setProjection(proj);

	// Set the score message
	score.setFont(&font);
	score.setPosition(330.0f, 370.0f);
	score.setString(score_str);
	score.setColour(glm::vec3(0.0f, 1.0f, 0.0f));
	score.setProjection(proj);
	
	EventManager *event_mgr = context->event_mgr;
	event_mgr->addCallback(SPACE_BAR_EVENT, &GameOverState::backToMenu, this);

	background = new Background(nullptr);
	background->setPosition(glm::vec2(window_size.x / 2.0f, window_size.y / 2.0f));
	background->setTexture(texture_mgr->getTexture(BACKGROUND_TEXTURE));
}

void GameOverState::destroy()
{
	EventManager *event_mgr = context->event_mgr;
	event_mgr->removeCallback(SPACE_BAR_EVENT);

	if (background != nullptr)
	{
		delete background;
		background = nullptr;
	}
}

void GameOverState::update(float dt)
{
}

void GameOverState::draw()
{
	render.drawSprite(background);
	title.draw();
	score.draw();
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
