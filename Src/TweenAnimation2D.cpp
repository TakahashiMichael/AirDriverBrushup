

#include "TweenAnimation2D.h"
#include "GLFWEW.h"
#include <iostream>

/**
* 先生に質問したいこと
*
*
*/

namespace Tweener {
	
	TweenAnimation::TweenAnimation() {

		active = false;		//アクティブなら動かす

	}





	// @class Linear <等速直線運動アニ

	/*
	* constructor
	*
	* @param dis		移動する距離.
	* @param time		移動にかける時間.
	*
	* あくまで保持するのは時間と1秒に移動する距離である
	*/
	Linear::Linear(glm::vec3& pos,const glm::vec2& dis ,float time):time(time),sprpos(pos),elapsedTime(0.0f){
		this->speed = dis / time;	//あくまでspeedには一秒あたりで進む距離を計算して格納.
		active = true;
	}

	/*
	* Update関数.
	*
	* 
	*
	*
	*/
	void Linear::Update() {

		if (elapsedTime <= time) {
			//Acquire Deltatime(デルタタイムの取得)
			GLFWEW::Window& window = GLFWEW::Window::Instance();
			float deltaTime = window.DeltaTime();
			sprpos += glm::vec3(speed.x, speed.y,0) * deltaTime;
			elapsedTime += deltaTime;
		}
		else {
			//移動を終えた時にアクティブをゼロに.
			active = false;
		}
	}
}