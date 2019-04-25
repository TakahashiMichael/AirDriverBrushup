#pragma once
#define _USE_MATH_DEFINES
#include <math.h> //���c����
#include "GLFWEW.h" //�������̏���
#include <glm/matrix.hpp>


namespace Cal{
	float radian(float angle);
	float angle(float radian);
	float hypotenuse(glm::vec3,glm::vec3);//��_�̋��������߂ăt���[�g�ŕԂ�.
	glm::vec3 vectorAB(glm::vec3, glm::vec3);//A����B�ւ̃x�N�g�������߂�.
	glm::vec3 scatterPos(glm::vec3 pos,float distance);//�����_����-dis~dis��x,y�ʁX�ɑ���
	float RorL(float);//50%�̊m���Ń}�C�i�X��������.
	float speed(float, float);//����������,
	bool circleCollision(glm::vec3,glm::vec3,float A,float B);//��̏Փ˔���.�𒲂ׂ�.
	bool circleCollision(glm::vec3,glm::vec3,float AandB);//��̏Փ˔���.�𒲂ׂ�.
	bool circleCollision(float distance,float A,float B);//��̏Փ˔���.�𒲂ׂ�.
	bool circleCollision(float distance,float AandB);//��̏Փ˔���.�𒲂ׂ�.
	bool runTimer(float timer, float deltatime, float settimer);
	bool runTimer(float timer,float deltatime);//�^�C�}�[����f���^�^�C�����������炷.
	float thetaAB(glm::vec3 posA, glm::vec3 posB);//posA�ɑ΂���posB�̃��p�x�𒲂ׂ�float�ŕԂ�.

	glm::vec3 destination(glm::vec3 pos ,float distance,float radian);//pos���璷���Ɗp�x����͂��ĖړI�n�̍��Wglm::vec3�����߂�

	bool clossProduct(glm::vec3 vecA,glm::vec3 vecB ,glm::vec3 posC);//vecAB�ɑ΂���_C�O�ς𒲂ׂ�.�x�N�g���ɑ΂��ē_����Ȃ�true
	//����XZver;
	bool crossProductXZ(const glm::vec3& vecA, const glm::vec3& vecB, const glm::vec3& posC);

	//�|���S���Ƃ�����W���炻�̍��������߂�.
	float HeightOfPolygon(const glm::vec3& polyPosA, const glm::vec3& polyPosB, const glm::vec3& polyPosC, glm::vec3& checkPos);
	//�|���S���̖@�����킩���Ă���ꍇ.
	float HeightOfPolygon(const glm::vec3& polyNormal, const glm::vec3& polyPos, const glm::vec3& checkPos);

	//�|���S���ƒ����̓����蔻��
	bool HitPolyAndLine(const glm::vec3& polyPosA, const glm::vec3& polyPosB, glm::vec3& polyPosC, glm::vec3& LinePosA,const glm::vec3& LinePosB);
	//�@���ƃ|���̈�_�Ɛ���
	bool HitPolyAndLine(const glm::vec3& polyNormal,const glm::vec3& polyPos,const glm::vec3& LinePosA, const glm::vec3& LinePosB);
};
