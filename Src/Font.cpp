#include "Font.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include "FileNameData.h"

//シングルインスタンスの生成
Font& Font::Instance() {
	static Font instance;
	return instance;

}

//デストラクタ
Font::~Font() {

}


bool Font::Init() {
	if (isInitialize) {
		std::cout << "既に初期化されています" << std::endl;
		return false;
	}

	this->program.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_SIMPLE,FILENAME_SHADER_FRAG_SIMPLE));;
	const glm::mat4x4 matProj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
	const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->program.SetViewProjectionMatrix(matProj * matView);	
	this->texFont.Reset(Texture::LoadImage2D(FILENAME_TGA_FONTDOT));

	//mapを初期化する,
	//現在のフォントフォルダがこんな感じ,2/6
	const char fontsnum = 65;
	const char fonts[fontsnum] =
		"YZ7890! QRSTUVWXIJKLMNOPABCDEFGHyz123456qrstuvwxijklmnopabcdefgh";


	//位置文字づつマップに登録.
	for (int i = 0; i < fontsnum;++i) {
		fontMap.insert(std::make_pair(fonts[i],i));
	}
	//イニシャライズの確認..
	for (int i = 0; i < fontsnum; ++i) {
		std::cout << "文字(KEY)を表示:" << fonts[i];
		std::cout << "   そのKEYに対応する値を表示" << fontMap.at(fonts[i])<<std::endl;
	}
	

	this->isInitialize = true;
	return true;
}
/*
* ストリングの要素数だけ繰り返し,
* 現在テスト用で使用,
*/
void Font::AddString(std::string string ,const glm::vec3& t, const glm::vec3& r, const glm::vec3& s) {
	//初期化されていない場合は実行しない
	if (!isInitialize) {
		std::cout << "ERROR:初期化されてません:Font::AddString" << std::endl;
		return;
	}
	glDisable(GL_DEPTH_TEST);

	//描画するためにMeshListを取得
	MeshList& meshList = MeshList::Instance();
	this->program.Use();
	for (int i = 0; i < string.size(); ++i) {
		// HP表示.
		this->program.BindTexture(0, this->texFont.Get());
		this->program.Draw(meshList.GetMesh(fontMap.at(string[i]) + meshList.GetFontBegin()), t+( glm::vec3(12.0f,0.0f,0.0f) * s)*(float)i, r, s);

	}

}

/*
* 数字だって表示できてもいいじゃない!
* 
*/
void Font::AddString(int i, const glm::vec3& t, const glm::vec3& r, const glm::vec3& s) {
	//int型をstring型に変換する.
	std::ostringstream oss;
	oss << i;
	AddString(oss.str(),t,r,s);
}
int Font::MeshNum(const char)
{



	return 0;
}