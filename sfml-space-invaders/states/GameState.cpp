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
#define BULLET_INITIAL_POS_PADDING 20.0f
#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)
#define WORLD_GRAVITY b2Vec2(0.0f, 0.0f)
#define PLAYER_START_POS glm::vec2(400.0f, 700.0f)

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
	
	// Create the Aliens
	for (int i = 0; i < NUM_ALIENS; ++i)
	{
		aliens.push_back(new Alien(world, glm::vec2(alien_x, alien_y)));
		alien_x += ALIEN_POS_INCREMENT;

		if ((i + 1) % 5 == 0) {
			alien_x = ALIEN_INITIAL_X;
			alien_y += ALIEN_POS_INCREMENT;
		}
	}

	// Create the player
	player = new Player(world, PLAYER_START_POS);
}

void GameState::stop() {}

void GameState::init()
{
	EventManager *event_mgr = context->event_mgr;
	
	// Set up the world for Box2d
	world = new b2World(WORLD_GRAVITY);
	world->SetContactListener(&listener);

	// Set up the event bindings
	event_mgr->addBinding(LEFT_EVENT, EventType::KeyPressed, sf::Keyboard::A);
	event_mgr->addBinding(RIGHT_EVENT, EventType::KeyPressed, sf::Keyboard::D);
	event_mgr->addBinding(LEFT_RELEASE_EVENT, EventType::KeyReleased, sf::Keyboard::A);
	event_mgr->addBinding(RIGHT_RELEASE_EVENT, EventType::KeyReleased, sf::Keyboard::D);
	event_mgr->addBinding(SPACE_BAR_EVENT, EventType::KeyPressed, sf::Keyboard::Space);

	// Set up the event callbacks
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
	// Update rate for Box2d
	world->Step(dt, 8, 3);
	
	// Go through the list of alive Aliens
	AlienVector::iterator alien_itr = aliens.begin();
	while (alien_itr != aliens.end())
	{
		(*alien_itr)->update(dt);

		// Determine if the Alien has been hit
		if ((*alien_itr)->isHidden())
		{
			// Move to graveyard for removal
			graveyard.push_back(*alien_itr);
			alien_itr = aliens.erase(alien_itr);
			continue;
		}
		++alien_itr;
	}

	player->update(dt);

	// Go through the fire bullets
	ProjectileVector::iterator bullet_itr = bullets.begin();
	while (bullet_itr != bullets.end())
	{
		(*bullet_itr)->update(dt);

		// If the bullet has gone above the viewable area
		if ((*bullet_itr)->getPosition().y < 0.0f || (*bullet_itr)->isHidden())
		{
			// Move to vector for removal
			spent_bullets.push_back(*bullet_itr);
			bullet_itr = bullets.erase(bullet_itr);
			continue;
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
	// Remove the bullets from memory
	for (Projectile *bullet : spent_bullets)
	{
		delete bullet;
	}
	spent_bullets.clear();

	// Remove the "dead" Aliens from memory
	for (Alien *alien : graveyard)
	{
		delete alien;
	}
	graveyard.clear();
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
	glm::vec2 bullet_initial_pos = player->getPosition();
	bullet_initial_pos.y -= BULLET_INITIAL_POS_PADDING;
	Projectile *bullet = new Projectile(world, bullet_initial_pos);
	bullets.push_back(bullet);
}
