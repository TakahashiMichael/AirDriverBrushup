#include "Calculation.h"
#include <iostream>


namespace Cal {

	//��_�̋��������߂�
	float hypotenuse(glm::vec3 A, glm::vec3 B) {
		float lan;
		float x;
		float y;

		x = A.x - B.x;
		y = A.y - B.y;

		lan = sqrt(std::pow(x, 2) + std::pow(y, 2));
		return lan;
	}
	//��ɓ��͂������W�����ɓ��͂������W�ւ�vec3�����߂�.
	glm::vec3 vectorAB(glm::vec3 A, glm::vec3 B) {

		return B - A;
	}



	//����(float len),���瑬��(float speed)�����邾��.
	float speed(float len, float speed) {

		return (len / speed);
	}


	//----------------------------------------------------------
	//�ȉ��^�C�}�[�����炷����.
	bool runTimer(float timer, float deltatime, float settimer) {
		if (timer >= 0) {
			timer -= deltatime;
		}
		if (timer > 0) {
			return false;
		}
		else {
			timer = settimer + timer;
			return true;
		}
	}
	bool runTimer(float timer, float deltatime) {
		if (timer >= 0) {
			timer -= deltatime;
		}
		if (timer > 0) {
			return false;
		}
		else {
			return true;
		}
	}
	//--------------------------------------------------------------------------------
	//������.���W�A���ŕԂ�.
	float thetaAB(glm::vec3 posA, glm::vec3 posB) {
		float theta = 0.0f;
		float x = posB.x - posA.x;
		float y = posB.y - posA.y;
		theta = atan2(y, x);
		return theta;
	}


	//�ȉ��O�ς𒲂ׂ鎮.
	bool clossProduct(glm::vec3 vecA, glm::vec3 vecB, glm::vec3 posC) {
		return((vecB.x - vecA.x)*(posC.y - vecA.y) - (posC.x - vecA.x)*(vecB.y - vecA.y)) >= 0;
	}
	//�O��XZver,AB�x�N�g���Ɠ_C
	bool crossProductXZ(const glm::vec3& vecA,const glm::vec3& vecB ,const glm::vec3& posC) {

		return((vecB.x - vecA.x)*(posC.z - vecA.z) - (posC.x - vecA.x)*(vecB.z - vecA.z)) >= 0;
	}
	
	/*
	*  x���W��y���W�A�܂��Ώۂ̃|���S�����獂��Y�����߂�
	*  @param polyPosA,polyPosB,polyPosC :�|���S����`�悷��position
	*  
	*  
	*  @return val :Y���W�̍���.
	*/
	float HeightOfPolygon(const glm::vec3& polyPosA, const glm::vec3& polyPosB,const glm::vec3& polyPosC, glm::vec3& checkPos)
	{
		//�@�����v�Z.
		glm::vec3 AB=polyPosB-polyPosA,AC=polyPosC-polyPosA ;
		glm::vec3 vNormal = glm::normalize(glm::cross(AB,AC));
		//�|���S����
		return HeightOfPolygon(vNormal,polyPosA,checkPos);
	}

	//�|���S���̃|�W�V�����͂ǂ��ł������͂�,
	float HeightOfPolygon(const glm::vec3& polyNormal,const glm::vec3& polyPos, const glm::vec3& checkPos)
	{
		float posY = polyPos.y - ((polyNormal.x*(checkPos.x-polyPos.x))+(polyNormal.z*(checkPos.z-polyPos.z))) / polyNormal.y;

		return posY;
	}


	/*
	* �|���S���ƃ��C���̓����蔻������.
	* @param :polyPosA,polyPosB,polyPosC�@�|���S�����`������O�_
	* 
	* @param :LinePosA,LinePosB			������������̎n�_�ƏI�_
	* 
	* 
	* 
	*/
	bool HitPolyAndLine(const glm::vec3& polyPosA, const glm::vec3& polyPosB, glm::vec3& polyPosC, glm::vec3& LinePosA, const glm::vec3& LinePosB)
	{
		//�@�����v�Z.
		glm::vec3 AB = polyPosB - polyPosA, AC = polyPosC - polyPosA;
		glm::vec3 vNormal = glm::normalize(glm::cross(AB, AC));
		//�|���S����
		return HitPolyAndLine(vNormal, polyPosA, LinePosA,LinePosB);
	}
	//�@���ƃ|���̈�_�Ɛ���
	bool HitPolyAndLine(const glm::vec3& polyNormal,const glm::vec3& polyPos,const glm::vec3& LinePosA, const glm::vec3& LinePosB)
	{
		glm::vec3 vecA = LinePosA-polyPos;
		glm::vec3 vecB = LinePosB-polyPos;
		float A=glm::dot(polyNormal,vecA);
		float B=glm::dot(polyNormal, vecB);
		return (A*B)<0;
	}
}