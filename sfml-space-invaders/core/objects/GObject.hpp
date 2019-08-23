#ifndef CORE_OBJECTS_GOBJECT_HPP
#define CORE_OBJECTS_GOBJECT_HPP

class GObject
{
public:
	virtual void draw() = 0;
	virtual void update(float dt) = 0;
};

#endif // CORE_OBJECTS_GOBJECT_HPP