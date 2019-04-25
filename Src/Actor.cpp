/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include "GLFWEW.h"
#include "Font.h"

/**
* ������.
*/
void Actor::Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{
  this->mesh = mesh;
  texture = tex;
  position = pos;
  rotation = rot;
  this->scale = scale;

  health = hp;
}


/**
* �I��.
*/
void Actor::Finalize()
{
}

/**
* �X�V.
*
* @param deltaTime �o�ߎ���.
*/
void Actor::Update(float deltaTime)
{
  position += velocity * deltaTime;
  colWorld.origin = colLocal.origin + position;
  colWorld.size = colLocal.size;
}

/**
* ���p�\��Actor���擾����.
*
* @param actorList �����Ώۂ̃A�N�^�[�̃��X�g.
*
* @return ���p�\��Actor�̃|�C���^.
*         ���p�\��Actor��������Ȃ����nullptr.
*/
Actor* FindAvailableActor(std::vector<Actor*>& actorList)
{
  for (auto& actor : actorList) {
    if (actor && actor->health <= 0) {
      return actor;
    }
  }
  return nullptr;
}

/**
* �A�N�^�[�̏�Ԃ��X�V����.
*
* @param actorList �X�V����A�N�^�[�̃��X�g.
* @param deltaTime �O��̍X�V����̌o�ߎ���.
*/
void UpdateActorList(std::vector<Actor*>& actorList, float deltaTime)
{
  for (auto& actor : actorList) {
    if (actor && actor->health > 0) {
      actor->Update(deltaTime);
    }
  }
}

/**
* Actor��`�悷��.
*
* @param actorList �`�悷��A�N�^�[�̃��X�g.
* @param shader    �`��Ɏg�p����V�F�[�_�[�E�I�u�W�F�N�g.
* @param meshList  �`��Ɏg�p���郁�b�V�����X�g.
*/
void RenderActorList(std::vector<Actor*>& actorList, Shader::Program& shader, MeshList& meshList)
{
  for (auto& actor : actorList) {
    if (actor && actor->health > 0) {
      shader.BindTexture(0, actor->texture);
      shader.Draw(meshList[actor->mesh], actor->position, actor->rotation, actor->scale);
    }
  }
}

/**
* �A�N�^�[���X�g����ɂ���.
*
* @param actorList ��ɂ���A�N�^�[�̃��X�g.
*/
void ClearActorList(std::vector<Actor*>& actorList)
{
  for (auto& actor : actorList) {
    delete actor;
  }
  actorList.clear();
}
/**
*
*/
void PlayerActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (health <= 0) {
    downAngle += glm::radians(-45.0f) * deltaTime;
    if (downAngle < glm::radians(-90.0f)) {
      downAngle = glm::radians(-90.0f);
    }
  }
  const glm::quat qx(glm::vec3(downAngle, 0, 0));
  const glm::quat qy(glm::vec3(0, direction, 0));
  rotation.y = glm::radians(direction);
  glm::mat4 matR = glm::rotate(glm::mat4(1), glm::radians(direction),glm::vec3(0,1,0));
  this->vNormal = matR*glm::vec4(0,0,1.0f,1);


  camera.Update();
  Move(deltaTime);
}

