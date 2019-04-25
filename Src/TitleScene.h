/**
* @file TitleGameScene.h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "SelectManager.h"
#include "Audio.h"
#include "Sprite.h"

/**
* �^�C�g�����.
*/
class TitleScene : public Scene
{
public:
  TitleScene() = default;
  virtual ~TitleScene() = default;

  virtual bool Initialize() override;
  virtual void ProcessInput() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Finalize() override;

  enum class STATE {
	  e_STATE_STAY,			//�v���[���p,���͂܂ő҂�
	  e_STATE_BEGIN_0,		//project by takahashi�̂Ƃ���.
	  e_STATE_BEGIN_1,		//�^�C�g���̃I�[�v�j���O
	  e_STATE_BEGIN_2,		//��ɓ���
	  e_STATE_SELECT,		//���͉��
	  e_STATE_MANUAL,		//�}�j���A����\��
	  e_STATE_CREDIT,		//�N���W�b�g��\��.
	  e_STATE_EXIT,			//�I�����m�肵��.
	  e_STATE_TRANSITION,   //�J��

  };
  void SetState(STATE s) {state =s ; }
private:
	const float beginStateTime=3.0f;
	float beginStageTimer;

	STATE state;
  MeshList& meshList=MeshList::Instance();

  Texture::Image2D texBackGround;
  Texture::Image2D texLogo;
  Texture::Image2D texPushAnyKey;

  Shader::Program progSimple;

  //Selectclass�̃e�X�g
  Select::Manager select;
  Select::Unit choice;
  Select::Unit choice2;
  Select::Unit credit;
  Select::Unit manual;


  //�^�C�g���Ƃ����S���X�v���C�g�ŕ\���ɕύX����.
  SpriteRenderer& renderer = SpriteRenderer::Instance();
  Sprite2D sprLogo;
  glm::vec4 logoColor;		//color for sprLogo;
  Sprite2D sprBG;
  Sprite2D sprBGsub;
  Sprite2D sprManual;		//
  Sprite2D sprCredit;
  glm::vec4 whiteColor;		//�t�F�[�h�A�E�g�Ɏg��.
  Sprite2D sprWhite;		//���I�I
  Sprite2D sprTakahashi;	//�X�v������,
  glm::vec4 takahashiColor; 

  //audio�̃e�X�g.
  Audio::EngineRef audio = Audio::Engine::Instance();
  Audio::SoundPtr BuckBGM;


  //this val is scroll speed,
  float scrollSpeed;
  int scrollCount;

  //Begin_0�̃^�C�}�[
  float state_0_Timer;
  const float state_0_Time = 6.0f;
  const float state_0_FadeIn_Start = 1.0f;
  const float state_0_FadeOut_Start = 4.0f;

  //Exit�̃^�C�}�[
  float state_Exit_Timer;
  const float state_Exit_Time = 3.0f;

  //Transition�̃^�C�}�[
  float state_Transition_Timer;
  const float state_Transition_Time = 2.0f;

  static bool beginTitle;	//�͂��߂̈����L������.
};

#endif // TITLESCENE_H_INCLUDED