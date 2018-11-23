#include "Matrix4.h"
#include "Vector.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//Standard Matrix4 Multiplication
	std::cout << "//Standard Matrix4 Multiplication//" << std::endl << std::endl;
	Matrix4 mat1(1, 0, 1, 0, 0, 4, 2, 0, 2, 1, 1, 2, 1, 0, 0, 3);
	mat1.Print();

	Matrix4 mat2(1, 0, 1, 0, 0, 4, 2, 0, 2, 1, 1, 2, 1, 0, 0, 3);
	mat2.Print();

	Matrix4 result = mat1 * mat2;
	result.Print();

	//Matrix4 * Vector4 Multiplication
	std::cout << "//Matrix4 * Vector4 Multiplication//" << std::endl << std::endl;
	Vector3 v_Result = MatrixMath::Translate(1, 2, 3) * Vector4(1);
	std::cout << v_Result.ToString() << std::endl << std::endl;

	//Matrix Inversion
	std::cout << "//Matrix Inversion//" << std::endl << std::endl;
	Matrix4 mat3(1,0,1,0,0,4,2,0,2,1,1,2,1,0,0,3);
	mat3.Print();
	mat3.Invert();
	mat3.Print();

	getchar();

	return 0;
}