/*
* �v���C���[�̓�������������.
* moveform�œ�����ݒ肷��.
*/
void PlayerActor::Move(float deltaTime) {
	//�}�stop�@�t���b�O��ǉ�,on�Ȃ瓮���Ȃ�
	if (!stop) {
		//�O�i����,
		if (moveform == Moveform_Straight) {
			//�ǋL.�����ɕK�v�ȗv�f��ݒ�,
			{
				float gravity = 15.0f * deltaTime;
				this->position.y -= gravity;
			}

			if (speed <= maxSpeed) {
				speed += acceleration * deltaTime;
			}
			else if (speed > maxSpeed) {
				speed -= deceleration* deltaTime;
			}

			position += vNormal * speed * deltaTime;
		}
		//�u���[�L����.
		else if (moveform == Moveform_brake) {
			speed -= deceleration * deltaTime;
			if (speed < 0) {
				speed = 0;
			}
			//�d�͏���.
			{
				float gravity = 15.0f * deltaTime;
				position.y -= gravity;
			}
			position += vNormal * speed * deltaTime;

		}
		//
		else if (moveform == Moveform_Air) {
			if (speed<=maxSpeed) {
				speed += acceleration * deltaTime;
			}
			else {
				speed -= deceleration * deltaTime;
			}
			position += vNormal * speed * deltaTime;
			//�d�͏���.
			if (flightTimer >= 0) {
				flightTimer -= deltaTime;
				position.y += flightForce * deltaTime;
			}
			else {
				float gravity = 15.0f * deltaTime;
				position.y -= gravity;
			}
		}
		else if (moveform == Moveform_AirBrake) {
			speed -= deceleration * deltaTime;
			if (speed < 0) {
				speed = 0;
			}
			//�d�͏���.
			{
				float gravity = downSpeed * deltaTime;
				position.y -= gravity;
			}
			position += vNormal * speed * deltaTime;

		}
	}

}

/*
* �v���C���[�̓��͏���
*
*/
void PlayerActor::ProcessInput() {
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime = window.DeltaTime();

	if (window.GetCommand(GLFWEW::Window::COMMANDLIST_UP_PRESS)) {
	}
	else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_DOWN_PRESS)) {

	}
	if (window.GetCommand(GLFWEW::Window::COMMANDLIST_RIGHT_PRESS)) {
		this->direction += -turning * deltaTime;
	}
	else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_LEFT_PRESS)) {
		this->direction += turning * deltaTime;

	}
	else {
		//this->direction = 0.0f;

	}




	// �v���C���[���ړ�����.
	const float speed = 10.0f;

	if (window.GetCommand(GLFWEW::Window::COMMANDLIST_BRAKE)) {
		//�u���[�L����.
		if (isGround) {
			setMoveform(PlayerActor::Moveform_brake);
		}
		else if (!isGround) {
			setMoveform(PlayerActor::Moveform_AirBrake);
		}

	}
	else {
		//�X�y�[�X���͂��ĂȂ���΃A�N�Z��.
		if (isGround) {
			setMoveform(PlayerActor::Moveform_Straight);
		}
		else if (!isGround) {
			setMoveform(PlayerActor::Moveform_Air);
		}
	}


	camera.ProcessInput();
}


/*
* �v���C���[�ɏ�Ԃ�ݒ�,
* ��Ԃɂ��,�l�̍Đݒ�������ōs��.
* 
* 
*/
void PlayerActor::setMoveform(int _moveform) 
{
	moveform = _moveform; 
	this->ResetMoveVal();
}

void PlayerActor::resetParam() {
	this->speed = 0;
	this->isGround = true;
	this->direction = 180;
}

