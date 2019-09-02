#include "Alien.hpp"

#define SCALE 30.0f
#define ALIEN_SIZE glm::vec2(50.0f, 50.0f)
#define ALIEN_BODY_DENSITY 1.0f

Alien::Alien(b2World * world) : Sprite(world, b2_dynamicBody, ALIEN_SIZE, ALIEN_BODY_DENSITY) {}

Alien::~Alien() {}
