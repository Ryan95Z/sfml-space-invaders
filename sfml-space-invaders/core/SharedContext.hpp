#ifndef CORE_SHARED_CONTEXT_HPP
#define CORE_SHARED_CONTEXT_HPP

#include "managers/EventManager.hpp"

struct SharedContext
{
	EventManager *event_mgr;
};

#endif // CORE_SHARED_CONTEXT_HPP