#include "GameState.hpp"

#include "../core/tools/Logger.hpp"

#define LEFT_EVENT "left"
#define LEFT_RELEASE_EVENT "left_released"
#define RIGHT_EVENT "right"
#define RIGHT_RELEASE_EVENT "right_released" 
#define SPACE_BAR_EVENT "space_bar"

#define MOVEMENT_STEP 250

#define ALIEN_INITIAL_X 200.0f
#define ALIEN_INITIAL_Y 100.0f
#define ALIEN_POS_INCREMENT 100.0f

#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)

GameState::GameState(StateID id, SharedContext *context) : BaseState(id, context) {}

GameState::~GameState()
{
	cleanup();
}

void GameState::start()
{
	float alien_x = ALIEN_INITIAL_X;
	float alien_y = ALIEN_INITIAL_Y;
	
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		alien_pos[i] = glm::vec2(alien_x, alien_y);
		alien_x += ALIEN_POS_INCREMENT;

		if ((i + 1) % 5 == 0) {
			alien_x = ALIEN_INITIAL_X;
			alien_y += ALIEN_POS_INCREMENT;
		}
	}

	// Player's initial position
	pos = glm::vec2(400.0f, 700.0f);

	game_count = 0;
}

void GameState::stop() {}

void GameState::init()
{
	EventManager *event_mgr = context->event_mgr;
	event_mgr->addBinding(LEFT_EVENT, EventType::KeyPressed, sf::Keyboard::A);
	event_mgr->addBinding(RIGHT_EVENT, EventType::KeyPressed, sf::Keyboard::D);
	event_mgr->addBinding(LEFT_RELEASE_EVENT, EventType::KeyReleased, sf::Keyboard::A);
	event_mgr->addBinding(RIGHT_RELEASE_EVENT, EventType::KeyReleased, sf::Keyboard::D);
	event_mgr->addBinding(SPACE_BAR_EVENT, EventType::KeyPressed, sf::Keyboard::Space);

	event_mgr->addCallback(LEFT_EVENT, &GameState::left, this);
	event_mgr->addCallback(RIGHT_EVENT, &GameState::right, this);
	event_mgr->addCallback(LEFT_RELEASE_EVENT, &GameState::stop, this);
	event_mgr->addCallback(RIGHT_RELEASE_EVENT, &GameState::stop, this);
	event_mgr->addCallback(SPACE_BAR_EVENT, &GameState::fire, this);
}

void GameState::destroy() {}

void GameState::update(float dt)
{
	pos += velocity * dt;

	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		if (move_left == true)
		{
			alien_pos[i].x -= 100 * dt;
		}
		else
		{
			alien_pos[i].x += 100 * dt;
		}
	}
	game_count++;
	if (game_count == 100)
	{
		game_count = 0;
		move_left = !move_left;
	}

	PositionVector::iterator itr = pvec.begin();
	while (itr != pvec.end())
	{
		if (itr->y < 0.0f) {
			rvec.push_back(itr);
		}

		itr->y -= 200.0f * dt;
		++itr;
	}

	Logger::debug("Projectiles: " + std::to_string(pvec.size()));
	
	
}

void GameState::draw()
{
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		render.drawSprite(alien_pos[i], SPRITE_SIZE);
	}

	for (glm::vec2 &p : pvec)
	{
		render.drawSprite(p, glm::vec2(10.0f, 10.0f));
	}

	render.drawSprite(pos, SPRITE_SIZE);

}

void GameState::cleanup()
{
	while (rvec.begin() != rvec.end())
	{
		pvec.erase(*rvec.begin());
		rvec.erase(rvec.begin());
	}
}

void GameState::left(EventDetails * details)
{
	velocity.x = -MOVEMENT_STEP;
}

void GameState::right(EventDetails * details)
{
	velocity.x = MOVEMENT_STEP;
}

void GameState::stop(EventDetails * details)
{
	velocity.x = 0;
}

void GameState::fire(EventDetails * details)
{
	glm::vec2 x = pos;
	x.x += 20.0f;
	pvec.push_back(glm::vec2(x));
}
