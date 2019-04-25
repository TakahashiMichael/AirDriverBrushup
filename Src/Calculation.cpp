#include "Calculation.h"
#include <iostream>


namespace Cal {

	//二点の距離を求める
	float hypotenuse(glm::vec3 A, glm::vec3 B) {
		float lan;
		float x;
		float y;

		x = A.x - B.x;
		y = A.y - B.y;

		lan = sqrt(std::pow(x, 2) + std::pow(y, 2));
		return lan;
	}
	//先に入力した座標から後に入力した座標へのvec3を求める.
	glm::vec3 vectorAB(glm::vec3 A, glm::vec3 B) {

		return B - A;
	}



	//距離(float len),から速さ(float speed)を割るだけ.
	float speed(float len, float speed) {

		return (len / speed);
	}


	//----------------------------------------------------------
	//以下タイマーを減らす処理.
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
	//ただし.ラジアンで返す.
	float thetaAB(glm::vec3 posA, glm::vec3 posB) {
		float theta = 0.0f;
		float x = posB.x - posA.x;
		float y = posB.y - posA.y;
		theta = atan2(y, x);
		return theta;
	}


	//以下外積を調べる式.
	bool clossProduct(glm::vec3 vecA, glm::vec3 vecB, glm::vec3 posC) {
		return((vecB.x - vecA.x)*(posC.y - vecA.y) - (posC.x - vecA.x)*(vecB.y - vecA.y)) >= 0;
	}
	//外積XZver,ABベクトルと点C
	bool crossProductXZ(const glm::vec3& vecA,const glm::vec3& vecB ,const glm::vec3& posC) {

		return((vecB.x - vecA.x)*(posC.z - vecA.z) - (posC.x - vecA.x)*(vecB.z - vecA.z)) >= 0;
	}
	
	/*
	*  x座標とy座標、また対象のポリゴンから高さYを求める
	*  @param polyPosA,polyPosB,polyPosC :ポリゴンを描画するposition
	*  
	*  
	*  @return val :Y座標の高さ.
	*/
	float HeightOfPolygon(const glm::vec3& polyPosA, const glm::vec3& polyPosB,const glm::vec3& polyPosC, glm::vec3& checkPos)
	{
		//法線を計算.
		glm::vec3 AB=polyPosB-polyPosA,AC=polyPosC-polyPosA ;
		glm::vec3 vNormal = glm::normalize(glm::cross(AB,AC));
		//ポリゴンの
		return HeightOfPolygon(vNormal,polyPosA,checkPos);
	}

	//ポリゴンのポジションはどこでもいいはず,
	float HeightOfPolygon(const glm::vec3& polyNormal,const glm::vec3& polyPos, const glm::vec3& checkPos)
	{
		float posY = polyPos.y - ((polyNormal.x*(checkPos.x-polyPos.x))+(polyNormal.z*(checkPos.z-polyPos.z))) / polyNormal.y;

		return posY;
	}


	/*
	* ポリゴンとラインの当たり判定を取る.
	* @param :polyPosA,polyPosB,polyPosC　ポリゴンを形成する三点
	* 
	* @param :LinePosA,LinePosB			判定を取る線分の始点と終点
	* 
	* 
	* 
	*/
	bool HitPolyAndLine(const glm::vec3& polyPosA, const glm::vec3& polyPosB, glm::vec3& polyPosC, glm::vec3& LinePosA, const glm::vec3& LinePosB)
	{
		//法線を計算.
		glm::vec3 AB = polyPosB - polyPosA, AC = polyPosC - polyPosA;
		glm::vec3 vNormal = glm::normalize(glm::cross(AB, AC));
		//ポリゴンの
		return HitPolyAndLine(vNormal, polyPosA, LinePosA,LinePosB);
	}
	//法線とポリの一点と線分
	bool HitPolyAndLine(const glm::vec3& polyNormal,const glm::vec3& polyPos,const glm::vec3& LinePosA, const glm::vec3& LinePosB)
	{
		glm::vec3 vecA = LinePosA-polyPos;
		glm::vec3 vecB = LinePosB-polyPos;
		float A=glm::dot(polyNormal,vecA);
		float B=glm::dot(polyNormal, vecB);
		return (A*B)<0;
	}
}