#include "Body.h" 

Body::Body(float mass_, float rotaionalInertia_) {
	mass = mass_;
	rotationalInertia = rotaionalInertia_;

	pos.Set(0, 0, 0);
	vel.Set(0, 0, 0);
	accel.Set(0, 0, 0);
	worldForce.Set(0, 0, 0);
}

Body::Body(float mass_, Vector3 pos_, Vector3 vel_, Vector3 accel_) {
	mass = mass_;
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;

	radius = 1.0f;
}

void Body::Update(const float deltaTime) {
	//With Gravity
	if (gravity) {
		pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
		pos.y += (vel.y * deltaTime) + (0.5f * (accel.y + -9.8f) * (deltaTime * deltaTime));
		pos.z += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));

		vel.x += accel.x * deltaTime;
		vel.y += (accel.y + -9.8f) * deltaTime;
		vel.z += accel.z * deltaTime;

		/// Assuming all acceleration comes from an applied force - maybe not in the future - gravity!!
		//accel.x = 0.0f;
		//accel.y = 0.0f;
		//accel.z = 0.0f;

		if (pos.y < 1.5f) {
			pos.y = 1.5f;
		}
	}
	else {

		//Update Orientation Angle : Angle = initAngle + W(init)*time + 1/2AngularAcel(time^2)
		angle += (angularVel * deltaTime) + (0.5f * angularAccel * (deltaTime * deltaTime));

		//Update Angular Velocity W = W(initial) + AngularAccel*time
		angularVel += angularAccel * deltaTime;

		//Rotate force Vector 
		worldForce.x = (forceApplied.x * cos(angle)) + (forceApplied.y * -sin(angle));
		worldForce.y = (forceApplied.x * sin(angle)) + (forceApplied.y * cos(angle));

		//Apply force 
		accel = worldForce / mass;

		//Update Positon 
		pos += (vel * deltaTime) + (accel * 0.5f * (deltaTime * deltaTime));

		//Velocity
		vel += accel * deltaTime;
	}
}

//Sets force
void Body::ApplyForce(Vector3 force) {
	forceApplied = force;
}

//Status:Good
void Body::ApplyTorque(float torque) {
	angularAccel = torque / rotationalInertia;
}