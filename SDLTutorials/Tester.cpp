#include "Matrix4.h"
#include "Vector.h"
#include "Quaternion.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//Testing Vector3 Roation
	Quaternion q1(Vector3(0, 0, 1), 90);
	Vector3 result = q1.Rotate(Vector3(1, 0, 0));
	std::cout << "Testing Vector3 Roation" << std::endl;
	std::cout << result.ToString() << std::endl << std::endl;

	//Testing Quaternion Multiplication
	Quaternion q2(1, 2, 2, 3);
	Quaternion q3(2, 1, 2, 5);
	Quaternion q_result = q2 * q3;
	std::cout << "Testing Quaternion Multiplication" << std::endl;
	std::cout << q_result.quaternion.ToString() << std::endl << std::endl;

	//Testing Slerp Interpolation
	Quaternion slerpResult = q2.Slerp(q3, 0.5f);
	std::cout << "Testing Quaternion Slerp" << std::endl;
	std::cout << slerpResult.quaternion.ToString() << std::endl << std::endl;

	getchar();

	return 0;
}

