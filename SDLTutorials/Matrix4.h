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
	Matrix4(const Matrix4& otherM);
	Matrix4(float s);
	Matrix4(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4, float z1, float z2, float z3, float z4, float w1, float w2, float w3, float w4);

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
	void Invert() const;
	void Print() const;
	

	//Operator Overloads
	Matrix4 operator * (const Matrix4& otherMat) const;
	Vector3 operator * (const Vector4& otherV) const;
	Vector3 operator * (const Vector3& otherV) const;
	//Get Matrix component

	inline float operator () (int r, int c)const {
		return m[r][c];
	}
	//Sets Matrix component
	inline float& operator() (int r, int c) {
		return m[r][c];
	}
};

//Static Matrix4 Math Class
class MatrixMath {
public:
	Matrix4 static Scale(float x, float y, float z);
	Matrix4 static Scale(const Vector3& scale);
	Matrix4 static Translate(float x, float y, float z);
	Matrix4 static Translate(const Vector3& translation);
	Matrix4 static RotateX(float angleInDegrees);
	Matrix4 static RotateY(float angleInDegrees);
	Matrix4 static RotateZ(float angleInDegrees);
};


#endif

