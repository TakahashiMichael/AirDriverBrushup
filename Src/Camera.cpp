#include "Camera.h"
#include <iostream>
#include "GLFWEW.h"



//distance�̉��Z
void Camera::AddDistance(float f) {
	this->distance += f;
	this->calucNormal();
}


/*
* �J�����̃|�W�V�������v�Z���ĕԂ�.
*
*
*
*
*/
const glm::vec3& Camera::GetPos()
{
	calucPos();//�J�����̈ʒu���Čv�Z.

	//std::cout << "�o�O�`�F�b�Ny�̉�]:" << this->rotate.y << std::endl;

	return this->position;
}

//�Ō�

glm::vec3 Camera::normalXZ()
{

	return normalXZ(0.0f);
}
glm::vec3 Camera::normalXZ(float angle) {

	//normal���v���C���[����J�����̖@���Ȃ̂Ő������t��.
	glm::vec3 xz = -(normal);
	//y������0�ɂ��Đ��K�����ĉ�],�Ō�ɒP�ʃx�N�g����;
	xz.y = 0;

	xz = glm::rotate(glm::mat4x4(1), glm::radians(angle), glm::vec3(0, 1, 0)) * glm::vec4(xz, 1);


	return glm::normalize(xz);

}

/*
* ���݂̃J����class�������Ă�l����J�����̈ʒu���v�Z���܂�.
* distance�̕������Ȃǂ͂����Œ�������.
*/
void Camera::calucPos() {
	//distance��0�ȉ��Ȃ�0.1�ɖ߂�.
	if (distance <= 0) {
		distance = 0.1f;
	}


	this->position = (normal * distance) + (*targetPos);
}

//Y����](�@��),�����I�C���[�p
void Camera::normalRotateY(float angle) {

	rotate.y += angle;
	this->resetRotate();
	this->calucNormal();
}
//Y����](�@��),�����I�C���[�p
void Camera::normalRotateX(float angle) {

	rotate.x += angle;
	this->resetRotate();
	this->calucNormal();
}

void Camera::resetRotate() {
	//x�̉�]�����傫������ƃJ�������o�O��̂Œ���.
	if (this->rotate.x > 89.0f)
	{
		std::cout << "���_x1" << std::endl;
		this->rotate.x = 89.0f;
	}
	else if (this->rotate.x < -89.0f)
	{

		std::cout << "���_x-1" << std::endl;
		this->rotate.x = -89.0f;
	}

	//�I�C���[�p�Ȃ̂�,y��180�𒴂�������-180�ɂ���

	if (this->rotate.y > 180.0f)
	{

		std::cout << "���_y1" << std::endl;
		this->rotate.y -= 360.0f;
	}
	else if (this->rotate.y < -180.0f)
	{
		std::cout << "���_y-1" << std::endl;
		this->rotate.y += 360.0f;
	}
}

void Camera::calucNormal() {
	//x��],y,��]���v�Z z��]�͈Ӗ���
	//const glm::mat4 matRotateX = glm::rotate(glm::mat4(1), glm::radians(rotate.x), glm::vec3(1, 0, 0));
	//const glm::mat4 matRotateXY = glm::rotate(matRotateX, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateYX = glm::rotate(matRotateY, glm::radians(rotate.x), glm::vec3(1, 0, 0));

	this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}



















//----------------------------------------------�������牺��tps�J����.




void Camera2::resetRotate() {
	//x�̉�]�����傫������ƃJ�������o�O��̂Œ���.
	if (this->rotate.x > 75.0f)
	{
		std::cout << "���_x1" << std::endl;
		this->rotate.x = 75.0f;
	}
	else if (this->rotate.x < -30.0f)
	{

		std::cout << "���_x-1" << std::endl;
		this->rotate.x = -30.0f;
	}

	//�I�C���[�p�Ȃ̂�,y��180�𒴂�������-180�ɂ���

	if (this->rotate.y > 180.0f)
	{

		std::cout << "���_y1" << std::endl;
		this->rotate.y -= 360.0f;
	}
	else if (this->rotate.y < -180.0f)
	{
		std::cout << "���_y-1" << std::endl;
		this->rotate.y += 360.0f;
	}
}
//distance�̉��Z
void Camera2::AddDistance(float f) {
	this->distance += f;
}
void Camera2::calucNormal() {
	//x��],y,��]���v�Z z��]�͈Ӗ���
	//const glm::mat4 matRotateX = glm::rotate(glm::mat4(1), glm::radians(rotate.x), glm::vec3(1, 0, 0));
	//const glm::mat4 matRotateXY = glm::rotate(matRotateX, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateYX = glm::rotate(matRotateY, glm::radians(rotate.x), glm::vec3(1, 0, 0));

	this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}

