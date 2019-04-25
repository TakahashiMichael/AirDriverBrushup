#include "ResultScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include "FileNameData.h"
#include "Font.h"

/*
* ����������,
*
*/
bool ResultScene::Initialize()
{
	state = STATE::e_STATE_BEGIN_0;

	bgm = audio.Prepare(FILENAME_WAV_RESULTSCENE);
	SE_CortSound = audio.Prepare(FILENAME_WAV_RESULTCARVOICE);
	SE_ResultBegin = audio.Prepare(FILENAME_WAV_RESULTBEGIN);
	SE_ResultBegin->Play();
	//bgm->Play(Audio::Flag::Flag_Loop);
	//�w�i�̐ݒ�
	sprFrame = Sprite2D(FILENAME_TGA_RESULTFRAME);
	//��
	sprWhite = Sprite2D(FILENAME_TGA_WHITE);
	whiteOut = glm::vec4(1);
	sprWhite.SetColor(&whiteOut);
	//�J�[�g
	sprCart = Sprite2D(FILENAME_TGA_CART2D);
	sprCart.SetScale(glm::vec3(1));//�傫����ݒ肷��.
	cartPos = glm::vec3(2, 0, 0);
	sprCart.SetPos(cartPos);

	fontPos = glm::vec3(400,200,0);
	pointPos = cartPos*glm::vec3(800,600,0);

	//timer�̏�����.
	state_Begin_0_Timer = 0;
	state_Begin_1_Timer = 0;
	state_Transition_Timer = 0;
	return true;
}


/*
* ���͏���,
*
*/
void ResultScene::ProcessInput()
{
	if (state == STATE::e_STATE_DSIPLAYPOINTS) {
		GLFWEW::Window& window = GLFWEW::Window::Instance();
		if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DECISION)) {
			state = STATE::e_STATE_TRANSITION;
		}
	}
}

/*
* �X�V����,
*
*
*/
void ResultScene::Update()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltatime = (float)window.DeltaTime();

	if (state == STATE::e_STATE_BEGIN_0) {

		if (state_Begin_0_Timer <= state_Begin_0_Time) {
			//���w�i���烿�����Z���Ă���
			if (whiteOut.a > 0) {
				whiteOut.a -= deltatime / 2.0f;
				if (whiteOut.a <= 0) {
					whiteOut.a = 0;
				}
			}
			if (fontPos.x > -50) {
				fontPos.x -= fontScrollSpeed * deltatime;
			}
			state_Begin_0_Timer += deltatime;
		}
		else {
			state = STATE::e_STATE_BEGIN_1;
			bgm->Play(Audio::Flag::Flag_Loop);
			SE_CortSound->Play();
		}
		
	}
	else if (state == STATE::e_STATE_BEGIN_1) {
		if (state_Begin_1_Timer <= state_Begin_1_Time) {
			cartPos.x -= 3.0f * deltatime;
			sprCart.SetPos(cartPos);
			//��ʒu�܂ŃJ�[�g�̓����ɍ��킹��.
			if (pointPos.x > pointStayPosX) {
				pointPos = cartPos * glm::vec3(400, 300, 0)+glm::vec3(400,0,0);
				if (pointPos.x < pointStayPosX) {
					pointPos.x = pointStayPosX;

				}
			}
			state_Begin_1_Timer += deltatime;
		}
		else {
			state = STATE::e_STATE_DSIPLAYPOINTS;
		}

	}
	else if (state == STATE::e_STATE_DSIPLAYPOINTS) {
		sprCart.SetPos(cartPos);

	}
	else if (state==STATE::e_STATE_TRANSITION) {
		if (state_Transition_Timer < state_Transition_time) {
			//�z���C�g�A�E�g.
			if (whiteOut.a < 1) {
				whiteOut.a += deltatime;
				if (whiteOut.a >= 1) {
					whiteOut.a = 1;
				}
			}
			state_Transition_Timer += deltatime;
		}
		else {
			NextScene("Title");
		}
	}

}

/*
* �`�揈��,
*
*/
void ResultScene::Render()
{


	SpriteRenderer& renderer = SpriteRenderer::Instance();
	
	if(state == STATE::e_STATE_BEGIN_0){
		renderer.AddSprite(&sprFrame);
		renderer.AddSprite(&sprWhite);

	}
	else if (state == STATE::e_STATE_BEGIN_1) {
		renderer.AddSprite(&sprFrame);
		renderer.AddSprite(&sprWhite);

		renderer.AddSprite(&sprCart);
	}
	else if (state == STATE::e_STATE_DSIPLAYPOINTS) {
		renderer.AddSprite(&sprFrame);
		renderer.AddSprite(&sprWhite);
	}
	else if (state == STATE::e_STATE_TRANSITION) {
		renderer.AddSprite(&sprFrame);
		renderer.AddSprite(&sprWhite);
	}
	renderer.Draw();

	if (state==STATE::e_STATE_BEGIN_0) {
		Font& font = Font::Instance();
		font.AddString("Result", fontPos, glm::vec3(), glm::vec3(5));
		font.AddString(resultPoint, pointPos, glm::vec3(), glm::vec3(8));
	}
	else if (state == STATE::e_STATE_BEGIN_1) {
		Font& font = Font::Instance();
		font.AddString("Result", fontPos, glm::vec3(), glm::vec3(5));
		font.AddString(resultPoint, pointPos, glm::vec3(), glm::vec3(8));
	}
	else if (state ==STATE::e_STATE_DSIPLAYPOINTS) {
		Font& font = Font::Instance();
		font.AddString("Result", fontPos, glm::vec3(), glm::vec3(5));
		font.AddString(resultPoint, pointPos, glm::vec3(), glm::vec3(8));
	}
	else if (state == STATE::e_STATE_TRANSITION) {

	}
	

}

/*
* �I������,
*/
void ResultScene::Finalize()
{
	bgm->Stop();
}



int ResultScene::resultPoint;