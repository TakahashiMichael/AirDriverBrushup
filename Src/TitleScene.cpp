/**
* @file TitleScene.h
*/
#include "TitleScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FileNameData.h"



/*
* Selectに関数ポインタを設定する都合上.
* classに属さないTitleScene型のポインタをグローバルに持たせたが
*
* いまいち納得できないのでまた機会があったら改善したいのが本音 2/10
*/
struct CopyTitle:public TitleScene
{
	void NextStage();
};
CopyTitle* copyTitle=nullptr;		//とりあえず

/*
* 関数
* @func NextStage 
* @func stateCregit
*
*
*/
void f_NextStage();
void f_StateCredit();
void f_StateManual();


bool TitleScene::beginTitle = true;

/**
* 初期化.
*/
bool TitleScene::Initialize()
{
  std::vector<std::string> modelList;
  modelList.push_back(FILENAME_OBJ_PLANE);
  if (!meshList.Allocate(modelList)) {
    return false;
  }

  progSimple.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_SIMPLE, FILENAME_SHADER_FRAG_SIMPLE));

  texLogo.Reset(Texture::LoadImage2D(FILENAME_TGA_TITLELOGO));
  texBackGround.Reset(Texture::LoadImage2D(FILENAME_TGA_TITLEBACK));

  std::vector<std::string> string;
  string.push_back("GameStart");
  string.push_back("Manual");
  string.push_back("Credit");
  choice.SetChoices(string);
  choice.SetNextUnit("GameStart", &choice2);
  std::vector<std::string> string2;
  string2.push_back("GameStart");
  string2.push_back("AB");
  choice2.SetChoices(string2);

  choice2.SetFuncPtr(f_NextStage);
  select.SetEntryPoint(&choice);
  choice.SetNextUnit("Credit",&credit);
  credit.SetFuncPtr(f_StateCredit);
  choice.SetNextUnit("Manual", &manual);
  manual.SetFuncPtr(f_StateManual);

  //CopyTitleのテスト,ダウンキャストしてポインタを登録
  copyTitle = (CopyTitle*)this;

  //
  BuckBGM= audio.Prepare(FILENAME_WAV_TITLESCENE);

  //Set to scrollSpeed;
  scrollSpeed = 0.1f;
  scrollCount = 5;

  sprLogo = Sprite2D(FILENAME_TGA_TITLELOGO);
  logoColor = glm::vec4(1,1,1,0);
  sprLogo.SetColor(&logoColor);
  sprBG = Sprite2D(FILENAME_TGA_TITLEBACK,glm::vec3(0,2,0));
  sprBG.SetTweener(glm::vec2(0,-2.0f), scrollSpeed);
  sprBGsub = Sprite2D(FILENAME_TGA_TITLEBACK);
  sprBGsub.SetTweener(glm::vec2(0, -2.0f), scrollSpeed);
  sprManual = Sprite2D(FILENAME_TGA_MANUAL);
  sprCredit = Sprite2D(FILENAME_TGA_CREDIT);
  whiteColor = glm::vec4(1);
  sprWhite = Sprite2D(FILENAME_TGA_WHITE);
  sprWhite.SetColor(&whiteColor);
  sprTakahashi = Sprite2D(FILENAME_TGA_TITLECREDIT);
  takahashiColor = glm::vec4(1,1,1,0);
  sprTakahashi.SetColor(&takahashiColor);
  
  //初回ならbegin_0 違うならbegin_1
  if (beginTitle) {
	  state = STATE::e_STATE_BEGIN_0;
	  beginTitle = false;
  }
  else {
	  state = STATE::e_STATE_BEGIN_1;
	  BuckBGM->Play(Audio::Flag::Flag_Loop);

  }
  beginStageTimer = 0.0f;
  state_0_Timer = 0.0f;
  state_Transition_Timer = 0.0f;
  return true;
}

/**
* 入力の処理.
*/
void TitleScene::ProcessInput()
{
	if (state == STATE::e_STATE_STAY){
		GLFWEW::Window& window = GLFWEW::Window::Instance();
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			state = STATE::e_STATE_BEGIN_0;
		}
	}
	else if (state == STATE::e_STATE_SELECT) {
		select.ProcessInput();
	}
	else if (state == STATE::e_STATE_CREDIT) {
		GLFWEW::Window& window = GLFWEW::Window::Instance();
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_CANCEL) || window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			select.Back();
			state = STATE::e_STATE_SELECT;
		}
	}
	else if (state == STATE::e_STATE_MANUAL) {
		GLFWEW::Window& window = GLFWEW::Window::Instance();
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_CANCEL) || window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			select.Back();
			state = STATE::e_STATE_SELECT;
		}

	}
}

