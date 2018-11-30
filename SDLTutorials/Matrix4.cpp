#include "Matrix4.h"
#include <iostream>
#include <cmath>

//---------------------------------------- Matrix4 Class -------------------------------------------//

//Constructors
Matrix4::Matrix4()
{
	SetIdentity();
}

//Sets All elements to value s
Matrix4::Matrix4(float s) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = s;
		}
	}
}

//Sets Elements per column
Matrix4::Matrix4(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4, 
	float z1, float z2, float z3, float z4, float w1, float w2, float w3, float w4) {
	m[0][0] = x1; m[1][0] = x2; m[2][0] = x3; m[3][0] = x4;
	m[0][1] = y1; m[1][1] = y2; m[2][1] = y3; m[3][1] = y4;
	m[0][2] = z1; m[1][2] = z2; m[2][2] = z3; m[3][2] = z4;
	m[0][3] = w1; m[1][3] = w2; m[2][3] = w3; m[3][3] = w4;
}

//Copy Constructor
Matrix4::Matrix4(const Matrix4& mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = mat(i, j);
		}
	}
}

//Sets all components to 0
void Matrix4::SetNull() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][i] = 0;
		}
	}
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

//Inverts Matrix Using Lower Upper Decomposition
void Matrix4::Invert()const {

	//Divide Column 1 by m[0][0]
	for (int i = 1; i < 4; i++) {
		m[0][i] /= m[0][0];
	}

	for (int i = 1; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < i; k++) 
				sum += m[j][k] * m[k][i];
			m[j][i] -= sum;
		}
		if (i < 3) {
			for (int j = i + 1; j < 4; j++) {
				float sum = 0.0f;
				for (int k = 0; k < i; k++)
					sum += m[i][k] * m[k][j];
				m[i][j] = (m[i][j] - sum) / m[i][i];
			}
		}
	}

	//Inverting Lower Triangle Matrix
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			float sum = 1;
			if (i != j) {
				sum = 0.0f;
				for (int k = i; k < j; k++)
					sum -= m[j][k] * m[k][i];
			}
			m[j][i] = sum / m[j][j];
		}
	}

	//Inverting Upper triangle Matrix
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {
				float sum = 0;
				for (int k = i; k < j; k++) {
					if (i == k)
						sum += m[k][j];
					else
						sum += m[k][j] * m[i][k];
				}
				m[i][j] = -sum;
			}
		}
	}
	
	//Inverting Remaining Matrix elements
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			int index;

			if (i > j)
				index = i;
			else
				index = j;

			for (int k = index; k < 4; k++) {
				if (j == k) {
					sum += m[k][i];
				}
				else {
					sum += m[j][k] * m[k][i];
				}
			}

			m[j][i] = sum;
		}
	}
}

//Prints matrix to console
void Matrix4::Print() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//Multiplies By other Matrix
Matrix4 Matrix4::operator * (const Matrix4& otherMat) const {
	Matrix4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result(i, j) = m[i][0] * otherMat(0, j);
			result(i, j) += m[i][1] * otherMat(1, j);
			result(i, j) += m[i][2] * otherMat(2, j);
			result(i, j) += m[i][3] * otherMat(3, j);
		}
	}
	return result;
}

//Multiplies By Vector4
Vector3 Matrix4::operator * (const Vector4& otherV) const {
	Matrix4 result = *this * MatrixMath::Translate(otherV.x, otherV.y, otherV.z);
	Vector3 v(result(0, 3), result(1, 3), result(2, 3));
	return v;
}

//Multiplies By Vector3
Vector3 Matrix4::operator*(const Vector3& otherV) const {
	Matrix4 result = *this * MatrixMath::Translate(otherV);
	Vector3 v(result(0, 3), result(1, 3), result(2, 3));
	return v;
}

//-------------------------------------- Matrix 3 ------------------------------------------

//Constructors
Matrix4::Matrix4()
{
	SetIdentity();
}

//Sets All elements to value s
Matrix4::Matrix4(float s) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = s;
		}
	}
}

//Sets Elements per column
Matrix4::Matrix4(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4,
	float z1, float z2, float z3, float z4, float w1, float w2, float w3, float w4) {
	m[0][0] = x1; m[1][0] = x2; m[2][0] = x3; m[3][0] = x4;
	m[0][1] = y1; m[1][1] = y2; m[2][1] = y3; m[3][1] = y4;
	m[0][2] = z1; m[1][2] = z2; m[2][2] = z3; m[3][2] = z4;
	m[0][3] = w1; m[1][3] = w2; m[2][3] = w3; m[3][3] = w4;
}

