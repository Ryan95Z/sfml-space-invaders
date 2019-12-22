#ifndef LISTENERS_CONTACT_LISTENER_HPP
#define LISTENERS_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class GameContactListener : public b2ContactListener
{
public:
	GameContactListener() = default;
	~GameContactListener() = default;

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
};

#endif // LISTENERS_ALIEN_CONTACT_LISTENER_HPP