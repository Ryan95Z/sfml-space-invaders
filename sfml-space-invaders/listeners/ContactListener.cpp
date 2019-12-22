#include "ContactListener.hpp"

#include <iostream>

#include "../core/Sprite.hpp"

void GameContactListener::BeginContact(b2Contact * contact)
{
	Sprite *body_a = (Sprite *)contact->GetFixtureA()->GetBody()->GetUserData();
	Sprite *body_b = (Sprite *)contact->GetFixtureB()->GetBody()->GetUserData();

	body_a->beginContact(body_b->getType());
	body_b->beginContact(body_a->getType());
}

void GameContactListener::EndContact(b2Contact * contact) {}
