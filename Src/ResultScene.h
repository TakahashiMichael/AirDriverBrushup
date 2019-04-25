// file ResultScene.h 
// mainscene����̃V�[���ڍs

#ifndef RESULTSCENE_H_INCLUDED
#define RESULTSCENE_H_INCLUDED

#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "Audio.h"
#include "Sprite.h"
/*
* �Q�[���̌��ʉ��
*
*
*
*/
class ResultScene :public Scene {
public:
	ResultScene() = default;
	virtual ~ResultScene() = default;

	virtual bool Initialize()override;
	virtual void ProcessInput()override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;

	static void setResultPoint(int point) { resultPoint = point; }//
	enum class STATE{
		e_STATE_BEGIN_0,
		e_STATE_BEGIN_1,
		e_STATE_DSIPLAYPOINTS,			//�_���̕\��.
		e_STATE_TRANSITION,				//�J��,�z���C�g�A�E�g.
	};

private:

	STATE state;					//�X�e�[�g�Ǘ�
	MeshList& meshList=MeshList::Instance();

	Shader::Program progSimple;

	Audio::EngineRef audio = Audio::Engine::Instance();
	Audio::SoundPtr bgm;
	Audio::SoundPtr SE_CortSound;
	Audio::SoundPtr SE_ResultBegin;


	//�w�i�Ɏg��
	Sprite2D sprFrame;
	//���C���Ɠ����Ńz���C�g�A�E�g�Ɏg��
	Sprite2D sprWhite;
	glm::vec4 whiteOut;	//���̐F
	//�_�����^��ł���J�[�g
	Sprite2D sprCart;
	glm::vec3 cartPos;
	
	//���C������_�����󂯎��
	static int resultPoint;
	glm::vec3 pointPos;		//�_���t�H���g�̃|�W�V����
	const float pointStayPosX = 100.0f;

	glm::vec3 fontPos;		//���U���g�̈ʒu.
	const float fontScrollSpeed = 1000.0;

	//begin0�̕ϐ�
	float state_Begin_0_Timer;
	const float state_Begin_0_Time = 2.0f;
	//begin1�̕ϐ�
	float state_Begin_1_Timer;
	const float state_Begin_1_Time = 3.0f;

	//transition�̕ϐ�
	float state_Transition_Timer;
	const float state_Transition_time = 3.0f;
};


#endif // !RESULTSCENE_H_INCLUDED
