#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include <SDL/SDL.h>

class Body {
private:
	float radius, mass, rotationalInertia, angle, angularVel, angularAccel;
	Vector3 pos, vel, accel, worldForce, forceApplied;
	bool gravity;
public:
	Body(float mass_, float rotationalInertia_);
	Body(float mass_, Vector3 pos_, Vector3 vel_, Vector3 accel_);

	void Update(const float deltaTime);
	void ApplyForce(Vector3 force);
	void ApplyTorque(float torque);
};


#endif
