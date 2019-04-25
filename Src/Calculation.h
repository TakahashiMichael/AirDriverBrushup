#pragma once
#define _USE_MATH_DEFINES
#include <math.h> //原田さん
#include "GLFWEW.h" //初期化の準備
#include <glm/matrix.hpp>


namespace Cal{
	float radian(float angle);
	float angle(float radian);
	float hypotenuse(glm::vec3,glm::vec3);//二点の距離を求めてフロートで返す.
	glm::vec3 vectorAB(glm::vec3, glm::vec3);//AからBへのベクトルを求める.
	glm::vec3 scatterPos(glm::vec3 pos,float distance);//ランダムで-dis~disをx,y別々に足す
	float RorL(float);//50%の確率でマイナスをかける.
	float speed(float, float);//距離÷速さ,
	bool circleCollision(glm::vec3,glm::vec3,float A,float B);//二つの衝突判定.を調べる.
	bool circleCollision(glm::vec3,glm::vec3,float AandB);//二つの衝突判定.を調べる.
	bool circleCollision(float distance,float A,float B);//二つの衝突判定.を調べる.
	bool circleCollision(float distance,float AandB);//二つの衝突判定.を調べる.
	bool runTimer(float timer, float deltatime, float settimer);
	bool runTimer(float timer,float deltatime);//タイマーからデルタタイムだけを減らす.
	float thetaAB(glm::vec3 posA, glm::vec3 posB);//posAに対するposBのΘ角度を調べてfloatで返す.

	glm::vec3 destination(glm::vec3 pos ,float distance,float radian);//posから長さと角度を入力して目的地の座標glm::vec3を求める

	bool clossProduct(glm::vec3 vecA,glm::vec3 vecB ,glm::vec3 posC);//vecABに対する点C外積を調べる.ベクトルに対して点が上ならtrue
	//↑のXZver;
	bool crossProductXZ(const glm::vec3& vecA, const glm::vec3& vecB, const glm::vec3& posC);

	//ポリゴンとある座標からその高さを求める.
	float HeightOfPolygon(const glm::vec3& polyPosA, const glm::vec3& polyPosB, const glm::vec3& polyPosC, glm::vec3& checkPos);
	//ポリゴンの法線がわかっている場合.
	float HeightOfPolygon(const glm::vec3& polyNormal, const glm::vec3& polyPos, const glm::vec3& checkPos);

	//ポリゴンと直線の当たり判定
	bool HitPolyAndLine(const glm::vec3& polyPosA, const glm::vec3& polyPosB, glm::vec3& polyPosC, glm::vec3& LinePosA,const glm::vec3& LinePosB);
	//法線とポリの一点と線分
	bool HitPolyAndLine(const glm::vec3& polyNormal,const glm::vec3& polyPos,const glm::vec3& LinePosA, const glm::vec3& LinePosB);
};
