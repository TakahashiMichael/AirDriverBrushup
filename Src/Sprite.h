// @file Sprite2D.h


#ifndef SPRITE2D_H_INCLUDED
#define SPRITE2D_H_INCLUDED

#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>
#include <memory>
#include "TweenAnimation2D.h"


/*
* 目的,2Dテクスチャを描画する,
* 一枚のテクスチャから範囲指定で切り取りそれを描画する,
*
* とりあえず前先生がやっていたみたいに一つ一つを毎フレーム登録していく方法をとる
*
*
*/
class SpriteRenderer;
class Sprite2D {
public:
	friend class SpriteRenderer;

	struct Rect;
	Sprite2D() = default;
	explicit Sprite2D(std::string);				//ファイルを登録.
	Sprite2D(std::string,Rect,glm::vec3);		//コンストラクタ.
	Sprite2D(std::string, glm::vec3);
	Sprite2D(std::string,Rect);

	void Update();					//不本意ながら必要になった2/24
	void SetPos(const glm::vec3& newPos) { position = newPos; }
	void SetColor(glm::vec4* c) { color = c; }	//仕様先で静的に作ったのをとりあえず登録してほしい.
	void SetRotate(const glm::vec3& rotate);
	void SetScale(const glm::vec3& scale);
	bool AnimActive();
	struct Rect
	{
		glm::vec2 origin;	//原点のテクスチャ座標
		glm::vec2 length;	//原点からの長さ(テクスチャ座標で),

		Rect() :origin(glm::vec2()),length(glm::vec2(1)) {};
	};
	void SetTweener(const glm::vec2& pos,float speed);
private:
	GLuint texId=0;			//描画に使用するテクスチャid;
	Rect rect;				//描画に使用するテクスチャの座標,
	glm::vec3 position;
	glm::vec4* color;		//描画.する際の色を調整.
	std::unique_ptr<glm::vec3> rotate;
	std::unique_ptr<glm::vec3> scale;

	/*
	* スタティックについて田中先生に質問したい,
	* Texture::Image2Dのデストラクタはいつ通るのか?
	* A. メイン関数の後にちゃんとデストラクタに通るらしい.
	*/
	static std::map<std::string, Texture::Image2D> texList;  //テクスチャの名前とidを紐付けするリスト,key=filename
	GLuint CheckSameTexture(std::string);
	std::unique_ptr<Tweener::TweenAnimation> moveAnimptr;		//
};


/*
* 2Dスプライトが上手くできたので味を占めました
*
* 3Dでも同じようにやってみる.
*/
class Actor;		//参照するために前方宣言.
class Sprite3D {
public:
	Sprite3D()=default;
	Sprite3D(std::string);

private:
	Actor* actorptr;
};

/* 描画を実際に行うクラス
* シングルトンインスタンス
* 
*
*
*
*/
class SpriteRenderer {
public:
	static SpriteRenderer& Instance();

	bool Init();					//初期化.
	void Draw();					//描画処理,
	void AddSprite(Sprite2D*);		//スプライトの登録,
	void AddSprite(Sprite3D*);


	void SetColor(const glm::vec4& c) { color = c; }
private:
	SpriteRenderer() = default;
	~SpriteRenderer();
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	MeshList& meshList = MeshList::Instance();	//描画するためにメッシュリストの追加.
	Shader::Program program2D;		//2Dsprite用のシェーダー,
	Shader::Program program3D;		//3Dsprite用のシェーダ.
	std::vector<Sprite2D*> SpriteList2D;
	std::vector<Sprite3D*> SpriteList3D;
	
	glm::vec4 color;			//スプライト全体のカラーを調整.
	void Draw2D();			//2Dスプライトを描画,Drawで統一.
	void Draw3D();			//3Dスプライトを描画,Drawで統一.

};




#endif // !SPRITE2D_H_INCLUDED
