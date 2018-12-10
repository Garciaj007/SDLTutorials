#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Matrix4.h"

class Quaternion
{
public:
	//Member
	mutable Vector4 quaternion;

	//Constructors
	Quaternion();
	Quaternion(Vector3 axis, float angle);
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector4& v);

	//Member Methods
	Vector3 Rotate(const Vector3& v);
	Matrix4 ConvertToMatrix();
	float Mag();
	float Dot(const Quaternion& q);
	void Normalize();
	void Conjugate();
	void Inverse();
	Quaternion Slerp(const Quaternion& otherQuat, float t);
	Quaternion Lerp(const Quaternion& otherQuat, float t);
	
	//Operator Overloads
	Quaternion& operator=(const Quaternion& q);
	Quaternion operator*(const Quaternion& q);
	Quaternion operator+(const Quaternion& q);
	Quaternion operator-(const Quaternion& q);
};

#endif