//Copy Constructor
Matrix4::Matrix4(const Matrix4& mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = mat(i, j);
		}
	}
}

//Sets all components to 0
void Matrix4::SetNull() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][i] = 0;
		}
	}
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

//Inverts Matrix Using Lower Upper Decomposition
void Matrix4::Invert()const {

	//Divide Column 1 by m[0][0]
	for (int i = 1; i < 4; i++) {
		m[0][i] /= m[0][0];
	}

	for (int i = 1; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < i; k++)
				sum += m[j][k] * m[k][i];
			m[j][i] -= sum;
		}
		if (i < 3) {
			for (int j = i + 1; j < 4; j++) {
				float sum = 0.0f;
				for (int k = 0; k < i; k++)
					sum += m[i][k] * m[k][j];
				m[i][j] = (m[i][j] - sum) / m[i][i];
			}
		}
	}

	//Inverting Lower Triangle Matrix
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			float sum = 1;
			if (i != j) {
				sum = 0.0f;
				for (int k = i; k < j; k++)
					sum -= m[j][k] * m[k][i];
			}
			m[j][i] = sum / m[j][j];
		}
	}

	//Inverting Upper triangle Matrix
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 4; j++) {
			if (i != j) {
				float sum = 0;
				for (int k = i; k < j; k++) {
					if (i == k)
						sum += m[k][j];
					else
						sum += m[k][j] * m[i][k];
				}
				m[i][j] = -sum;
			}
		}
	}

	//Inverting Remaining Matrix elements
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			int index;

			if (i > j)
				index = i;
			else
				index = j;

			for (int k = index; k < 4; k++) {
				if (j == k) {
					sum += m[k][i];
				}
				else {
					sum += m[j][k] * m[k][i];
				}
			}

			m[j][i] = sum;
		}
	}
}

//Prints matrix to console
void Matrix4::Print() const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//Multiplies By other Matrix
Matrix4 Matrix4::operator * (const Matrix4& otherMat) const {
	Matrix4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result(i, j) = m[i][0] * otherMat(0, j);
			result(i, j) += m[i][1] * otherMat(1, j);
			result(i, j) += m[i][2] * otherMat(2, j);
			result(i, j) += m[i][3] * otherMat(3, j);
		}
	}
	return result;
}

//Multiplies By Vector4
Vector3 Matrix4::operator * (const Vector4& otherV) const {
	Matrix4 result = *this * MatrixMath::Translate(otherV.x, otherV.y, otherV.z);
	Vector3 v(result(0, 3), result(1, 3), result(2, 3));
	return v;
}

//Multiplies By Vector3
Vector3 Matrix4::operator*(const Vector3& otherV) const {
	Matrix4 result = *this * MatrixMath::Translate(otherV);
	Vector3 v(result(0, 3), result(1, 3), result(2, 3));
	return v;
}

//-------------------------------------------- Matrix Math Class -------------------------------------------//

//Creates & Returns a Scale Matrix via 3 scalar components
Matrix4 MatrixMath::Scale(float x, float y, float z){
	Matrix4 m;
	m.Scale(x, y, z);
	return m;
}

//Creates & Returns a Scale Matrix via vector
Matrix4 MatrixMath::Scale(const Vector3& scale) {
	Matrix4 m;
	m.Scale(scale);
	return m;
}

//Creates & Returns a Translate Matrix via 3 scalar components
Matrix4 MatrixMath::Translate(float x, float y, float z) {
	Matrix4 m;
	m.Translate(x, y, z);
	return m;
}

//Creates & Returns a Translate Matrix via Vector Components
Matrix4 MatrixMath::Translate(const Vector3& translation) {
	Matrix4 m;
	m.Translate(translation);
	return m;
}

//Creates & returns a RotationX Matrix
Matrix4 MatrixMath::RotateX(float angle) {
	Matrix4 m;
	m.RotateX(angle);
	return m;
}

//Creates & Returns a RotationY Matrix
Matrix4 MatrixMath::RotateY(float angle) {
	Matrix4 m;
	m.RotateY(angle);
	return m;
}

//Creates & Returns a RotationZ Matrix 
Matrix4 MatrixMath::RotateZ(float angle) {
	Matrix4 m;
	m.RotateZ(angle);
	return m;
}
