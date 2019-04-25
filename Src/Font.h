// @file Font.h

#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "MeshList.h"
#include "Shader.h"
#include <string>
#include <map>
#include "Texture.h"
/*
* simpleshader�� meshlist���當����\������
*
*
* Select�Ƃ��Ŏg�����Ǝv��������static�V���O���g���ɂ��邱�Ƃɂ���,2/10
*/

class Font {
public:
	static Font& Instance();

	void AddString(std::string s ,const glm::vec3&,const glm::vec3&,const glm::vec3&);
	void AddString(int, const glm::vec3&, const glm::vec3&, const glm::vec3&);//�Ƃ肠���������ɂ��Ή�
	bool Init();
private:
	Font() = default;
	~Font();
	Font(const Font&)=delete;
	Font& operator=(const Font&) = delete;

	Shader::Program program;		//�V�[���Ŏg�p���Ă���simpleprogram��o�^����
	bool isInitialize = false;			    //�C�j�V�����C�Y���������Ă��邩�ǂ���.
	std::map<char, int> fontMap;			//���͂�����������Y�����ԍ�������o���ׂ̃}�b�v�^.
	int MeshNum(const char c);				//�������炵�悤����mesh���X�g�i���o�[����肷��(�ʒu�����P��)
	
	Texture::Image2D texFont;				//�t�H���g��`�悷�邽�߂̃e�N�X�`��,�������͂���ŌŒ�,
};



#endif // !FONT_H_INCLUDED