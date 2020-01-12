#include "Player.hpp"

#define PLAYER_SIZE glm::vec2(50.0f, 50.0f)
#define PLAYER_LIVES 3

Player::Player(b2World * world) : Sprite(world, b2_staticBody, SpriteType::Player, PLAYER_SIZE, 0.0f),
	lives(PLAYER_LIVES)
{
	setUpCollision();
}

Player::Player(b2World * world, glm::vec2 pos) : Player(world)
{
	this->setPosition(pos);
	setUpCollision();
}

Player::~Player() {}

void Player::update(float dt)
{
	glm::vec2 pos = this->getPosition();
	pos.x += (velocity * dt);
	this->setPosition(pos);
}

void Player::beginContact(SpriteType type)
{
	if ((type == SpriteType::AlienProjectile) && (lives > 0))
	{
		--lives;
	}
}

void Player::endContact(SpriteType type)
{
}

void Player::left()
{
	velocity = -100.0f;
}

void Player::right()
{
	velocity = 100.0f;
}

void Player::stop()
{
	velocity = 0.0f;
}

bool Player::isDead() const
{
	return is_dead;
}

const unsigned int Player::getLives() const
{
	return lives;
}

void Player::setUpCollision()
{
	b2Filter filter = fixture->GetFilterData();

	// Set that the current object is the player
	filter.categoryBits = PLAYER;

	// State that it only collides with the Alien projectile
	filter.maskBits = ALIEN_PROJECTILE;

	fixture->SetFilterData(filter);
}
