#ifndef CORE_SHARED_CONTEXT_HPP
#define CORE_SHARED_CONTEXT_HPP

class EventManager;
class Window;

struct SharedContext
{
	Window *window;
	EventManager *event_mgr;
};

#endif // CORE_SHARED_CONTEXT_HPP