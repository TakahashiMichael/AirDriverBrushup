//@ file Debug.h

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <glm/gtc/matrix_transform.hpp>
#include <string>
/*
* ���܂�ɂ�glm::vec3�^�̈ʒu�v�f�������cout����@�B�����������̂ő΍�̂��ߍ쐬
* 
* �Ȃ�cpp��g���̂����������Ȃ��C������...2/11
*/

namespace Debug {
	
	void print(glm::vec3);							//�v�f���ʂɕ\��
	void print(std::string,glm::vec3);				//�Ȃɂ��t�������������͂������,
}//namespace Debug


#endif // !DEBUG_H_INCLUDED