/**
* 状態の更新.
*/
void TitleScene::Update()
{
	//acquire deltatime
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime = window.DeltaTime();

	if (state == STATE::e_STATE_BEGIN_0) {
		if (state_0_Timer >= state_0_Time) {
			state = STATE::e_STATE_BEGIN_1;
			BuckBGM->Play(Audio::Flag::Flag_Loop);

		}
		else if (state_0_Timer >= state_0_FadeIn_Start && state_0_Timer < state_0_FadeOut_Start) {
			if (takahashiColor.a < 1) {
				takahashiColor.a += deltaTime;
				if (takahashiColor.a >= 1) {
					takahashiColor.a = 1;
				}
			}
		}
		else if (state_0_Timer >= state_0_FadeOut_Start) {
			if (takahashiColor.a > 0) {
				takahashiColor.a -= deltaTime;
				if (takahashiColor.a <= 0) {
					takahashiColor.a = 0;
				}
			}
		}

		state_0_Timer += deltaTime;

	}
	else if (state == STATE::e_STATE_BEGIN_1) {

		if (!sprBG.AnimActive()) {
			sprBG.SetPos(glm::vec3(0));
			sprBGsub.SetPos(glm::vec3(0, 2.0f, 0));
			if (scrollCount > 0) {
				scrollSpeed *= 1.5f;
				--scrollCount;
				sprBG.SetTweener(glm::vec2(0, -2.0f), scrollSpeed);
				sprBGsub.SetTweener(glm::vec2(0, -2.0f), scrollSpeed);
			}
			else if (scrollCount == 0) {
				sprLogo.SetTweener(glm::vec2(0,0.5f),2.0f);
				state = STATE::e_STATE_BEGIN_2;
			}
		}

	}
	else if (state == STATE::e_STATE_BEGIN_2) {
		beginStageTimer += deltaTime;
		if (logoColor.a < 1) {
			logoColor.a += deltaTime;
			if (logoColor.a >= 1) {
				logoColor.a = 1;
			}
		}
		if (beginStageTimer >= beginStateTime) {
			state = STATE::e_STATE_SELECT;
			whiteColor.a = 0;
		}

	}
	else if (state == STATE::e_STATE_SELECT) {
		//もし選択画面でexitを押した場合ゲームを終了させる.
		if (select.GetExit()) {
			state = STATE::e_STATE_EXIT;
			whiteColor.a = 0;
		}

	}
	else if (state ==STATE::e_STATE_EXIT) {
		if (state_Exit_Timer >= state_Exit_Time) {
			GLFWEW::Window& window = GLFWEW::Window::Instance();
			window.Exit();
		}
		else {
			if (whiteColor.a < 1) {
				whiteColor.a += deltaTime / 2;
				if (whiteColor.a >= 1) {
					whiteColor.a = 1;
				}
			}
			state_Exit_Timer += deltaTime;
		}
	}
	else if (state==STATE::e_STATE_TRANSITION)
	{
		if (state_Transition_Timer < state_Transition_Time) {
			if (whiteColor.a < 1) {
				whiteColor.a += deltaTime;
				if (whiteColor.a >= 1) {
					whiteColor.a = 1;
				}
			}
			state_Transition_Timer += deltaTime;
		}
		else {
			copyTitle->NextStage();
		}
	}


  // 座標変換行列を作成する.
//  const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
  const glm::mat4x4 matProj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, 500.0f);
  const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  progSimple.SetViewProjectionMatrix(matProj * matView);
  select.Update();
  sprLogo.Update();
  sprBG.Update();
  sprBGsub.Update();
  sprManual.Update();
  sprCredit.Update();
}

/**
* 描画.
*/
void TitleScene::Render()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  meshList.BindVertexArray();
  //progSimple.Use();

  //progSimple.BindTexture(0, texBackGround.Get());
  //progSimple.Draw(meshList[0], glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));



  if (state == STATE::e_STATE_BEGIN_0) {
	  renderer.AddSprite(&sprWhite);
	  renderer.AddSprite(&sprTakahashi);
  }
  else if (state ==STATE::e_STATE_BEGIN_1) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprBGsub);
	  renderer.AddSprite(&sprLogo);
  }
  else if (state ==STATE::e_STATE_BEGIN_2) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprBGsub);
	  renderer.AddSprite(&sprLogo);
  }
  else if (state ==STATE::e_STATE_SELECT) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprBGsub);
	  renderer.AddSprite(&sprLogo);

  }
  else if (state == STATE::e_STATE_CREDIT) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprBGsub);

	  renderer.AddSprite(&sprCredit);
  }
  else if (state == STATE::e_STATE_MANUAL) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprBGsub);

	  renderer.AddSprite(&sprManual);
  }
  else if (state == STATE::e_STATE_EXIT) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprLogo);
	  renderer.AddSprite(&sprWhite);
  }
  else if (state==STATE::e_STATE_TRANSITION) {
	  renderer.AddSprite(&sprBG);
	  renderer.AddSprite(&sprWhite);
  }
  renderer.Draw();
  if (state == STATE::e_STATE_SELECT) {
	  select.Render();
  }
 
}

/**
* 終了.
*/
void TitleScene::Finalize()
{
	//登録されたままだとよろしくないので.
	copyTitle = nullptr;
	BuckBGM->Stop();
}












//=======================================================================
/*
* 
*
*/
void CopyTitle::NextStage()
{
	NextScene("Drive");
}



void f_NextStage() {
	if (copyTitle!=nullptr) {
		copyTitle->SetState(TitleScene::STATE::e_STATE_TRANSITION);
	}
}

void f_StateCredit() {
	if (copyTitle != nullptr) {
		copyTitle->SetState(TitleScene::STATE::e_STATE_CREDIT);
	}
}
void f_StateManual() {
	if (copyTitle != nullptr) {
		copyTitle->SetState(TitleScene::STATE::e_STATE_MANUAL);
	}
}