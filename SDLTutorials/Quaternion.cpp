#include "Quaternion.h"
#include <iostream>

/* Constructors */
Quaternion::Quaternion()
{
	quaternion.Set(0,0,0,1);
}

Quaternion::Quaternion(const Vector4& v) {
	quaternion = v;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
	quaternion = Vector4(x, y, z, w);
}

Quaternion::Quaternion(Vector3 axis, float angle) {
	axis.Normalize();
	Vector3 a(axis * sinf(DEGREESTORAD(angle) / 2));
	quaternion.Set(a.x, a.y, a.z, cosf(DEGREESTORAD(angle) / 2));
}

/* Member Methods */

//Convert Quaternion to Matrix
Matrix4 Quaternion::ConvertToMatrix() {
	return Matrix4(
		 quaternion.x, quaternion.y, quaternion.z, quaternion.w, 
		-quaternion.y, quaternion.x, quaternion.w, -quaternion.z, 
		-quaternion.z, -quaternion.w, quaternion.x, quaternion.y, 
		-quaternion.w, quaternion.z, -quaternion.y, quaternion.x );
}

//Rotates Quaternion given Vector
Vector3 Quaternion::Rotate(const Vector3& v) {
	Quaternion p(v);
	Quaternion inverse = quaternion;
	inverse.Inverse();
	Quaternion result = *this * p * inverse;
	return Vector3(result.quaternion);
}

//Returns the Dot Product of the quaternion
float Quaternion::Dot(const Quaternion& q) {
	return (quaternion.w * q.quaternion.w) + Vector3(quaternion).Dot(q.quaternion);
}

//Returns the Magnitude of the quaternion
float Quaternion::Mag() {
	return sqrtf((quaternion.w * quaternion.w) + (Vector3(quaternion).Mag() * Vector3(quaternion).Mag()));
}

//Normalizes the quaternion
void Quaternion::Normalize() {
	quaternion = quaternion / Mag();
}

//Converts the quaternion to the conjugate
void Quaternion::Conjugate() {
	quaternion.Set(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

//Inverts the quaternion
void Quaternion::Inverse() {
	Quaternion congugate(quaternion);
	congugate.Conjugate();
	quaternion = congugate.quaternion / (Mag() * Mag());
}

Quaternion Quaternion::Lerp(const Quaternion& otherQuat, float t) {
	if (t < 0) {
		std::cout << "Invalid t Value, No interpolation below 0" << std::endl;
		return Quaternion();
	}
	else if (t > 1) {
		std::cout << "Invalid t Value, Not interpolation beyond 1" << std::endl;
		return Quaternion();
	}
	else if (t == 0) {
		return *this;
	}
	else if (t == 1) {
		return otherQuat;
	}
	else {
		Quaternion q2 = otherQuat;
		Normalize();
		q2.Normalize();
		return Quaternion(quaternion * (1 - t) + q2.quaternion * t);
	}
}

//Slerping Quaternion
Quaternion Quaternion::Slerp(const Quaternion& otherQuat, float t) {
	if (t < 0) {
		std::cout << "Invalid t Value, No interpolation below 0" << std::endl;
		return Quaternion();
	}
	else if (t > 1) {
		std::cout << "Invalid t Value, Not interpolation beyond 1" << std::endl;
		return Quaternion();
	}
	else if (t == 0) {
		return *this;
	}
	else if (t == 1) {
		return otherQuat;
	}
	else {
		Quaternion q2 = otherQuat;
		Normalize();
		q2.Normalize();
		//if the dot product are close LERP
		if (Dot(q2) > 0.99f) {
			return Lerp(q2, t);
		}
		else {
			//Check Which Dot contains Shortest Path
			if (Dot(q2) >= 0) {
				float theta = acosf(DEGREESTORAD(Dot(q2)));
				std::cout << "Theta: " << theta << std::endl;
				return Quaternion(quaternion * (sinf(theta * (1 - t)) / sinf(theta)) + q2.quaternion * (sinf(t * theta) / sinf(theta)));
			}
			else {
				//Negate Quaternions
				-quaternion;
				-q2.quaternion;
				float theta = acosf(DEGREESTORAD(Dot(q2)));
				return Quaternion(quaternion * (sinf(theta * (1 - t)) / sinf(theta)) + q2.quaternion * (sinf(t * theta) / sinf(theta)));
			}
		}
	}
}

/* Operator Overloads */

Quaternion& Quaternion::operator=(const Quaternion& q) {
	quaternion = q.quaternion;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q) {
	Vector3 v = (Vector3(quaternion) * q.quaternion.w) + (Vector3(q.quaternion) * quaternion.w) + Vector3(quaternion).Cross(Vector3(q.quaternion));
	float w  = (quaternion.w * q.quaternion.w) - (Vector3(quaternion).Dot(Vector3(q.quaternion)));
	Vector4 temp(v.x, v.y, v.z, w);
	return Quaternion(temp);
}

Quaternion Quaternion::operator+(const Quaternion& q) {
	return Quaternion(quaternion + q.quaternion);
}

Quaternion Quaternion::operator-(const Quaternion& q) {
	return Quaternion(quaternion - q.quaternion);
}