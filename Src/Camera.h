//TPSカメラクラス

#ifndef CAMERA_H_INCLUDET
#define CAMERA_H_INCLUDET
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
	Camera() = default;
	Camera(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distanceに加算.
	const glm::vec3& GetPos();				//カメラのポジションを返す.
	glm::vec3 normalXZ();					//XZ平面上のカメラからプレイヤーに向かう法線を取得.
	glm::vec3 normalXZ(float angle);		//↑の回転ver :引数はオイラー角
	void normalRotateY(float angle);		//Y軸回転(法線),引数オイラー角	
	void normalRotateX(float angle);		//Y軸回転(法線),引数オイラー角
private:
	const glm::vec3* targetPos;			//対象となるキャラクターのポインタ
	glm::vec3 position;					//カメラのポジション
	glm::vec3 normal;					//対象からカメラに向かう法線ヴェクトル
	float distance;						//対象からカメラまでの距離
	glm::vec3 rotate=glm::vec3(0);		//カメラの回転角の各成分.(オイラー角),(z軸は設定してない)
	void calucPos();					//targetPos,position,normal からカメラのポジションを計算する.
	void calucNormal();					//rotate情報からnormalを再計算する.
	void resetRotate();					//rotateの値を修正する.

};

//fpsカメラテスト
class Camera2 {
public:
	Camera2() = default;
	Camera2(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distanceに加算.
	const glm::vec3& GetPos();				//カメラのポジションを返す.
	glm::vec3 ViewPoint();					//注視点を返す
	glm::vec3 normalXZ();					//XZ平面上のカメラからプレイヤーに向かう法線を取得.
	glm::vec3 normalXZ(float angle);		//↑の回転ver :引数はオイラー角
	void normalRotateY(float angle);		//Y軸回転(法線),引数オイラー角	
	void normalRotateX(float angle);		//Y軸回転(法線),引数オイラー角
private:
	const glm::vec3* targetPos;			//対象となるキャラクターのポインタ
	glm::vec3 position;					//カメラのポジション
	glm::vec3 normal;					//対象からカメラに向かう法線ヴェクトル
	float distance;						//対象からカメラまでの距離
	glm::vec3 rotate = glm::vec3(0);	//カメラの回転角の各成分.(オイラー角),(z軸は設定してない)
	void calucPos();					//targetPos,position,normal からカメラのポジションを計算する.
	void calucNormal();					//rotate情報からnormalを再計算する.
	void resetRotate();					//rotateの値を修正する.

};



//プレイヤーの前方を
class Camera3 {
public:
	Camera3() = default;
	Camera3(glm::vec3* target, float dist) :targetPos(target), distance(dist) {
		calucNormal();
	};

	void AddDistance(float f);				//distanceに加算.
	const glm::vec3& GetPos();				//カメラのポジションを返す.
	glm::vec3& SetPos();					//
	glm::vec3 normalXZ();					//XZ平面上のカメラからプレイヤーに向かう法線を取得.
	glm::vec3 normalXZ(float angle);		//↑の回転ver :引数はオイラー角
	void normalRotateY(float angle);		//Y軸回転(法線),引数オイラー角	
	void normalRotateX(float angle);		//Y軸回転(法線),引数オイラー角
private:	
	const glm::vec3* targetPos;			//対象となるキャラクターのポインタ
	glm::vec3 position;					//カメラのポジション
	glm::vec3 normal;					//対象からカメラに向かう法線ヴェクトル
	float distance;						//対象からカメラまでの距離
	glm::vec3 rotate = glm::vec3(0);	//カメラの回転角の各成分.(オイラー角),(z軸は設定してない)
	void calucPos();					//targetPos,position,normal からカメラのポジションを計算する.
	void calucNormal();					//rotate情報からnormalを再計算する.
	void resetRotate();					//rotateの値を修正する.

};


/*
* 本番 遊びは終わりだ(∩ ∩)
*
* 色々考えた結果カメラはプレイヤーに持たせるのが一番いい気がする
* とりあえず作って考える2/10
*
* カメラ仕様はプレイヤーの進行方向に注視点
*
* 基本はプレイヤーの後ろから注視点を見るが入力によってはすこし
* 回転した位置から注視点をみることもある
*/
class PlayerCamera {
public:
	PlayerCamera() = default;
	PlayerCamera(glm::vec3*,glm::vec3*);

	void ProcessInput();					//入力
	void Update();							//更新
	const glm::vec3& Pos();					//ゲッターマン
	const glm::vec3& TargetPos();			//注視点.

private:
	glm::vec3 position;						//カメラの座標
	glm::vec3 targetPos;					//注視点
	glm::vec3 normalTC;						//注視点からカメラへの法線
	glm::vec3 rotateTC=glm::vec3(20,0,0);					//vecTPを基準にした時のvecTCに対するオイラー回転角Y(水平),X(垂直).(Zは0で)
	glm::vec3* playerPos=nullptr;			//対象のプレイヤーの座標.
	glm::vec3* playerDir=nullptr;			//対象のプレイヤーの進行方向

	float maxRotateY = 15.0f;				//角度が変わる限界
	float distancePT=5.0f;					//プレイヤーから注視点の距離/
	float distanceCT=15.0f;					//カメラから注視点の距離.



	void TarPosUpdate();					//注視点を計算する.
	void NormalTCUpdate();					//注視点からカメラへの法線を計算.
	void PosUpdate();

};

#endif // !CAMERA_H_INCLUDET
