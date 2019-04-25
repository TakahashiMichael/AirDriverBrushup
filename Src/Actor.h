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
* ������.
*/
struct Rect
{
  glm::vec3 origin;
  glm::vec3 size;
};

/**
* �V�[���ɔz�u����I�u�W�F�N�g.
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
  void FontRender();				//�f�o�b�O�p.
  enum {
	  Moveform_Straight,				//���i
	  Moveform_brake,					//�u���[�L,
	  Moveform_Air,						//��.
	  Moveform_AirBrake,				//�󒆂̃u���[�L,
  };


  void setMoveform(int _moveform);					//�����̃p�^�[���̃Z�b�^�[.
  int GetMoveform() { return this->moveform; };
  void Move(float deltatime);												//�ǉ�//�����̓���������������

  const glm::vec3& CameraPos() { return camera.Pos(); }
  const glm::vec3& CameraTarPos() { return camera.TargetPos(); }
  float direction = 0;//���W�A������

  bool stop = false;	//�����܂��K�v�������̂ł���k.
  void resetParam();	//���x����0��

  bool isGround = true;				//�Ȃ��Ə�肭�����Ȃ��C�����Ă���

private:



	int moveform = Moveform_Straight;		//�����̃p�^�[��.2/5�̎��_�ł͂��΂炭�^������
  float downAngle = 0;						

  glm::vec3 vNormal=glm::vec3(0);		//�i�s����.	
  float speed=0;						//���x�x
  float acceleration=15.0f;				//�����x
  float maxSpeed=60.0f;					//�ō���
  float deceleration = 50.0f;			//�����x,�u���[�L�p���[
  float turning = 10.0f;				//���񐫔\,
  float flightForce = 60.0f;				//��ԗ�
  float flightTimer = 3.0f;				
  float downSpeed = 60.0f;

  PlayerCamera camera=PlayerCamera(&position,&vNormal);				//�t���i�̃J����.

  void ResetMoveVal();					//�l�̐ݒ�.
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

// �Փ˂�����(0=��, 1=�E, 2=��, 3=��, 4=��, 5=��O).
enum class CollisionPlane
{
  none = -1, // �Փ˂Ȃ�.
  negativeX = 0, // ����.
  positiveX, // �E��.
  negativeY, // ����.
  positiveY, // �㑤.
  negativeZ, // ����.
  positiveZ, // ��O��.
};

struct CollisionTime
{
  float time; // �Փ˂�������.
  CollisionPlane plane; // �Փ˂�����.
};

CollisionTime FindCollisionTime(const Actor&, const Actor&, float);

#endif // ACTOR_H_INCLUDED