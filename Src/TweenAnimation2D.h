// @file TweenAnimation2D

#ifndef TWEENANIMATION2D_H_INCLUDED
#define TWEENANIMATION2D_H_INCLUDED


#include <glm/gtc/matrix_transform.hpp>
namespace Tweener {
	/*
	* 2Dスプライトに添付する感じで作れればいいなぁ的なのりで作ってる
	*
	* とりあえず初めは.動く時間と距離を持たせることにする
	*
	*/
	class TweenAnimation {
	public:
		TweenAnimation();

		virtual bool GetActive() { return active; }
		virtual void Update()=0;//更新処理.

		
	protected:
		bool active=false;		//アクティブなら動かす


	};


	class Linear :public TweenAnimation {
	public:
		Linear(glm::vec3& pos,const glm::vec2& dis, float speed);
		void Update()override;

	private:
		Linear() = default;

		const float time;		//移動にかかる時間.
		float elapsedTime;		//経過時間.
		glm::vec2 speed;		//1秒あたりの移動距離
		glm::vec3& sprpos;		//アニメーション対象となるスプライトのポジション.
	};


}

#endif // !TWEENANIMATION2D_H_INCLUDED
