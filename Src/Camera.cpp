#include "Camera.h"
#include <iostream>
#include "GLFWEW.h"



//distanceの加算
void Camera::AddDistance(float f) {
	this->distance += f;
	this->calucNormal();
}


/*
* カメラのポジションを計算して返す.
*
*
*
*
*/
const glm::vec3& Camera::GetPos()
{
	calucPos();//カメラの位置を再計算.

	//std::cout << "バグチェックyの回転:" << this->rotate.y << std::endl;

	return this->position;
}

//最後

glm::vec3 Camera::normalXZ()
{

	return normalXZ(0.0f);
}
glm::vec3 Camera::normalXZ(float angle) {

	//normalがプレイヤーからカメラの法線なので正負を逆に.
	glm::vec3 xz = -(normal);
	//y成分を0にして正規化して回転,最後に単位ベクトルに;
	xz.y = 0;

	xz = glm::rotate(glm::mat4x4(1), glm::radians(angle), glm::vec3(0, 1, 0)) * glm::vec4(xz, 1);


	return glm::normalize(xz);

}

/*
* 現在のカメラclassが持ってる値からカメラの位置を計算します.
* distanceの幅制限などはここで調整する.
*/
void Camera::calucPos() {
	//distanceが0以下なら0.1に戻す.
	if (distance <= 0) {
		distance = 0.1f;
	}


	this->position = (normal * distance) + (*targetPos);
}

//Y軸回転(法線),引数オイラー角
void Camera::normalRotateY(float angle) {

	rotate.y += angle;
	this->resetRotate();
	this->calucNormal();
}
//Y軸回転(法線),引数オイラー角
void Camera::normalRotateX(float angle) {

	rotate.x += angle;
	this->resetRotate();
	this->calucNormal();
}

void Camera::resetRotate() {
	//xの回転軸が大きすぎるとカメラがバグるので調整.
	if (this->rotate.x > 89.0f)
	{
		std::cout << "問題点x1" << std::endl;
		this->rotate.x = 89.0f;
	}
	else if (this->rotate.x < -89.0f)
	{

		std::cout << "問題点x-1" << std::endl;
		this->rotate.x = -89.0f;
	}

	//オイラー角なので,yが180を超えた時に-180にする

	if (this->rotate.y > 180.0f)
	{

		std::cout << "問題点y1" << std::endl;
		this->rotate.y -= 360.0f;
	}
	else if (this->rotate.y < -180.0f)
	{
		std::cout << "問題点y-1" << std::endl;
		this->rotate.y += 360.0f;
	}
}

void Camera::calucNormal() {
	//x回転,y,回転を計算 z回転は意味が
	//const glm::mat4 matRotateX = glm::rotate(glm::mat4(1), glm::radians(rotate.x), glm::vec3(1, 0, 0));
	//const glm::mat4 matRotateXY = glm::rotate(matRotateX, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateYX = glm::rotate(matRotateY, glm::radians(rotate.x), glm::vec3(1, 0, 0));

	this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}



















//----------------------------------------------こっから下がtpsカメラ.




void Camera2::resetRotate() {
	//xの回転軸が大きすぎるとカメラがバグるので調整.
	if (this->rotate.x > 75.0f)
	{
		std::cout << "問題点x1" << std::endl;
		this->rotate.x = 75.0f;
	}
	else if (this->rotate.x < -30.0f)
	{

		std::cout << "問題点x-1" << std::endl;
		this->rotate.x = -30.0f;
	}

	//オイラー角なので,yが180を超えた時に-180にする

	if (this->rotate.y > 180.0f)
	{

		std::cout << "問題点y1" << std::endl;
		this->rotate.y -= 360.0f;
	}
	else if (this->rotate.y < -180.0f)
	{
		std::cout << "問題点y-1" << std::endl;
		this->rotate.y += 360.0f;
	}
}
//distanceの加算
void Camera2::AddDistance(float f) {
	this->distance += f;
}
void Camera2::calucNormal() {
	//x回転,y,回転を計算 z回転は意味が
	//const glm::mat4 matRotateX = glm::rotate(glm::mat4(1), glm::radians(rotate.x), glm::vec3(1, 0, 0));
	//const glm::mat4 matRotateXY = glm::rotate(matRotateX, glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotate.y), glm::vec3(0, 1, 0));
	const glm::mat4 matRotateYX = glm::rotate(matRotateY, glm::radians(rotate.x), glm::vec3(1, 0, 0));

	this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}

