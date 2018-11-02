#ifndef COLLIDER_H
#define COLLIDER_H
#include "Body.h"

class Collider
{
public:
	static bool Collided(const Body& b1, const Body& b2);
	static void HandleCollision(Body& b1, Body& b2);
};
#endif // !COLLIDER_H

