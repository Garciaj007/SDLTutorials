#include "GameManager.h"
#include <memory>
#include <iostream>

/*
int main(int argc, char* argv[])
{	
	std::unique_ptr<GameManager> ptr = std::make_unique<GameManager>();
	bool status = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	}
	else if (status == false) {
		/// You should have learned about stderr (std::cerr) in Operating Systems 
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}

	return 0;
}
*/