/*
* FontRender
*
*/
void PlayerActor::FontRender() {
	//font�̃e�X�g.�擾
	Font& font = Font::Instance();
	//font.AddString("Im Takahashi",glm::vec3(-350,100,0),glm::vec3(0,0,0),glm::vec3(2,2,1));
	//�X�e�[�^�X�̕\��.
	if (GetMoveform() == PlayerActor::Moveform_Straight) {
		font.AddString("MoveType Straight", glm::vec3(-350, 200, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 1));

	}
	else if (GetMoveform() == PlayerActor::Moveform_brake) {
		font.AddString("MoveType Brake", glm::vec3(-350, 200, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 1));

	}
	else if (GetMoveform() == PlayerActor::Moveform_Air) {
		font.AddString("MoveType Air", glm::vec3(-350, 200, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 1));

	}
	else if (GetMoveform() == PlayerActor::Moveform_AirBrake) {
		font.AddString("MoveType AirBrake", glm::vec3(-350, 200, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 1));

	}

	/*
	* �f�o�b�O�p�ɃX�e�[�^�X��\������.
	*
	*
	*
	*/
	int fontCount = 0; //�\�����Ă��鐔.
	const float fontSpace = 30.0f;//�t�H���g�ƃt�H���g�̏c�Ԋu
	const float fontsize = 1.5f;//�\���t�H���g�̑傫��.
	font.AddString("MaxSpeed", glm::vec3(-350, 150-(fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize,fontsize, 1));
	font.AddString(maxSpeed, glm::vec3(-150, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	++fontCount;
	font.AddString("Turning", glm::vec3(-350, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	font.AddString(turning, glm::vec3(-150, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));

	++fontCount;
	font.AddString("Accele", glm::vec3(-350, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	font.AddString(acceleration, glm::vec3(-150, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));

	++fontCount;
	font.AddString("Decele", glm::vec3(-350, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	font.AddString(deceleration, glm::vec3(-150, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));

	++fontCount;
	font.AddString("FlightF", glm::vec3(-350, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	font.AddString(flightForce, glm::vec3(-150, 150 - (fontSpace*fontsize*fontCount), 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));

	font.AddString("Speed", glm::vec3(150, 150 , 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));
	font.AddString(speed, glm::vec3(350, 150 , 0), glm::vec3(0, 0, 0), glm::vec3(fontsize, fontsize, 1));


	//float speed = 0;						//���x�x
	//float acceleration = 15.0f;				//�����x
	//float maxSpeed = 60.0f;					//�ō���
	//float deceleration = 50.0f;			//�����x,�u���[�L�p���[
	//float turning = 10.0f;				//���񐫔\,
	//float flightForce = 10.0f;				//��ԗ�
	//float flightTimer = 1.0f;
}

/*
* �v���C���[�̏�Ԃɉ����Ēl���Đݒ肷��.
*/
void PlayerActor::ResetMoveVal() 
{
	if (this->moveform == Moveform_Straight) {
		acceleration = 20.0f;			//�����x
		maxSpeed = 60.0f;				//�ō���
		turning = 30.0f;				//���񐫔\,
		flightTimer = 1.0f;
	}
	else if (this->moveform == Moveform_brake) {
		acceleration = 15.0f;			//�����x
		maxSpeed = 30.0f;				//�ō���
		turning = 50.0f;				//���񐫔\,
		flightTimer = 1.0f;
	}
	else if (this->moveform == Moveform_Air)
	{
		acceleration = 30.0f;			//�����x
		maxSpeed = 150.0f;				//�ō���
		turning = 60.0f;				//���񐫔\,

	}
	else if (this->moveform==Moveform_AirBrake)
	{
		acceleration = 15.0f;			//�����x
		maxSpeed = 60.0f;				//�ō���
		turning = 5.0f;					//���񐫔\,

	}


}

/**
*
*/
void BulletActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (glm::any(glm::lessThan(position, glm::vec3(-20)))) {
    health = 0;
  } else if (glm::any(glm::greaterThanEqual(position, glm::vec3(20)))) {
    health = 0;
  }
}

/**
*
*/
void ZombieActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (!target) {
    return;
  }

  const float moveSpeed = baseSpeed * 2.0f;
  const float rotationSpeed = baseSpeed * glm::radians(60.0f);
  const float frontRange = glm::radians(15.0f);

  const glm::vec3 v = target->position - position;
  const glm::vec3 vTarget = glm::normalize(v);
  float radian = std::atan2(-vTarget.z, vTarget.x) - glm::radians(90.0f);
  if (radian <= 0) {
    radian += glm::radians(360.0f);
  }
  const glm::vec3 vZombieFront = glm::rotate(glm::mat4(1), rotation.y, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
  if (std::abs(radian - rotation.y) > frontRange) {
    const glm::vec3 vRotDir = glm::cross(vZombieFront, vTarget);
    if (vRotDir.y >= 0) {
      rotation.y += rotationSpeed * deltaTime;
      if (rotation.y >= glm::radians(360.0f)) {
        rotation.y -= glm::radians(360.0f);
      }
    } else {
      rotation.y -= rotationSpeed * deltaTime;
      if (rotation.y < 0) {
        rotation.y += glm::radians(360.0f);
      }
    }
  }

  // �\���ɐڋ߂��Ă��Ȃ���Έړ�����. �ڋ߂��Ă���΍U������.
  if (glm::length(v) > 1.0f) {
    velocity = vZombieFront * moveSpeed;
  } else {
    velocity = glm::vec3(0);
    // ����I�ɍU����ԂɂȂ�.
    if (isAttacking) {
      isAttacking = false;
      attackingTimer = 5.0f;
    } else {
      attackingTimer -= deltaTime;
      if (attackingTimer <= 0) {
        isAttacking = true;
      }
    }
  }
}

/**
* 2�̒����`�̏Փˏ�Ԃ𒲂ׂ�.
*
* @param lhs �����`����1.
* @param rhs �����`����2.
*
* @retval true  �Փ˂��Ă���.
* @retval false �Փ˂��Ă��Ȃ�.
*/
bool DetectCollision(const Actor& lhs, const Actor& rhs)
{
  return
    lhs.colWorld.origin.x < rhs.colWorld.origin.x + rhs.colWorld.size.x &&
    lhs.colWorld.origin.x + lhs.colWorld.size.x > rhs.colWorld.origin.x &&
    lhs.colWorld.origin.y < rhs.colWorld.origin.y + rhs.colWorld.size.y &&
    lhs.colWorld.origin.y + lhs.colWorld.size.y > rhs.colWorld.origin.y &&
    lhs.colWorld.origin.z < rhs.colWorld.origin.z + rhs.colWorld.size.z &&
    lhs.colWorld.origin.z + lhs.colWorld.size.z > rhs.colWorld.origin.z;
}

/**
* �Փ˂���܂ł̌o�ߎ��Ԃ��v�Z����.
*/
CollisionTime FindCollisionTime(const Actor& a, const Actor& b, float deltaTime)
{
  const glm::vec3 aMin = a.colWorld.origin;
  const glm::vec3 aMax = aMin + a.colWorld.size;
  const glm::vec3 bMin = b.colWorld.origin;
  const glm::vec3 bMax = bMin + b.colWorld.size;

  // �A�N�^�[a���Î~�A�A�N�^�[b���ړ����Ă���Ƃ݂Ȃ��A�Փ˂��N�������ŒZ�����𒲂ׂ�.
  const glm::vec3 v = (b.velocity - a.velocity) * deltaTime;
  float tfirst = -1.0f;
  float tlast = 0.0f;
  CollisionPlane plane = CollisionPlane::none;
  for (int i = 0; i < 3; ++i) {
    // �ړ������ɂ���Ē��ׂ������ς���.
    if (v[i] < 0) { // b�͍��ֈړ���.
      // a���E���ɂ���(���ɗ���Ă���)�ꍇ�͏Փ˂Ȃ�.
      if (bMax[i] < aMin[i]) {
        return { 1, CollisionPlane::none };
      }
      // �Î~��(a)�E�[���ړ���(b)���[���E�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      // ���傫���ق����ՓˊJ�n�����Ƃ��č̗p.
      if (aMax[i] > bMin[i]) {
        const float newTime = (aMax[i] - bMin[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::positiveX, CollisionPlane::positiveY, CollisionPlane::positiveZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // �Î~��(a)���[���ړ���(b)�E�[���E�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      // ��菬�����ق����ՓˏI�������Ƃ��č̗p.
      if (aMin[i] > bMax[i]) {
        tlast = std::min((aMin[i] - bMax[i]) / v[i], tlast);
      }
    } else if (v[i] > 0) { // b�͉E�ֈړ���.
      // a�������ɂ���(���ɗ���Ă���)�ꍇ�͏Փ˂Ȃ�.
      if (bMin[i] > aMax[i]) {
        return { 1, CollisionPlane::none };
      }
      // �Î~��(a)���[���ړ���(b)�E�[��荶�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      if (aMin[i] < bMax[i]) {
        const float newTime = (aMin[i] - bMax[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::negativeX, CollisionPlane::negativeY, CollisionPlane::negativeZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // �Î~��(a)�E�[���ړ���(b)���[��荶�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      if (aMax[i] < bMin[i]) {
        tlast = std::min((aMax[i] - bMin[i]) / v[i], tlast);
      }
    }
  }

  if (tfirst > tlast) {
    return { 1, CollisionPlane::none };
  }

  return { tfirst, plane };
}