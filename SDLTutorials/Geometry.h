#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Vector.h"
#include <vector>
struct Ray {
	//Member Variables
	mutable Vector3 start; ///Start Point
	mutable Vector3 direction; ///Direction

	//Constructor
	Ray(Vector3 start_, Vector3 direction_);

	//Member Methods
	Vector3 currentPosition(float t);
};

class Plane {
private:
	//Member Variable
	Vector4 plane;
public:
	//Constructor
	Plane(float x_, float y_, float z_, float d_);
	Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2);

	//Member Methods
	Vector3 IntersectionPoint(Ray ray);
};
#endif

