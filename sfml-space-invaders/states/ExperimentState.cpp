#include "ExperimentState.hpp"

#define SPRITE_SIZE glm::vec2(50.0f, 50.0f)

#define SCALE 30.0f

ExperimentState::ExperimentState(StateID id, SharedContext *context) : BaseState(id, context)
{
	gravity = b2Vec2(0.0f, -9.8f);
	world = new b2World(gravity);
}

ExperimentState::~ExperimentState()
{
	destroy();

	world->DestroyBody(body);
	world->DestroyBody(s_body);

	delete world;
	world = nullptr;
}

void ExperimentState::start()
{
	pos = glm::vec2(100.0f, 700.0f);

	b2BodyDef mybodyDef;
	mybodyDef.type = b2_dynamicBody;
	mybodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);

	body = world->CreateBody(&mybodyDef);

	b2PolygonShape shape;
	shape.SetAsBox((50.0f / 2.0f) / SCALE, (50.0f / 2.0f) / SCALE);

	b2FixtureDef fixture_def;
	fixture_def.density = 1.0f;
	fixture_def.shape = &shape;
	body->CreateFixture(&fixture_def);

	s_pos = glm::vec2(0.0f, 200.0f);

	b2BodyDef s_bodyx;
	s_bodyx.type = b2_staticBody;
	s_bodyx.position = b2Vec2(s_pos.x / SCALE, s_pos.y / SCALE);

	s_body = world->CreateBody(&s_bodyx);

	b2PolygonShape s_shape;
	s_shape.SetAsBox((500.0f / 2.0f) / SCALE, (50.0f / 2.0f) / SCALE);

	b2FixtureDef s_fixture;
	s_fixture.density = 0.0f;
	s_fixture.shape = &s_shape;
	s_body->CreateFixture(&s_fixture);
}

void ExperimentState::stop()
{
}

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
			
			pos = glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
			render.drawSprite(pos, SPRITE_SIZE);
		}
		else
		{
			glm::vec2 x = glm::vec2(b2_pos.x * SCALE, b2_pos.y * SCALE);
			render.drawSprite(x, glm::vec2(800.0f, 50.0f));
		}
	}
}

void ExperimentState::cleanup() {}
