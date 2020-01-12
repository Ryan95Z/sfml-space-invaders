#include <iostream>
#include "AlienProjectile.hpp"

#define PROJECTILE_VELOCITY b2Vec2(0.0f, 5.0f)

AlienProjectile::AlienProjectile(b2World * world) : Projectile(world, glm::vec2(0.0f, 0.0f), SpriteType::AlienProjectile)
{
	setCollisionDetails();
}

AlienProjectile::AlienProjectile(b2World * world, glm::vec2 pos) : Projectile(world, pos, SpriteType::AlienProjectile)
{
	setCollisionDetails();
}

void AlienProjectile::update(float dt)
{
	body->SetLinearVelocity(PROJECTILE_VELOCITY);
}

void AlienProjectile::beginContact(SpriteType type)
{
	if (type == SpriteType::Player)
	{
		is_hidden = true;
	}
}

void AlienProjectile::setCollisionDetails()
{
	b2Filter filter = fixture->GetFilterData();

	// Set that the current object is the alien projectile
	filter.categoryBits = ALIEN_PROJECTILE;

	// State that it only collides with the player
	filter.maskBits = PLAYER;

	fixture->SetFilterData(filter);
}
