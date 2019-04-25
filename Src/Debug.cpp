#include "Debug.h"
#include <iostream>

namespace Debug {

	/* 
	* —v‘f‚ðŒÂ•Ê‚É•\Ž¦
	*/
	void print(glm::vec3 vec) {
		std::cout << "Debug::print. glm::vec3Œ^‚Ì—v‘f‚ð•\Ž¦‚·‚é" << std::endl;
		std::cout << "vec3‚Ìx—v‘f:" << vec.x << std::endl;
		std::cout << "vec3‚Ìy—v‘f:" << vec.y << std::endl;
		std::cout << "vec3‚Ìz—v‘f:" << vec.z << std::endl;
	}
	/*
	* ã‚É‚È‚É‚©•t‚¯‰Á‚¦‚½‚¢•¶Í‚ª‚ ‚ê‚Î,
	*/
	void print(std::string string, glm::vec3 vec) {
		std::cout << string << std::endl;
		print(vec);
	}


}