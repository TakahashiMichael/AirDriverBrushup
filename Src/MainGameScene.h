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
* メインゲーム画面.
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

  std::map<int,Texture::Image2D> texNums;		//点板

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


  //audioのテスト.
  Audio::EngineRef audio = Audio::Engine::Instance();
  Audio::SoundPtr backBGM;
  Audio::SoundPtr SEpanelHit; //パネルに衝突した時の音
  Audio::SoundPtr SEradyGo;	//発進するとき


  //スプライトのテスト.
  Sprite2D sprTest;


  /*
  * ポイントストライクで使う変数
  *
  *	ここまで変数増やすならクラス化するべきでは?? 2/12
  */
  const glm::vec2 frontPanel = glm::vec2(200, 200);	//正面パネルの大きさ
  const int frontWidthCount = 5;						//正面パネルの横の枚数.
  const int frontHeightCount = 5;							//正面パネルの縦の数
  const int frontPanelAll = frontWidthCount * frontHeightCount;		//正面パネルの枚数
  const glm::vec2 frontOnePanel = glm::vec2(frontPanel.x / frontWidthCount, frontPanel.y / frontHeightCount);		//一枚当たりの横と縦.
  const glm::vec2 footPanel = glm::vec2(200, 200);		//床パネルの大きさ.
  const int footWidthCount = 5;
  const int footHeightCount = 5;
  const int footPanelAll = footWidthCount * footHeightCount;	//床パネルの枚数
  const glm::vec2 footOnePanel = glm::vec2(footPanel.x / footWidthCount, footPanel.y / footHeightCount);
  
  const int panelCountAll = frontPanelAll + footPanelAll;
  const glm::vec3 playerStartPos = glm::vec3(footPanel.x/2,frontPanel.y*2/3+100,footPanel.y+300.0f);
  std::vector<Actor*> frontPanelList;
  std::vector<Actor*> footPanelList;
  const glm::vec3 ranwaySize =glm::vec3(50,0,200) ;//滑走路の長さ
  const glm::vec3 ranwayOrigin = glm::vec3(footPanel.x/2,frontPanel.y*2/3,footPanel.y+ranwaySize.z/2);//滑走路の原点
  std::vector<int> pointList;				//点数版の分布.

  //デバッグ用カメラと注視点
  Camera camera;
  glm::vec3 cameraTarget=glm::vec3();
  //パネルとの当たり判定を検知する.
  void HitPanel();
  //プレイヤーのポジションの制御.
  enum class Area {
	  RanWay,		//滑走路
	  Air,			//空中に飛び出した後,
  };
  Area playerArea;
  void ControlPos();

  //プレイヤーの位置からぶつかったパネルナンバーを特定する
  int PanelNumSpecific();
  int hitPanelNum=0;


  //ゲームの繰り返し回数
  const int tryMax = 1;
  int tryCount = 0;

  //再チャレンジ
  void Restart();


  //待機状態.
  void StandBy();
  const float stanbyTime = 1.2f;
  float stanbyTimer=stanbyTime;
  

  //パネルにとどまる時間
  const float stayPanelTime=4.0f;
  float stayPanelTimer = 0.0f;

  //パネルにとどまる処理
  void StayPanel();

  //リザルトシーンに移る処理.
  void GoResult();

  //フェードインアウトに使うvec4
  glm::vec4 whiteOut;
  //パネルの合計得点を記録する変数
  int TotalPoint=0;

  //パネルに得点を割り振りシャッフル
  void PanelPointShuffle();

};

#endif // MAINGAMESCENE_H_INCLUDED