#include "Sprite.h"
#include <iostream>
#include "Actor.h"
#include "FileNameData.h"


std::map<std::string,Texture::Image2D> Sprite2D::texList;


/*
* いっぱいコンストラクタあるけれどとりあえずfilenameさえあれば他は後から設定できる
* 
* @param filename:	テクスチャを作成するファイル
* @param rect:		もしテクスチャから範囲切り取りをするなら設定.
* @param position;  画面上に表示する位置情報.
*
* (* *)<<初期化リスト最強かよ.
*
* 現在,rectのテクスチャ座標は自力で計算して手入力でお願いします<<使えねえ...
*/
Sprite2D::Sprite2D(std::string fn):Sprite2D(fn,Rect(),glm::vec3()) {}
Sprite2D::Sprite2D(std::string fn,Rect rect):Sprite2D(fn,rect,glm::vec3()) {}
Sprite2D::Sprite2D(std::string fn,glm::vec3 pos):Sprite2D(fn,Rect(),pos) {}
Sprite2D::Sprite2D(std::string filename,Rect rec,glm::vec3 pos):rect(rec),
position(pos), texId(CheckSameTexture(filename)) {
	this->color = nullptr;	//カラーにはnullを設定.必要ならつけてって感じ.
}


/*
* テクスチャを二重に作らないように確認する
* 既にファイルを読み込んでいる場合はテクスチャを作成しない
*
*/
GLuint Sprite2D::CheckSameTexture(std::string filename) {
	if (texList.count(filename)) {
		std::cout << "Sprite2D::CheckSameTexture 既に読み込み済のテクスチャです: " << filename << std::endl;
	}
	else
	{
		texList.insert(std::make_pair(filename,Texture::Image2D()));
		texList.at(filename).Reset(Texture::LoadImage2D(filename.c_str()));
	}
	return texList.at(filename).Get();
}

/*
* 回転を設定.もし設定されていないなら新たに設定する.
* @param rotate :回転
*/
void Sprite2D::SetRotate(const glm::vec3& rotate) {
	//既に実態があれば上書き
	if(this->rotate) {
		*this->rotate = rotate;
	}
	else {
		this->rotate.reset(new glm::vec3(rotate));
	}
}
/*
* 拡大縮小を設定,もし設定されていないならnew
* @param scale :拡大縮小
*/
void Sprite2D::SetScale(const glm::vec3& scale) {
	//既に実態があるなら上書き
	if (this->scale) {
		*this->scale = scale;
	}//ないなら動的に確保.
	else {
		this->scale.reset(new glm::vec3(scale));
	}

}

/*
* Update
*
* アニメーションを設定しているのであれば使う/
*
*
*/
void Sprite2D::Update() {
	if (moveAnimptr) {
		moveAnimptr->Update();
	}
	////もしアニメーションが終わっているならアニメーションを解放する
	//if (!moveAnimptr->GetActive()) {
	//	moveAnimptr.reset();
	//}
}

/*
* アニメーションを設定する
*
* @param	
* @param 
*
*/
void Sprite2D::SetTweener(const glm::vec2& dir,float speed) {
	moveAnimptr.release();
	moveAnimptr.reset(new Tweener::Linear(this->position,dir,speed));

}
/*
* アニメーションが設定されているかどうか
* 
* @retval	true: 設定されている,
* @retval	false: 設定されていない,
*/
bool Sprite2D::AnimActive() {
	return moveAnimptr->GetActive();
}

/*
*シングルトンインスタンスの生成.
*
*
*/
SpriteRenderer& SpriteRenderer::Instance()
{
	static SpriteRenderer instance;
	return instance;
}


/*
* 初期化関数
*
*
*
*
*/
bool SpriteRenderer::Init()
{
	program2D.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_2DSPRITE, FILENAME_SHADER_FRAG_2DSPRITE));
	color = glm::vec4(1, 1, 1, 1);

	return true;
}
//デストラクタ.
SpriteRenderer::~SpriteRenderer()
{

}


/*
* スプライトを追加する
*
* 
*
*/
void SpriteRenderer::AddSprite(Sprite2D* spriteprt)
{
	SpriteList2D.push_back(spriteprt);

}
void SpriteRenderer::AddSprite(Sprite3D* spriteptr)
{
	SpriteList3D.push_back(spriteptr);
}

/*
* スプライトを描画する.
*
* 毎フレーム描画するテクスチャは削除するの
*
* 理解度が追い付いてなくてとりあえずそのシーンのmeshを引数で使う.できれば改善したい
*/
void SpriteRenderer::Draw()
{
	Draw2D();
	//Draw3d();
}

//2Dスプライトを描画する.
void SpriteRenderer::Draw2D() {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	program2D.Use();

	for (int i = 0; i < SpriteList2D.size(); ++i) {
		program2D.SetUniColor(color);	//スプライトの数だけやることになるけれど.
		//送信する行列を作成.
		glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(SpriteList2D[i]->rect.origin, 0));
		glm::mat4 matTex = glm::scale(t, glm::vec3(SpriteList2D[i]->rect.length, 1));
		program2D.SetTextureMatrix(matTex);//テクスチャに行列をシェーダに転送.

		program2D.BindTexture(0, SpriteList2D[i]->texId);
		//もしスプライトにカラーが設定されているのであればシェーダに送り付ける
		if (SpriteList2D[i]->color != nullptr) {
			program2D.SetUniColor(*SpriteList2D[i]->color);
		}
		//もしスプライトに大きさや回転が設定されているのであればそれを使用する
		glm::vec3 rotation = SpriteList2D[i]->rotate != nullptr ? *SpriteList2D[i]->rotate : glm::vec3(0);
		glm::vec3 scale = SpriteList2D[i]->scale != nullptr ? *SpriteList2D[i]->scale : glm::vec3(2);
		program2D.Draw(meshList[meshList.GetSprite2D()], SpriteList2D[i]->position, rotation, scale);

	}

	SpriteList2D.clear();
}


