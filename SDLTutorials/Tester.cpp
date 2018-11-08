#include "Geometry.h"
#include "Matrix4.h"
#include "Vector.h"
#include <iostream>
#include <iomanip>


int main(int argc, char* argv[])
{
	Matrix4 mat;
	mat(0, 3) = 4;
	//mat.Translate(vec);
	//mat.Scale(2, 3, 4);
	//mat.Transpose();
	//mat.RotateX(60);
	//mat.RotateY(60);
	//mat.RotateZ(60);
	mat.Print();
	std::cout << mat(0, 3) << std::endl;
	getchar();

	return 0;
}

