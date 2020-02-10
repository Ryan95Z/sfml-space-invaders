#include "GameState.hpp"
#include "StateInfo.hpp"
#include "../core/managers/EventInfo.hpp"

#include "../core/tools/Logger.hpp"
#include "../core/Window.hpp"
#include "../entities/AlienProjectile.hpp"

#define MOVEMENT_STEP 250
#define ALIEN_INITIAL_X 25.0f
#define ALIEN_INITIAL_Y 50.0f
#define ALIEN_POS_INCREMENT 60.0f
#define ALIEN_FIRE_VAL 101
#define ALIEN_FIRE_VAL_2 11
#define ALIENS_PER_ROW 11
#define ALIEN_ROW_COUNT 7
#define ALIEN_COUNT (ALIENS_PER_ROW * ALIEN_ROW_COUNT)
#define SCORE_INCREMENT 10
#define BULLET_INITIAL_POS_PADDING 20.0f
#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)
#define WORLD_GRAVITY b2Vec2(0.0f, 0.0f)
#define PLAYER_START_POS glm::vec2(350.0f, 700.0f)
#define SCORE_TEXT_POS glm::vec2(20.0f, 10.0f)
#define LIVES_TEXT_POS glm::vec2(600.0f, 10.0f)
#define ARIAL_FONT_PATH "font/arial.ttf"
#define SCORE_TXT_TEMPLATE "Score: "
#define LIVES_TXT_TEMPLATE "Lives: "

GameState::GameState(StateID id, StateManager *state_mgr, SharedContext *context) : BaseState(id, state_mgr, context),
	world(nullptr), player(nullptr), dist(nullptr), background(nullptr)  {}

GameState::~GameState()
{
	destroy();
	cleanup();
}

void GameState::start()
{
	Alien *s = nullptr;
	float alien_x = ALIEN_INITIAL_X;
	float alien_y = ALIEN_INITIAL_Y;

	score = 0;
	bullet_rounds = BULLET_MAGAZINE;
	
	// Set the context data
	context->data.has_player_won = false;
	context->data.score = score;

	// Create the Aliens and set the initial positions
	for (int i = 0; i < ALIEN_COUNT; ++i)
	{
		s = new Alien(world, glm::vec2(alien_x, alien_y));
		aliens.push_back(s);
		alien_x += ALIEN_POS_INCREMENT;

		// Move the Alien to the row underneath the current one.
		// This creates the grid of aliens
		if ((i + 1) % ALIENS_PER_ROW == 0) {
			alien_x = ALIEN_INITIAL_X;
			alien_y += ALIEN_POS_INCREMENT;
		}

		s->setTexture(texture_mgr->getTexture(ALIEN_TEXTURE));
	}

	background = new Background(world);
	background->setPosition(glm::vec2(window_size.x / 2.0f, window_size.y / 2.0f));
	background->setTexture(texture_mgr->getTexture(BACKGROUND_TEXTURE));

	// Create the player
	player = new Player(world, PLAYER_START_POS);
	player->setTexture(texture_mgr->getTexture(CANNON_TEXTURE));
	setScreenText();
}

void GameState::stop() {}

void GameState::init()
{
	Window *window = context->window;
	EventManager *event_mgr = context->event_mgr;
	const glm::ivec2 rand_dist_range = glm::ivec2(0, 2000);
	window_size = window->getSize();
	glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(window_size.x), 0.0f, static_cast<GLfloat>(window_size.y));

	is_game_over = false;
	dist = new std::uniform_int_distribution<int>(rand_dist_range.x, rand_dist_range.y);

	// Set up the world for Box2d
	world = new b2World(WORLD_GRAVITY);
	world->SetContactListener(&listener);

	// Set up the event callbacks
	event_mgr->addCallback(LEFT_EVENT, &GameState::left, this);
	event_mgr->addCallback(RIGHT_EVENT, &GameState::right, this);
	event_mgr->addCallback(LEFT_RELEASE_EVENT, &GameState::stop, this);
	event_mgr->addCallback(RIGHT_RELEASE_EVENT, &GameState::stop, this);
	event_mgr->addCallback(SPACE_BAR_EVENT, &GameState::fire, this);
	event_mgr->addCallback(R_BUTTON_RELEASE_EVENT, &GameState::reload, this);

	// Load in the font file
	font.loadFromFile(ARIAL_FONT_PATH);

	// Set up the score text
	score_txt.setFont(&font);
	score_txt.setProjection(proj);
	score_txt.setPosition(SCORE_TEXT_POS);

	// Set up the lives text
	lives_txt.setFont(&font);
	lives_txt.setProjection(proj);
	lives_txt.setPosition(LIVES_TEXT_POS);

	texture_mgr = context->texture_mgr;
	texture_mgr->loadTexture(ALIEN_TEXTURE, ALIEN_TEXTURE_PATH);
	texture_mgr->loadTexture(BULLET_TEXTURE, PLAYER_BULLET_TEXTURE_PATH);
	texture_mgr->loadTexture(ORB_TEXTURE, ALIEN_BULLET_TEXTURE_PATH);
	texture_mgr->loadTexture(CANNON_TEXTURE, CANNON_TEXTURE_PATH);
}

