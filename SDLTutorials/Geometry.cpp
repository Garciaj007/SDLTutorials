#include "Geometry.h"
#include <iostream>

//--------------------------------------------------------- Ray ------------------------------------------------------------
//Set Starting Point & Direction
Ray::Ray(Vector3 start_, Vector3 direction_) {
	start = start_;
	direction = direction_;
}

//Get Position at t
Vector3 Ray::currentPosition(float t) {
	Vector3 position;

	if (t == 0.0f) {
		//if t = 0, P(t) = S
		position = start; 
	} else if (t > 0.0f) {
		//if t > 0, P(t) = S * Vt;
		position = start;
		position += (direction * t);
	}
	else {
		//t < 0, t is not a ray.
		std::cout << "The value of t must be >= 0, or else it is considered a line. Please enter a valid t value" << std::endl;
	}

	return position;
}

//--------------------------------------------------------- Plane -----------------------------------------------------------

//Az + By + Cz + D = 0;
Plane::Plane(float x_, float y_, float z_, float d_) {
	plane.Set(x_, y_, z_, d_);
}

Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
	//Finding Coplanar Vectors using Coplanar points on a plane
	Vector3 e1 = v1 - v0;
	Vector3 e2 = v2 - v1;
	Vector3 N = e1.Cross(e2);
	float D = -(N.Dot(v0));
	//L = <Nx, Ny, Nz, D>
	plane.Set(N.x, N.y, N.z, D);
}

//Getting the position where the ray intersects with the plane
Vector3 Plane::IntersectionPoint(Ray ray) {
	//Getting Normal from plane
	Vector3 N(plane);
	Vector3 position;

	//if N . V != 0 & N . S + D != 0 then insersection occurs
	if (N.Dot(ray.direction) != 0 && !(N.Dot(ray.start) + plane.w == 0)) {
		float t = -((plane.w + N.Dot(ray.start)) / N.Dot(ray.direction));
		position = ray.currentPosition(t);
	}
	//if N . V = 0 & N . S + D == 0 then ray lies on plane
	else if (N.Dot(ray.direction) == 0 && (N.Dot(ray.start) + plane.w == 0)) {
		std::cout << "Ray lies on plane; therefore, no intersection..." << std::endl;
	}
	//Line doesnt intersect if above condition arent true.
	else {
		std::cout << "Ray does not intersect plane..." << std::endl;
	}

	return position;
}