//TPS�J�����N���X

#ifndef CAMERA_H_INCLUDET
#define CAMERA_H_INCLUDET
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
	Camera() = default;
	Camera(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distance�ɉ��Z.
	const glm::vec3& GetPos();				//�J�����̃|�W�V������Ԃ�.
	glm::vec3 normalXZ();					//XZ���ʏ�̃J��������v���C���[�Ɍ������@�����擾.
	glm::vec3 normalXZ(float angle);		//���̉�]ver :�����̓I�C���[�p
	void normalRotateY(float angle);		//Y����](�@��),�����I�C���[�p	
	void normalRotateX(float angle);		//Y����](�@��),�����I�C���[�p
private:
	const glm::vec3* targetPos;			//�ΏۂƂȂ�L�����N�^�[�̃|�C���^
	glm::vec3 position;					//�J�����̃|�W�V����
	glm::vec3 normal;					//�Ώۂ���J�����Ɍ������@�����F�N�g��
	float distance;						//�Ώۂ���J�����܂ł̋���
	glm::vec3 rotate=glm::vec3(0);		//�J�����̉�]�p�̊e����.(�I�C���[�p),(z���͐ݒ肵�ĂȂ�)
	void calucPos();					//targetPos,position,normal ����J�����̃|�W�V�������v�Z����.
	void calucNormal();					//rotate��񂩂�normal���Čv�Z����.
	void resetRotate();					//rotate�̒l���C������.

};

//fps�J�����e�X�g
class Camera2 {
public:
	Camera2() = default;
	Camera2(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distance�ɉ��Z.
	const glm::vec3& GetPos();				//�J�����̃|�W�V������Ԃ�.
	glm::vec3 ViewPoint();					//�����_��Ԃ�
	glm::vec3 normalXZ();					//XZ���ʏ�̃J��������v���C���[�Ɍ������@�����擾.
	glm::vec3 normalXZ(float angle);		//���̉�]ver :�����̓I�C���[�p
	void normalRotateY(float angle);		//Y����](�@��),�����I�C���[�p	
	void normalRotateX(float angle);		//Y����](�@��),�����I�C���[�p
private:
	const glm::vec3* targetPos;			//�ΏۂƂȂ�L�����N�^�[�̃|�C���^
	glm::vec3 position;					//�J�����̃|�W�V����
	glm::vec3 normal;					//�Ώۂ���J�����Ɍ������@�����F�N�g��
	float distance;						//�Ώۂ���J�����܂ł̋���
	glm::vec3 rotate = glm::vec3(0);	//�J�����̉�]�p�̊e����.(�I�C���[�p),(z���͐ݒ肵�ĂȂ�)
	void calucPos();					//targetPos,position,normal ����J�����̃|�W�V�������v�Z����.
	void calucNormal();					//rotate��񂩂�normal���Čv�Z����.
	void resetRotate();					//rotate�̒l���C������.

};



//�v���C���[�̑O����
class Camera3 {
public:
	Camera3() = default;
	Camera3(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distance�ɉ��Z.
	const glm::vec3& GetPos();				//�J�����̃|�W�V������Ԃ�.
	glm::vec3& SetPos();					//
	glm::vec3 normalXZ();					//XZ���ʏ�̃J��������v���C���[�Ɍ������@�����擾.
	glm::vec3 normalXZ(float angle);		//���̉�]ver :�����̓I�C���[�p
	void normalRotateY(float angle);		//Y����](�@��),�����I�C���[�p	
	void normalRotateX(float angle);		//Y����](�@��),�����I�C���[�p
private:	
	const glm::vec3* targetPos;			//�ΏۂƂȂ�L�����N�^�[�̃|�C���^
	glm::vec3 position;					//�J�����̃|�W�V����
	glm::vec3 normal;					//�Ώۂ���J�����Ɍ������@�����F�N�g��
	float distance;						//�Ώۂ���J�����܂ł̋���
	glm::vec3 rotate = glm::vec3(0);	//�J�����̉�]�p�̊e����.(�I�C���[�p),(z���͐ݒ肵�ĂȂ�)
	void calucPos();					//targetPos,position,normal ����J�����̃|�W�V�������v�Z����.
	void calucNormal();					//rotate��񂩂�normal���Čv�Z����.
	void resetRotate();					//rotate�̒l���C������.

};


/*
* �{�� �V�т͏I��肾(�� ��)
*
* �F�X�l�������ʃJ�����̓v���C���[�Ɏ�������̂���Ԃ����C������
* �Ƃ肠��������čl����2/10
*
* �J�����d�l�̓v���C���[�̐i�s�����ɒ����_
*
* ��{�̓v���C���[�̌�납�璍���_�����邪���͂ɂ���Ă͂�����
* ��]�����ʒu���璍���_���݂邱�Ƃ�����
*/
class PlayerCamera {
public:
	PlayerCamera() = default;
	PlayerCamera(glm::vec3*,glm::vec3*);

	void ProcessInput();					//����
	void Update();							//�X�V
	const glm::vec3& Pos();					//�Q�b�^�[�}��
	const glm::vec3& TargetPos();			//�����_.

private:
	glm::vec3 position;						//�J�����̍��W
	glm::vec3 targetPos;					//�����_
	glm::vec3 normalTC;						//�����_����J�����ւ̖@��
	glm::vec3 rotateTC=glm::vec3(20,0,0);					//vecTP����ɂ�������vecTC�ɑ΂���I�C���[��]�pY(����),X(����).(Z��0��)
	glm::vec3* playerPos=nullptr;			//�Ώۂ̃v���C���[�̍��W.
	glm::vec3* playerDir=nullptr;			//�Ώۂ̃v���C���[�̐i�s����

	float maxRotateY = 15.0f;				//�p�x���ς����E
	float distancePT=5.0f;					//�v���C���[���璍���_�̋���/
	float distanceCT=15.0f;					//�J�������璍���_�̋���.



	void TarPosUpdate();					//�����_���v�Z����.
	void NormalTCUpdate();					//�����_����J�����ւ̖@�����v�Z.
	void PosUpdate();

};

#endif // !CAMERA_H_INCLUDET