void GameState::destroy()
{
	// Remove the callback functions
	EventManager *event_mgr = context->event_mgr;
	event_mgr->removeCallback(LEFT_EVENT);
	event_mgr->removeCallback(RIGHT_EVENT);
	event_mgr->removeCallback(LEFT_RELEASE_EVENT);
	event_mgr->removeCallback(RIGHT_RELEASE_EVENT);
	event_mgr->removeCallback(SPACE_BAR_EVENT);
	event_mgr->removeCallback(R_BUTTON_RELEASE_EVENT);

	// Remove the textures from the manager
	texture_mgr->removeTexture(ALIEN_TEXTURE);
	texture_mgr->removeTexture(BULLET_TEXTURE);
	texture_mgr->removeTexture(ORB_TEXTURE);
	texture_mgr->removeTexture(CANNON_TEXTURE);

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

	// Remove all the enemy bullets from memory
	while (alien_bullets.begin() != alien_bullets.end())
	{
		delete *alien_bullets.begin();
		alien_bullets.erase(alien_bullets.begin());
	}

	// Remove the player from memory
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	// Remove the random number distributor
	if (dist != nullptr)
	{
		delete dist;
		dist = nullptr;
	}

	if (background != nullptr)
	{
		delete background;
		background = nullptr;
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
		enemyFire(*alien_itr);

		// Determine if the Alien has been hit
		if ((*alien_itr)->isHidden())
		{
			// Move to graveyard for removal
			score += SCORE_INCREMENT;
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

	// Go through the fired alien bullets
	bullet_itr = alien_bullets.begin();
	while (bullet_itr != alien_bullets.end())
	{
		(*bullet_itr)->update(dt);
		if ((*bullet_itr)->getPosition().y > window_size.y || (*bullet_itr)->isHidden())
		{
			// Move to vector for removal
			spent_bullets.push_back(*bullet_itr);
			bullet_itr = alien_bullets.erase(bullet_itr);
			continue;
		}
		++bullet_itr;
	}

	// Update the labels on the screen
	setScreenText();

	// Game over conditions
	if ((aliens.size() == 0) || (player->getLives() == 0) && !is_game_over)
	{
		is_game_over = true;
		context->data.score = score;
		context->data.has_player_won = (player->getLives() != 0);

		// Stop the player if still moving
		stop();
		state_mgr->registerNextState(GAME_OVER_STATE_ID);
	}
}

void GameState::draw()
{
	render.drawSprite(background);

	// Render the sprites
	Sprite *sprite = nullptr;
	for (b2Body *body_itr = world->GetBodyList(); body_itr != 0; body_itr = body_itr->GetNext())
	{
		sprite = (Sprite *)body_itr->GetUserData();
		render.drawSprite(sprite);
	}

	// Render the text
	score_txt.draw();
	lives_txt.draw();
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

void GameState::reset()
{
}

void GameState::left(EventDetails * details)
{
	if (is_game_over) { return; }
	player->left();
}

void GameState::right(EventDetails * details)
{
	if (is_game_over) { return; }
	player->right();
}

void GameState::stop(EventDetails * details)
{
	if (is_game_over) { return;  }
	player->stop();
}

void GameState::fire(EventDetails * details)
{
	if (bullet_rounds == 0)
	{
		Logger::debug("RELOAD");
		return;
	}

	glm::vec2 bullet_initial_pos = player->getPosition();
	bullet_initial_pos.y -= BULLET_INITIAL_POS_PADDING;
	Projectile *bullet = new Projectile(world, bullet_initial_pos);
	bullet->setTexture(texture_mgr->getTexture(BULLET_TEXTURE));
	bullets.push_back(bullet);
	--bullet_rounds;
}

void GameState::reload(EventDetails * details)
{
	bullet_rounds = BULLET_MAGAZINE;
}

void GameState::enemyFire(Alien * alien)
{
	int fire_number = (*dist)(generator);
	glm::vec2 bullet_pos = alien->getPosition();
	Projectile *bullet = nullptr;

	if (is_game_over) { return; }

	if (fire_number == ALIEN_FIRE_VAL || fire_number == ALIEN_FIRE_VAL_2)
	{
		bullet = new AlienProjectile(world, bullet_pos);
		bullet->setTexture(texture_mgr->getTexture(ORB_TEXTURE));
		alien_bullets.push_back(bullet);
	}
}

void GameState::setScreenText()
{
	score_txt.setString(SCORE_TXT_TEMPLATE + std::to_string(score));
	lives_txt.setString(LIVES_TXT_TEMPLATE + std::to_string(player->getLives()));
}
