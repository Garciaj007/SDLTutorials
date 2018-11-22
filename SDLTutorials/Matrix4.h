#ifndef MATRIX4_H
#define MATRIX4_H
#include "Vector.h"

#define PI 3.1456
#define DEGREESTORAD(x) (x * PI/180)

class Matrix4
{
private:
	//Members
	mutable float m[4][4] { 0 }; ///Matrix is a 2d matrix

public:
	//Constructor
	Matrix4();
	Matrix4(Matrix4& otherM);

	//Member Methods
	void SetNull() const;
	void SetIdentity() const;
	void Transpose() const;
	void Scale(float x, float y, float z) const;
	void Scale(Vector3 scale) const;
	void Translate(float x, float y, float z) const;
	void Translate(Vector3 translation) const;
	void RotateX(float angleInDegrees) const;
	void RotateY(float angleInDegrees) const;
	void RotateZ(float angleInDegrees) const;
	void Print() const;

	//Operator Overloads

	Matrix4 operator * (const Matrix4& otherMat) const;
	Vector3 operator * (const Vector4& otherV) const;

	//Get Matrix component
	inline float operator () (int r, int c)const {
		return m[r][c];
	}
	//Sets Matrix component
	inline float& operator() (int r, int c) {
		return m[r][c];
	}
};


#endif

