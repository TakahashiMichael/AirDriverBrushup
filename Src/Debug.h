//@ file Debug.h

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <glm/gtc/matrix_transform.hpp>
#include <string>
/*
* あまりにもglm::vec3型の位置要素を一個ずつcoutする機械が多すぎたので対策のため作成
* 
* なんかcpp一個使うのももったいない気もする...2/11
*/

namespace Debug {
	
	void print(glm::vec3);							//要素を個別に表示
	void print(std::string,glm::vec3);				//なにか付け加えたい文章があれば,
}//namespace Debug


#endif // !DEBUG_H_INCLUDED
