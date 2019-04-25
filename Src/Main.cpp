
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

/// �G���g���[�|�C���g.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL AirDriver")) {
    return 1;
  }

  //�����V�X�e���̏�����.
  Audio::EngineRef audio = Audio::Engine::Instance();
  if (!audio.Initialize()) {
	  return 1;
  }

  //�����_���[�V�X�e���̏�����.
  SpriteRenderer& renderer = SpriteRenderer::Instance();
  if (!renderer.Init()) {
	  return 1;
  }
  //Font�̏�����.
  Font& font = Font::Instance();
  if (!font.Init()) {
	  return 1;
  }
  std::shared_ptr<Scene> pScene(new TitleScene);
  if (!pScene->Initialize()) {
	  return 1;
  }

  // ���C�����[�v.
  window.InitTimer();
  while (!window.ShouldClose()) {
    window.Update();

    // �V�[����؂�ւ���.
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

	audio.Update();//�I�[�f�B�I�V�X�e���̍X�V.
  }
  pScene->Finalize();
  audio.Destroy();//�I�[�f�B�I�V�X�e���̍폜.

  return 0;
}
