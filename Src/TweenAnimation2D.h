// @file TweenAnimation2D

#ifndef TWEENANIMATION2D_H_INCLUDED
#define TWEENANIMATION2D_H_INCLUDED


#include <glm/gtc/matrix_transform.hpp>
namespace Tweener {
	/*
	* 2D�X�v���C�g�ɓY�t���銴���ō���΂����Ȃ��I�Ȃ̂�ō���Ă�
	*
	* �Ƃ肠�������߂�.�������ԂƋ������������邱�Ƃɂ���
	*
	*/
	class TweenAnimation {
	public:
		TweenAnimation();

		virtual bool GetActive() { return active; }
		virtual void Update()=0;//�X�V����.

		
	protected:
		bool active=false;		//�A�N�e�B�u�Ȃ瓮����


	};


	class Linear :public TweenAnimation {
	public:
		Linear(glm::vec3& pos,const glm::vec2& dis, float speed);
		void Update()override;

	private:
		Linear() = default;

		const float time;		//�ړ��ɂ����鎞��.
		float elapsedTime;		//�o�ߎ���.
		glm::vec2 speed;		//1�b������̈ړ�����
		glm::vec3& sprpos;		//�A�j���[�V�����ΏۂƂȂ�X�v���C�g�̃|�W�V����.
	};


}

#endif // !TWEENANIMATION2D_H_INCLUDED
