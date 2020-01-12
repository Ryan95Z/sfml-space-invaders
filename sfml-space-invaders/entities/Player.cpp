#include "Player.hpp"

#define PLAYER_SIZE glm::vec2(50.0f, 50.0f)

Player::Player(b2World * world) : Sprite(world, b2_staticBody, SpriteType::Player, PLAYER_SIZE, 0.0f)
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

void Player::setUpCollision()
{
	b2Filter filter = fixture->GetFilterData();
	filter.categoryBits = 0x002;
	filter.maskBits = 0x001;

	fixture->SetFilterData(filter);
}
