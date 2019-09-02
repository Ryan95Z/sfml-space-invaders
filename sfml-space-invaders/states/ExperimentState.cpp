#include "ExperimentState.hpp"

#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)
#define FLOOR_SIZE glm::vec2(800.0f, 50.0f)

#define SCALE 30.0f

ExperimentState::ExperimentState(StateID id, SharedContext *context) : BaseState(id, context), a1(nullptr)
{
	gravity = b2Vec2(0.0f, 9.8f);
	world = new b2World(gravity);

	a1 = new Alien(world);

	a1->setPosition(glm::vec2(200.0f, 20.0f));
}

ExperimentState::~ExperimentState()
{
	destroy();

	//world->DestroyBody(body);
	//world->DestroyBody(s_body);

	delete a1;
	a1 = nullptr;

	delete world;
	world = nullptr;
}

void ExperimentState::start() {}

void ExperimentState::stop() {}

void ExperimentState::init() {}

void ExperimentState::destroy() {}

void ExperimentState::update(float dt)
{
	world->Step(dt, 8, 3);
}

void ExperimentState::draw()
{
	for (b2Body *body_itr = world->GetBodyList(); body_itr != 0; body_itr = body_itr->GetNext())
	{
		b2Vec2 b2_pos = body_itr->GetPosition();
		if (body_itr->GetType() == b2_dynamicBody)
		{
			render.drawSprite(a1->getPosition(), a1->getSize());
		}
		else
		{
			glm::vec2 x = glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
			render.drawSprite(x, FLOOR_SIZE);
		}
	}
}

void ExperimentState::cleanup() {}