glm::vec3 Camera2::ViewPoint() {

	return this->normal*this->distance;

}





//-----------------------�ȉ�PlayerCamera-------------------------

//�R���X�g���N�^.
PlayerCamera::PlayerCamera(glm::vec3* playerPosPtr,glm::vec3* playerDirPtr):playerPos(playerPosPtr),playerDir(playerDirPtr){}


/*
* ���͏���
*
*
*
*/
void PlayerCamera::ProcessInput() {
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime = window.DeltaTime();
	//���͕����ɂ���ď��X�ɃJ�����𓮂���
	if (window.GetCommand(GLFWEW::Window::COMMANDLIST_RIGHT_PRESS)) {
		//���Α��ɌX���Ă���Ȃ疳���͂Ɠ����X�s�[�h�Ŗ߂�
		if (rotateTC.y < 0) {
			rotateTC.y += 60.0f*deltaTime;
		}
		else {
			rotateTC.y += 30.0*deltaTime;
			if (rotateTC.y >= maxRotateY) {
				rotateTC.y = maxRotateY;
			}
		}
	}
	else if (window.GetCommand(GLFWEW::Window::COMMANDLIST_LEFT_PRESS)) {
		//���Α��ɌX���Ă���Ȃ疳���͂Ɠ����X�s�[�h�Ŗ߂�
		if (rotateTC.y > 0) {
			rotateTC.y += -60.0f*deltaTime;
		}
		else {
			rotateTC.y += -30.0*deltaTime;
			if (rotateTC.y <= -maxRotateY) {
				rotateTC.y = -maxRotateY;
			}
		}
	}//�ǂ�������͂���Ă��Ȃ��Ȃ�y��߂�
	else {
		if (rotateTC.y != 0) {
			if (rotateTC.y > 0) {
				rotateTC.y -=60.0f*deltaTime;
			}
			else if (rotateTC.y < 0) {
				rotateTC.y -= -60.0f*deltaTime;

			}

			//�l���������̂Ȃ�0�ɂ���.
			if (rotateTC.y <= 1.0f && rotateTC.y >= -1.0f) {
				rotateTC.y = 0;
			}
		}
	}
}

/*
* �X�V����
*
*/
void PlayerCamera::Update() {
	//Update�Ƃ�����deltaTime������H
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime=window.DeltaTime();

	//�v�Z�֐����s.
	this->TarPosUpdate();
	this->NormalTCUpdate();
	this->PosUpdate();
}

/*
* �Q�b�^�[(Position)
*/
const glm::vec3& PlayerCamera::Pos() {
	return this->position;
}

/*
* �^�[�Q�b�g(�����_)�̍��W���v�Z����
*
*
*/
const glm::vec3& PlayerCamera::TargetPos() {

	return this->targetPos;
}

/*
* �����_�̌v�Z
*
* �o�^���Ă���v���C���[�̈ʒu�Ɛi�s����+���g��distansPT
* ���烏�[���h���W���v�Z����targetPos���X�V
*/
void PlayerCamera::TarPosUpdate() {
	//�����_=(�v���C���[�̃��[���h���W)+(P�̐i�s�����@��)*(����)
	targetPos = (*playerPos) + ((*playerDir)* distancePT);
}

/*
* �����_����J�����ւ̖@�����v�Z
*
*/
void PlayerCamera::NormalTCUpdate() {
	glm::vec3 normalTP = (-*playerDir);		//�������Ȃ��悤�ɂƂ肠���������_����v���C���[�̖@��
	normalTP.y = 0;
	normalTP = glm::normalize(normalTP);
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotateTC.y), glm::vec3(0, 1, 0));
	//�܂�Y�ŉ�]������xz���ʂ̖@��vecTC���o��,
	glm::vec3 normalTCxz = matRotateY * glm::vec4(normalTP,1);	

	//�Ȃ񂩑�������ŉ�]��axis���o��C������e�X�g
	glm::vec3 axis = glm::normalize(glm::cross(normalTCxz,glm::vec3(0,1,0)));
	const glm::mat4 matRotateX = glm::rotate(matRotateY, glm::radians(rotateTC.x), axis);

	//�����Ă邩��ԉ������Ƃ���Ȃ̂ŗv����
	this->normalTC = matRotateX * glm::vec4(normalTCxz,1);
	//this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}

/*
* Position�̌v�Z
*
*/
void PlayerCamera::PosUpdate() {
	//�J�����̈ʒu=�����_(���[���h���W)+(�@��TC*����)
	this->position = targetPos + (normalTC * distanceCT);

}