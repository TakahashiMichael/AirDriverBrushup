#include "Debug.h"
#include <iostream>

namespace Debug {

	/* 
	* 要素を個別に表示
	*/
	void print(glm::vec3 vec) {
		std::cout << "Debug::print. glm::vec3型の要素を表示する" << std::endl;
		std::cout << "vec3のx要素:" << vec.x << std::endl;
		std::cout << "vec3のy要素:" << vec.y << std::endl;
		std::cout << "vec3のz要素:" << vec.z << std::endl;
	}
	/*
	* 上になにか付け加えたい文章があれば,
	*/
	void print(std::string string, glm::vec3 vec) {
		std::cout << string << std::endl;
		print(vec);
	}


}