#include "Debug.h"
#include <iostream>

namespace Debug {

	/* 
	* �v�f���ʂɕ\��
	*/
	void print(glm::vec3 vec) {
		std::cout << "Debug::print. glm::vec3�^�̗v�f��\������" << std::endl;
		std::cout << "vec3��x�v�f:" << vec.x << std::endl;
		std::cout << "vec3��y�v�f:" << vec.y << std::endl;
		std::cout << "vec3��z�v�f:" << vec.z << std::endl;
	}
	/*
	* ��ɂȂɂ��t�������������͂������,
	*/
	void print(std::string string, glm::vec3 vec) {
		std::cout << string << std::endl;
		print(vec);
	}


}