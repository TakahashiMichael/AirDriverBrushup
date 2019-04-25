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
* タイトル画面.
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
	  e_STATE_STAY,			//プレゼン用,入力まで待つ
	  e_STATE_BEGIN_0,		//project by takahashiのところ.
	  e_STATE_BEGIN_1,		//タイトルのオープニング
	  e_STATE_BEGIN_2,		//上に同じ
	  e_STATE_SELECT,		//入力画面
	  e_STATE_MANUAL,		//マニュアルを表示
	  e_STATE_CREDIT,		//クレジットを表示.
	  e_STATE_EXIT,			//終了が確定した.
	  e_STATE_TRANSITION,   //遷移

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

  //Selectclassのテスト
  Select::Manager select;
  Select::Unit choice;
  Select::Unit choice2;
  Select::Unit credit;
  Select::Unit manual;


  //タイトルとかロゴをスプライトで表示に変更する.
  SpriteRenderer& renderer = SpriteRenderer::Instance();
  Sprite2D sprLogo;
  glm::vec4 logoColor;		//color for sprLogo;
  Sprite2D sprBG;
  Sprite2D sprBGsub;
  Sprite2D sprManual;		//
  Sprite2D sprCredit;
  glm::vec4 whiteColor;		//フェードアウトに使う.
  Sprite2D sprWhite;		//白！！
  Sprite2D sprTakahashi;	//スプラ高橋,
  glm::vec4 takahashiColor; 

  //audioのテスト.
  Audio::EngineRef audio = Audio::Engine::Instance();
  Audio::SoundPtr BuckBGM;


  //this val is scroll speed,
  float scrollSpeed;
  int scrollCount;

  //Begin_0のタイマー
  float state_0_Timer;
  const float state_0_Time = 6.0f;
  const float state_0_FadeIn_Start = 1.0f;
  const float state_0_FadeOut_Start = 4.0f;

  //Exitのタイマー
  float state_Exit_Timer;
  const float state_Exit_Time = 3.0f;

  //Transitionのタイマー
  float state_Transition_Timer;
  const float state_Transition_Time = 2.0f;

  static bool beginTitle;	//はじめの一回を記憶する.
};

#endif // TITLESCENE_H_INCLUDED