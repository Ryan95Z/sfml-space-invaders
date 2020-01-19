#include "TitleState.hpp"

TitleState::TitleState(StateID id, StateManager * state_mgr, SharedContext * context) : BaseState(id, state_mgr, context)
{
}

TitleState::~TitleState()
{
	destroy();
}

void TitleState::start()
{
}

void TitleState::stop()
{
}

void TitleState::init()
{
}

void TitleState::destroy()
{
}

void TitleState::update(float dt)
{
}

void TitleState::draw()
{
}

void TitleState::cleanup()
{
}

void TitleState::reset()
{
}




