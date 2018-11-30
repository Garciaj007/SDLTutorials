#include "Quaternion.h"

Quaternion::Quaternion()
{
	quaternion.Set(0,0,0,1);
}

Quaternion::Quaternion(const Vector4& v) {
	quaternion = v;
}

Quaternion::Quaternion(Vector3 axis, float angle) {
	Vector3 a(axis * sinf(DEGREESTORAD(angle) / 2));
	quaternion.Set(a.x, a.y, a.z, cosf(DEGREESTORAD(angle) / 2));
}

Matrix4 Quaternion::ConvertToMatrix() {

}

Vector3 Quaternion::Rotate(const Vector3& v) {

}

float Quaternion::Dot(const Quaternion& q) {
	return (quaternion.w * q.quaternion.w) + Vector3(quaternion).Dot(q.quaternion);
}

float Quaternion::Mag() {
	return sqrtf((quaternion.w * quaternion.w) + (Vector3(quaternion).Mag() * Vector3(quaternion).Mag()));
}

void Quaternion::Normalize() {
	quaternion = quaternion / Mag();
}

void Quaternion::Conjugate() {
	quaternion.Set(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

void Quaternion::Inverse() {
	Quaternion congugate(quaternion);
	congugate.Conjugate();
	quaternion = congugate.quaternion / (Mag() * Mag());
}

void Quaternion::Slerp(const Quaternion& otherQuat, float t) {

}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	quaternion = q.quaternion;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q) {
	Vector3 imaj = (Vector3(quaternion) * q.quaternion.w) + (Vector3(q.quaternion) * quaternion.w) + Vector3(quaternion).Cross(Vector3(q.quaternion));
	float w  = (quaternion.w * q.quaternion.w) - (Vector3(quaternion).Dot(Vector3(q.quaternion)));
	Vector4 temp(imaj.x, imaj.y, imaj.z, w);
	return Quaternion(temp);
}

Quaternion Quaternion::operator+(const Quaternion& q) {
	return Quaternion(quaternion + q.quaternion);
}

Quaternion Quaternion::operator-(const Quaternion& q) {
	return Quaternion(quaternion - q.quaternion);
}