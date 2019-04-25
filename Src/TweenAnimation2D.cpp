

#include "TweenAnimation2D.h"
#include "GLFWEW.h"
#include <iostream>

/**
* �搶�Ɏ��₵��������
*
*
*/

namespace Tweener {
	
	TweenAnimation::TweenAnimation() {

		active = false;		//�A�N�e�B�u�Ȃ瓮����

	}





	// @class Linear <���������^���A�j

	/*
	* constructor
	*
	* @param dis		�ړ����鋗��.
	* @param time		�ړ��ɂ����鎞��.
	*
	* �����܂ŕێ�����͎̂��Ԃ�1�b�Ɉړ����鋗���ł���
	*/
	Linear::Linear(glm::vec3& pos,const glm::vec2& dis ,float time):time(time),sprpos(pos),elapsedTime(0.0f){
		this->speed = dis / time;	//�����܂�speed�ɂ͈�b������Ői�ދ������v�Z���Ċi�[.
		active = true;
	}

	/*
	* Update�֐�.
	*
	* 
	*
	*
	*/
	void Linear::Update() {

		if (elapsedTime <= time) {
			//Acquire Deltatime(�f���^�^�C���̎擾)
			GLFWEW::Window& window = GLFWEW::Window::Instance();
			float deltaTime = window.DeltaTime();
			sprpos += glm::vec3(speed.x, speed.y,0) * deltaTime;
			elapsedTime += deltaTime;
		}
		else {
			//�ړ����I�������ɃA�N�e�B�u���[����.
			active = false;
		}
	}
}