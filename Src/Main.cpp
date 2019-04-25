
/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "MainGameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include <memory>
#include "Audio.h"
#include "Sprite.h"
#include "Font.h"

/// エントリーポイント.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL AirDriver")) {
    return 1;
  }

  //音声システムの初期化.
  Audio::EngineRef audio = Audio::Engine::Instance();
  if (!audio.Initialize()) {
	  return 1;
  }

  //レンダラーシステムの初期化.
  SpriteRenderer& renderer = SpriteRenderer::Instance();
  if (!renderer.Init()) {
	  return 1;
  }
  //Fontの初期化.
  Font& font = Font::Instance();
  if (!font.Init()) {
	  return 1;
  }
  std::shared_ptr<Scene> pScene(new TitleScene);
  if (!pScene->Initialize()) {
	  return 1;
  }

  // メインループ.
  window.InitTimer();
  while (!window.ShouldClose()) {
    window.Update();

    // シーンを切り替える.
    if (!pScene->NextScene().empty()) {
      glFinish();
      pScene->Finalize();
      if (pScene->NextScene() == "Title") {
        pScene.reset(new TitleScene);
      } else if (pScene->NextScene() == "MainGame") {
        pScene.reset(new MainGameScene);
	  }
	  else if (pScene->NextScene()=="Result") {
		  pScene.reset(new ResultScene);
	  }
      if (!pScene->Initialize()) {
        return 1;
      }
      window.InitTimer();
    }

    pScene->ProcessInput();
    pScene->Update();
    pScene->Render();
    window.SwapBuffers();

	audio.Update();//オーディオシステムの更新.
  }
  pScene->Finalize();
  audio.Destroy();//オーディオシステムの削除.

  return 0;
}