glm::vec3 Camera2::ViewPoint() {

	return this->normal*this->distance;

}





//-----------------------以下PlayerCamera-------------------------

//コンストラクタ.
PlayerCamera::PlayerCamera(glm::vec3* playerPosPtr,glm::vec3* playerDirPtr):playerPos(playerPosPtr),playerDir(playerDirPtr){}


/*
* 入力処理
*
*
*
*/
void PlayerCamera::ProcessInput() {
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime = window.DeltaTime();
	//入力方向によって徐々にカメラを動かす
	if (window.GetCommand(GLFWEW::Window::COMMANDLIST_RIGHT_PRESS)) {
		//反対側に傾いているなら無入力と同じスピードで戻す
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
		//反対側に傾いているなら無入力と同じスピードで戻す
		if (rotateTC.y > 0) {
			rotateTC.y += -60.0f*deltaTime;
		}
		else {
			rotateTC.y += -30.0*deltaTime;
			if (rotateTC.y <= -maxRotateY) {
				rotateTC.y = -maxRotateY;
			}
		}
	}//どちらも入力されていないならyを戻す
	else {
		if (rotateTC.y != 0) {
			if (rotateTC.y > 0) {
				rotateTC.y -=60.0f*deltaTime;
			}
			else if (rotateTC.y < 0) {
				rotateTC.y -= -60.0f*deltaTime;

			}

			//値が小さいのなら0にする.
			if (rotateTC.y <= 1.0f && rotateTC.y >= -1.0f) {
				rotateTC.y = 0;
			}
		}
	}
}

/*
* 更新処理
*
*/
void PlayerCamera::Update() {
	//UpdateといえばdeltaTimeっしょ？
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	float deltaTime=window.DeltaTime();

	//計算関数実行.
	this->TarPosUpdate();
	this->NormalTCUpdate();
	this->PosUpdate();
}

/*
* ゲッター(Position)
*/
const glm::vec3& PlayerCamera::Pos() {
	return this->position;
}

/*
* ターゲット(注視点)の座標を計算する
*
*
*/
const glm::vec3& PlayerCamera::TargetPos() {

	return this->targetPos;
}

/*
* 注視点の計算
*
* 登録してあるプレイヤーの位置と進行方向+自身のdistansPT
* からワールド座標を計算してtargetPosを更新
*/
void PlayerCamera::TarPosUpdate() {
	//注視点=(プレイヤーのワールド座標)+(Pの進行方向法線)*(長さ)
	targetPos = (*playerPos) + ((*playerDir)* distancePT);
}

/*
* 注視点からカメラへの法線を計算
*
*/
void PlayerCamera::NormalTCUpdate() {
	glm::vec3 normalTP = (-*playerDir);		//混乱しないようにとりあえず注視点からプレイヤーの法線
	normalTP.y = 0;
	normalTP = glm::normalize(normalTP);
	const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), glm::radians(rotateTC.y), glm::vec3(0, 1, 0));
	//まずYで回転させてxz平面の法線vecTCを出す,
	glm::vec3 normalTCxz = matRotateY * glm::vec4(normalTP,1);	

	//なんか多分これで回転軸axisが出る気がするテスト
	glm::vec3 axis = glm::normalize(glm::cross(normalTCxz,glm::vec3(0,1,0)));
	const glm::mat4 matRotateX = glm::rotate(matRotateY, glm::radians(rotateTC.x), axis);

	//合ってるか一番怪しいところなので要検証
	this->normalTC = matRotateX * glm::vec4(normalTCxz,1);
	//this->normal = matRotateYX * glm::vec4(0, 0, 1, 1);
}

/*
* Positionの計算
*
*/
void PlayerCamera::PosUpdate() {
	//カメラの位置=注視点(ワールド座標)+(法線TC*長さ)
	this->position = targetPos + (normalTC * distanceCT);

}