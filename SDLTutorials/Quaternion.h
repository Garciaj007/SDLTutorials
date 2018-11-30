#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Matrix4.h"

class Quaternion
{
public:
	mutable Vector4 quaternion;

	Quaternion();
	Quaternion(Vector3 axis, float angle);
	Quaternion(const Vector4& v);
	Quaternion(const Quaternion& q);

	Vector3 Rotate(const Vector3& v);
	Matrix4 ConvertToMatrix();
	float Mag();
	float Dot(const Quaternion& q);
	void Normalize();
	void Conjugate();
	void Inverse();
	void Slerp(const Quaternion& otherQuat, float t);
	
	Quaternion& operator=(const Quaternion& q);
	Quaternion operator*(const Quaternion& q);
	Quaternion operator+(const Quaternion& q);
	Quaternion operator-(const Quaternion& q);
	Quaternion operator/(const Quaternion& q)
};

#endif
