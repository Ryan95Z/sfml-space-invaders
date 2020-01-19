#include "ExperimentState.hpp"

#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)
#define FLOOR_SIZE glm::vec2(800.0f, 50.0f)

#define SCALE 30.0f

ExperimentState::ExperimentState(StateID id, SharedContext *context) : BaseState(id, context), a1(nullptr)
{
}

ExperimentState::~ExperimentState()
{
	destroy();
}

void ExperimentState::start() {}

void ExperimentState::stop() {}

void ExperimentState::init()
{
	gravity = b2Vec2(0.0f, 9.8f);
	world = new b2World(gravity);

	a1 = new Alien(world);
	a1->setPosition(glm::vec2(200.0f, 30.0f));

	f1 = new Floor(world);
	f1->setPosition(glm::vec2(400.0f, 600.0f));
}

void ExperimentState::destroy()
{
	delete a1;
	a1 = nullptr;

	delete f1;
	f1 = nullptr;

	delete world;
	world = nullptr;
}

void ExperimentState::update(float dt)
{
	world->Step(dt, 8, 3);
	a1->update(dt);
}

void ExperimentState::draw()
{
	Sprite *sprite = nullptr;
	for (b2Body *body_itr = world->GetBodyList(); body_itr != 0; body_itr = body_itr->GetNext())
	{
		sprite = (Sprite *) body_itr->GetUserData();
		render.drawSprite(sprite);
	}
}

void ExperimentState::cleanup() {}
