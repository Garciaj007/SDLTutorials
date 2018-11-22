#include "Matrix4.h"
#include "Vector.h"
#include <iostream>


int main(int argc, char* argv[])
{
	//Matrix Stack var
	Matrix4 mat;
	Vector3 v(1, 2, 3);

	//Setting value manually
	mat.SetNull();
	mat(0, 3) = 4;
	mat.Print();

	std::cout << mat(0, 3) << std::endl; //getting that value

	//Setting Translation Matrix by vector
	mat.SetNull();
	mat.Translate(v);
	mat.Print();

	//Set Scaling Matrix
	mat.SetNull();
	mat.Scale(2, 3, 4);
	mat.Print();

	//Transposing Matrix
	mat.SetNull();
	mat.Transpose();
	mat.Print();

	//Rotating Matrix on X Axis by 60
	mat.SetNull();
	mat.RotateX(60);
	mat.Print();

	//Rotating Matrix on Y Axis by 80
	mat.SetNull();
	mat.RotateY(80);
	mat.Print();

	//Rotating Matrix on Z Axis by 40
	mat.SetNull();
	mat.RotateZ(40);
	mat.Print();

	getchar();

	return 0;
}

