#ifndef STATES_TITLE_STATE_HPP
#define STATES_TITLE_STATE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/BaseState.hpp"
#include "../core/gui/Font.hpp"
#include "../core/gui/Text.hpp"

#include "../core/managers/EventManager.hpp"

#define FONT_PATH "font/arial.ttf"

class TitleState : public BaseState
{
public:
	TitleState(StateID id, StateManager *state_mgr, SharedContext *context);
	virtual ~TitleState();

	virtual void start();
	virtual void stop();

	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
	virtual void reset();
private:
	void startGame(EventDetails *details);

	glm::mat4 proj;
	Font arial;
	Text title;
	Text instructions;
};

#endif // !STATES_TITLE_STATE_HPP