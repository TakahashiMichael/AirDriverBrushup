/**
* @file MainGameScene.h
*/
#ifndef MAINGAMESCENE_H_INCLUDED
#define MAINGAMESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "Actor.h"
#include "GroundGrid.h"
#include <random>

#include "Camera.h"
#include "Audio.h"
#include "Font.h"
#include "Sprite.h"

/**
* ���C���Q�[�����.
*/
class MainGameScene : public Scene
{
public:
  MainGameScene() = default;
  virtual ~MainGameScene() = default;

  virtual bool Initialize() override;
  virtual void ProcessInput() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Finalize() override;

private:
  MeshList& meshList = MeshList::Instance();
  GroundGrid groundGrid;
  

  Texture::Image2D texId;
  Texture::Image2D texRanWay;
  Texture::Image2D texTree;
  Texture::Image2D texHouse;
  Texture::Image2D texRock;
  Texture::Image2D texHuman;
  Texture::Image2D texBullet;
  Texture::Image2D texFont;
  Texture::Image2D texSkyBox;

  std::map<int,Texture::Image2D> texNums;		//�_��

  Shader::Program progSimple;
  Shader::Program progLighting;
  Shader::LightList lights;

  float pointLightAngle;

  enum class State {
	StandBy,
    play,
    stageClear,
    gameOver,
	hitPanel,

  };
  State state = State::play;

  std::mt19937 random;

  PlayerActor player;
  Actor SkyBox;
  std::vector<Actor*> playerBulletList;
  std::vector<Actor*> enemyList;
  std::vector<Actor*> objectList;


  //audio�̃e�X�g.
  Audio::EngineRef audio = Audio::Engine::Instance();
  Audio::SoundPtr backBGM;
  Audio::SoundPtr SEpanelHit; //�p�l���ɏՓ˂������̉�
  Audio::SoundPtr SEradyGo;	//���i����Ƃ�


  //�X�v���C�g�̃e�X�g.
  Sprite2D sprTest;


  /*
  * �|�C���g�X�g���C�N�Ŏg���ϐ�
  *
  *	�����܂ŕϐ����₷�Ȃ�N���X������ׂ��ł�?? 2/12
  */
  const glm::vec2 frontPanel = glm::vec2(200, 200);	//���ʃp�l���̑傫��
  const int frontWidthCount = 5;						//���ʃp�l���̉��̖���.
  const int frontHeightCount = 5;							//���ʃp�l���̏c�̐�
  const int frontPanelAll = frontWidthCount * frontHeightCount;		//���ʃp�l���̖���
  const glm::vec2 frontOnePanel = glm::vec2(frontPanel.x / frontWidthCount, frontPanel.y / frontHeightCount);		//�ꖇ������̉��Əc.
  const glm::vec2 footPanel = glm::vec2(200, 200);		//���p�l���̑傫��.
  const int footWidthCount = 5;
  const int footHeightCount = 5;
  const int footPanelAll = footWidthCount * footHeightCount;	//���p�l���̖���
  const glm::vec2 footOnePanel = glm::vec2(footPanel.x / footWidthCount, footPanel.y / footHeightCount);
  
  const int panelCountAll = frontPanelAll + footPanelAll;
  const glm::vec3 playerStartPos = glm::vec3(footPanel.x/2,frontPanel.y*2/3+100,footPanel.y+300.0f);
  std::vector<Actor*> frontPanelList;
  std::vector<Actor*> footPanelList;
  const glm::vec3 ranwaySize =glm::vec3(50,0,200) ;//�����H�̒���
  const glm::vec3 ranwayOrigin = glm::vec3(footPanel.x/2,frontPanel.y*2/3,footPanel.y+ranwaySize.z/2);//�����H�̌��_
  std::vector<int> pointList;				//�_���ł̕��z.

  //�f�o�b�O�p�J�����ƒ����_
  Camera camera;
  glm::vec3 cameraTarget=glm::vec3();
  //�p�l���Ƃ̓����蔻������m����.
  void HitPanel();
  //�v���C���[�̃|�W�V�����̐���.
  enum class Area {
	  RanWay,		//�����H
	  Air,			//�󒆂ɔ�яo������,
  };
  Area playerArea;
  void ControlPos();

  //�v���C���[�̈ʒu����Ԃ������p�l���i���o�[����肷��
  int PanelNumSpecific();
  int hitPanelNum=0;


  //�Q�[���̌J��Ԃ���
  const int tryMax = 1;
  int tryCount = 0;

  //�ă`�������W
  void Restart();


  //�ҋ@���.
  void StandBy();
  const float stanbyTime = 1.2f;
  float stanbyTimer=stanbyTime;
  

  //�p�l���ɂƂǂ܂鎞��
  const float stayPanelTime=4.0f;
  float stayPanelTimer = 0.0f;

  //�p�l���ɂƂǂ܂鏈��
  void StayPanel();

  //���U���g�V�[���Ɉڂ鏈��.
  void GoResult();

  //�t�F�[�h�C���A�E�g�Ɏg��vec4
  glm::vec4 whiteOut;
  //�p�l���̍��v���_���L�^����ϐ�
  int TotalPoint=0;

  //�p�l���ɓ��_������U��V���b�t��
  void PanelPointShuffle();

};

#endif // MAINGAMESCENE_H_INCLUDED