#include "GameState.hpp"

#include "../core/tools/Logger.hpp"

#define LEFT_EVENT "left"
#define LEFT_RELEASE_EVENT "left_released"
#define RIGHT_EVENT "right"
#define RIGHT_RELEASE_EVENT "right_released" 
#define SPACE_BAR_EVENT "space_bar"

#define MOVEMENT_STEP 250

#define ALIEN_INITIAL_X 50.0f
#define ALIEN_INITIAL_Y 100.0f
#define ALIEN_POS_INCREMENT 100.0f

#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)

GameState::GameState(StateID id, SharedContext *context) : BaseState(id, context),
	world(nullptr), player(nullptr) {}

GameState::~GameState()
{
	destroy();
	cleanup();
}

void GameState::start()
{
	float alien_x = ALIEN_INITIAL_X;
	float alien_y = ALIEN_INITIAL_Y;
	
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		aliens.push_back(new Alien(world, glm::vec2(alien_x, alien_y)));
		alien_x += ALIEN_POS_INCREMENT;

		if ((i + 1) % 5 == 0) {
			alien_x = ALIEN_INITIAL_X;
			alien_y += ALIEN_POS_INCREMENT;
		}
	}

	player = new Player(world, glm::vec2(400.0f, 700.0f));
}

void GameState::stop() {}

void GameState::init()
{
	b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);
	world->SetContactListener(&listener);

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

void GameState::destroy()
{
	// Remove all aliens from memory
	while (aliens.begin() != aliens.end())
	{
		delete *aliens.begin();
		aliens.erase(aliens.begin());
	}

	// Remove all the bullets from memory
	while (bullets.begin() != bullets.end())
	{
		delete *bullets.begin();
		bullets.erase(bullets.begin());
	}

	// Remove the player from memory
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

void GameState::update(float dt)
{
	world->Step(dt, 8, 3);
	for (Alien *alien : aliens)
	{
		alien->update(dt);
	}

	player->update(dt);

	Projectile *p = nullptr;
	ProjectileVector::iterator bullet_itr = bullets.begin();
	while (bullet_itr != bullets.end())
	{
		p = *bullet_itr;
		if (p->getPosition().y < 0.0f)
		{
			removal.push_back(bullet_itr);
		}
		++bullet_itr;
	}
}

void GameState::draw()
{

	Sprite *sprite = nullptr;
	for (b2Body *body_itr = world->GetBodyList(); body_itr != 0; body_itr = body_itr->GetNext())
	{
		sprite = (Sprite *)body_itr->GetUserData();
		render.drawSprite(sprite);
	}
}

void GameState::cleanup()
{
	for (ProjectileVector::iterator itr : removal)
	{
		delete *itr;
		bullets.erase(itr);
	}
	bullets.clear();
}

void GameState::left(EventDetails * details)
{
	player->left();
}

void GameState::right(EventDetails * details)
{
	player->right();
}

void GameState::stop(EventDetails * details)
{
	player->stop();
}

void GameState::fire(EventDetails * details)
{
	glm::vec2 pos = player->getPosition();
	Projectile *p = new Projectile(world, pos);
	bullets.push_back(p);
}
