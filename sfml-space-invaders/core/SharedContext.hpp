#ifndef CORE_SHARED_CONTEXT_HPP
#define CORE_SHARED_CONTEXT_HPP

#include "common.hpp"

class EventManager;
class Window;

struct SharedContext
{
	Window *window;
	EventManager *event_mgr;
	GameData data;
};

#endif // CORE_SHARED_CONTEXT_HPP