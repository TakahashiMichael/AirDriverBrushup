// @file Font.h

#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "MeshList.h"
#include "Shader.h"
#include <string>
#include <map>
#include "Texture.h"
/*
* simpleshaderと meshlistから文字を表示する
*
*
* Selectとかで使おうと思った結果staticシングルトンにすることにした,2/10
*/

class Font {
public:
	static Font& Instance();

	void AddString(std::string s ,const glm::vec3&,const glm::vec3&,const glm::vec3&);
	void AddString(int, const glm::vec3&, const glm::vec3&, const glm::vec3&);//とりあえず数字にも対応
	bool Init();
private:
	Font() = default;
	~Font();
	Font(const Font&)=delete;
	Font& operator=(const Font&) = delete;

	Shader::Program program;		//シーンで使用しているsimpleprogramを登録する
	bool isInitialize = false;			    //イニシャライズが完了しているかどうか.
	std::map<char, int> fontMap;			//入力した文字から添え字番号を割り出す為のマップ型.
	int MeshNum(const char c);				//文字からしようするmeshリストナンバーを特定する(位置文字単位)
	
	Texture::Image2D texFont;				//フォントを描画するためのテクスチャ,多分今はこれで固定,
};



#endif // !FONT_H_INCLUDED