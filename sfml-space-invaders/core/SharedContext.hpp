#ifndef CORE_SHARED_CONTEXT_HPP
#define CORE_SHARED_CONTEXT_HPP

#include "managers/TextureManager.hpp"
#include "common.hpp"

class EventManager;
class Window;

struct SharedContext
{
	Window *window;
	EventManager *event_mgr;
	TextureManager *texture_mgr;
	GameData data;
};

#endif // CORE_SHARED_CONTEXT_HPP