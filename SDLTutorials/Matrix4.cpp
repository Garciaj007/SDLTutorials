#include "Matrix4.h"
#include <iostream>
#include <cmath>

//Constructor
Matrix4::Matrix4()
{
	SetIdentity();
}

//Sets Matrix to identity Matrix
void Matrix4::SetIdentity() const {
	for (int i = 0; i < 4; i++) {
		m[i][i] = 1;
	}
}

//Creates a Scaling matrix using x, y, z components
void Matrix4::Scale(float x, float y, float z) const {
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}

//Creates a Scaling Matrix with a Vector3
void Matrix4::Scale(Vector3 scale) const {
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
}

//Transposes Matrix AKA Inverts matrix from columns to rows and vice-versa
void Matrix4::Transpose() const {
	float temp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[j][i] = m[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = temp[i][j];
		}
	}
}

//Creates a translation matrix using xyz components
void Matrix4::Translate(float x, float y, float z) const {
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

//Creates a translation matrix using a vector
void Matrix4::Translate(Vector3 translation) const {
	m[0][3] = translation.x;
	m[1][3] = translation.y;
	m[2][3] = translation.z;
}

//Creates a rotation matrix for X angle
void Matrix4::RotateX(float angleInDegrees) const {
	float angle = DEGREESTORAD(angleInDegrees);
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
}

//Creates a rotation matrix for Y angle
void Matrix4::RotateY(float angleInDegrees) const {
	float angle = DEGREESTORAD(angleInDegrees);
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

//Creates a rotation matrix for Z angle
void Matrix4::RotateZ(float angleInDegrees) const {
	float angle = DEGREESTORAD(angleInDegrees);
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
}

//Prints matrix to console
void Matrix4::Print() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
