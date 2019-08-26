#include "GameState.hpp"

#define LEFT_EVENT "left"
#define RIGHT_EVENT "right"
#define SPACE_BAR_EVENT "space_bar"

#define MOVEMENT_STEP 500


GameState::GameState(StateID id, SharedContext *context) : BaseState(id, context) {}

GameState::~GameState() {}

void GameState::start()
{
	float alien_x = 100.0f;
	float alien_y = 200.0f;

	pos = glm::vec2(400.0f, 700.0f);
	
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		alien_pos[i] = glm::vec2(alien_x, alien_y);
		alien_x += 60.0f;
	}
}

void GameState::stop() {}

void GameState::init()
{
	EventManager *event_mgr = context->event_mgr;
	event_mgr->addBinding(LEFT_EVENT, EventType::KeyPressed, sf::Keyboard::A);
	event_mgr->addBinding(RIGHT_EVENT, EventType::KeyPressed, sf::Keyboard::D);
	event_mgr->addBinding(SPACE_BAR_EVENT, EventType::KeyPressed, sf::Keyboard::Space);

	event_mgr->addCallback(LEFT_EVENT, &GameState::left, this);
	event_mgr->addCallback(RIGHT_EVENT, &GameState::right, this);
	event_mgr->addCallback(SPACE_BAR_EVENT, &GameState::fire, this);
}

void GameState::destroy() {}

void GameState::update(float dt)
{
	deltaTime = dt;
}

void GameState::draw()
{
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		render.drawSprite(alien_pos[i]);
	}

	render.drawSprite(pos);
}

void GameState::left(EventDetails * details)
{
	pos.x -= MOVEMENT_STEP * deltaTime;
}

void GameState::right(EventDetails * details)
{
	pos.x += MOVEMENT_STEP * deltaTime;
}

void GameState::fire(EventDetails * details) {}
