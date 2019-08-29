#ifndef STATES_EXPERIMENT_STATE_HPP
#define STATES_EXPERIMENT_STATE_HPP

#include <Box2D/Box2D.h>

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#include "../entities/Alien.hpp"

class ExperimentState : public BaseState
{
public:
	ExperimentState(StateID id, SharedContext *context);
	virtual ~ExperimentState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
private:
	b2Vec2 gravity;
	b2World *world;

	Alien *a1;

	glm::vec2 pos;
	glm::vec2 s_pos;
	SpriteRender render;

	b2Body *body;
	b2Body *s_body;
};

#endif // STATES_EXPERIMENT_STATE_HPP