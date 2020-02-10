#ifndef STATES_GAME_OVER_STATE_HPP
#define STATES_GAME_OVER_STATE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../core/BaseState.hpp"
#include "../core/SpriteRender.hpp"
#include "../core/managers/EventManager.hpp"

#include "../core/gui/Font.hpp"
#include "../core/gui/Text.hpp"

#define FONT_PATH "font/arial.ttf"

#include "../entities/Background.hpp"

class GameOverState : public BaseState
{
public:
	GameOverState() = delete;
	GameOverState(GameOverState &) = delete;
	GameOverState(StateID id, StateManager *state_mgr, SharedContext *context);
	virtual ~GameOverState();

	virtual void start();
	virtual void stop();
	 
	virtual void init();
	virtual void destroy();

	virtual void update(float dt);
	virtual void draw();

	virtual void cleanup();
	virtual void reset();
protected:
	void backToMenu(EventDetails *details);
private:
	Font font;
	Text title;
	Text score;
	glm::mat4 proj;
	Background *background;
	SpriteRender render;
};

#endif // STATES_GAME_OVER_STATE_HPP