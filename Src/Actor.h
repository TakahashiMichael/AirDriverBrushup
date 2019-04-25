/**
* @file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <GL/glew.h>
#include "Shader.h"
#include "MeshList.h"
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include "Sprite.h"
#include "Camera.h"
/**
* 直方体.
*/
struct Rect
{
  glm::vec3 origin;
  glm::vec3 size;
};

/**
* シーンに配置するオブジェクト.
*/
class Actor
{
public:
  Actor() = default;
  virtual ~Actor() = default;

  void Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
  void Finalize();

  virtual void Update(float deltTIme);

public:
  int mesh = 0;
  GLuint texture = 0;

  glm::vec3 position = glm::vec3(0);
  glm::vec3 rotation = glm::vec3(0);
  glm::vec3 scale = glm::vec3(1);

  glm::vec3 velocity = glm::vec3(0);
  glm::vec3 tmpVelocity = glm::vec3(0);
  int health = 0; 
  Rect colLocal;
  Rect colWorld;
};

Actor* FindAvailableActor(std::vector<Actor*>&);
void UpdateActorList(std::vector<Actor*>&, float);
void RenderActorList(std::vector<Actor*>&, Shader::Program&, MeshList&);
void ClearActorList(std::vector<Actor*>&);

/**
*
*/
class PlayerActor : public Actor
{
public:
  virtual ~PlayerActor() = default;
  virtual void Update(float deltaTime) override;
  void ProcessInput();
  void FontRender();				//デバッグ用.
  enum {
	  Moveform_Straight,				//直進
	  Moveform_brake,					//ブレーキ,
	  Moveform_Air,						//空中.
	  Moveform_AirBrake,				//空中のブレーキ,
  };


  void setMoveform(int _moveform);					//動きのパターンのセッター.
  int GetMoveform() { return this->moveform; };
  void Move(float deltatime);												//追加//試しの動きを実装したい

  const glm::vec3& CameraPos() { return camera.Pos(); }
  const glm::vec3& CameraTarPos() { return camera.TargetPos(); }
  float direction = 0;//ラジアン多分

  bool stop = false;	//たちまち必要だったのでついあk.
  void resetParam();	//速度等を0に

  bool isGround = true;				//ないと上手くいかない気がしてきた

private:



	int moveform = Moveform_Straight;		//動きのパターン.2/5の時点ではしばらく真っすぐ
  float downAngle = 0;						

  glm::vec3 vNormal=glm::vec3(0);		//進行方向.	
  float speed=0;						//速度度
  float acceleration=15.0f;				//加速度
  float maxSpeed=60.0f;					//最高速
  float deceleration = 50.0f;			//減速度,ブレーキパワー
  float turning = 10.0f;				//旋回性能,
  float flightForce = 60.0f;				//飛ぶ力
  float flightTimer = 3.0f;				
  float downSpeed = 60.0f;

  PlayerCamera camera=PlayerCamera(&position,&vNormal);				//付属品のカメラ.

  void ResetMoveVal();					//値の設定.
};

/**
*
*/
class BulletActor : public Actor
{
public:
  virtual ~BulletActor() = default;
  virtual void Update(float deltaTime) override;
};

/**
*
*/
class ZombieActor : public Actor
{
public:
  virtual ~ZombieActor() = default;
  virtual void Update(float deltaTime) override;

public:
  Actor* target = nullptr;
  float attackingTimer = 5.0f;
  bool isAttacking = false;
  float baseSpeed = 1.0f;
};
bool DetectCollision(const Actor&, const Actor&);

// 衝突した面(0=左, 1=右, 2=下, 3=上, 4=奥, 5=手前).
enum class CollisionPlane
{
  none = -1, // 衝突なし.
  negativeX = 0, // 左側.
  positiveX, // 右側.
  negativeY, // 下側.
  positiveY, // 上側.
  negativeZ, // 奥側.
  positiveZ, // 手前側.
};

struct CollisionTime
{
  float time; // 衝突した時間.
  CollisionPlane plane; // 衝突した面.
};

CollisionTime FindCollisionTime(const Actor&, const Actor&, float);

#endif // ACTOR_H_INCLUDED