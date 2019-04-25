// file ResultScene.h 
// mainsceneからのシーン移行

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
* ゲームの結果画面
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
		e_STATE_DSIPLAYPOINTS,			//点数の表示.
		e_STATE_TRANSITION,				//遷移,ホワイトアウト.
	};

private:

	STATE state;					//ステート管理
	MeshList& meshList=MeshList::Instance();

	Shader::Program progSimple;

	Audio::EngineRef audio = Audio::Engine::Instance();
	Audio::SoundPtr bgm;
	Audio::SoundPtr SE_CortSound;
	Audio::SoundPtr SE_ResultBegin;


	//背景に使う
	Sprite2D sprFrame;
	//メインと同じでホワイトアウトに使う
	Sprite2D sprWhite;
	glm::vec4 whiteOut;	//その色
	//点数を運んでくるカート
	Sprite2D sprCart;
	glm::vec3 cartPos;
	
	//メインから点数を受け取る
	static int resultPoint;
	glm::vec3 pointPos;		//点数フォントのポジション
	const float pointStayPosX = 100.0f;

	glm::vec3 fontPos;		//リザルトの位置.
	const float fontScrollSpeed = 1000.0;

	//begin0の変数
	float state_Begin_0_Timer;
	const float state_Begin_0_Time = 2.0f;
	//begin1の変数
	float state_Begin_1_Timer;
	const float state_Begin_1_Time = 3.0f;

	//transitionの変数
	float state_Transition_Timer;
	const float state_Transition_time = 3.0f;
};


#endif // !RESULTSCENE_H_INCLUDED
