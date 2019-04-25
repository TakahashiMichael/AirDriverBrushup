#include "Font.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include "FileNameData.h"

//�V���O���C���X�^���X�̐���
Font& Font::Instance() {
	static Font instance;
	return instance;

}

//�f�X�g���N�^
Font::~Font() {

}


bool Font::Init() {
	if (isInitialize) {
		std::cout << "���ɏ���������Ă��܂�" << std::endl;
		return false;
	}

	this->program.Reset(Shader::BuildFromFile(FILENAME_SHADER_VERT_SIMPLE,FILENAME_SHADER_FRAG_SIMPLE));;
	const glm::mat4x4 matProj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
	const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->program.SetViewProjectionMatrix(matProj * matView);	
	this->texFont.Reset(Texture::LoadImage2D(FILENAME_TGA_FONTDOT));

	//map������������,
	//���݂̃t�H���g�t�H���_������Ȋ���,2/6
	const char fontsnum = 65;
	const char fonts[fontsnum] =
		"YZ7890! QRSTUVWXIJKLMNOPABCDEFGHyz123456qrstuvwxijklmnopabcdefgh";


	//�ʒu�����Â}�b�v�ɓo�^.
	for (int i = 0; i < fontsnum;++i) {
		fontMap.insert(std::make_pair(fonts[i],i));
	}
	//�C�j�V�����C�Y�̊m�F..
	for (int i = 0; i < fontsnum; ++i) {
		std::cout << "����(KEY)��\��:" << fonts[i];
		std::cout << "   ����KEY�ɑΉ�����l��\��" << fontMap.at(fonts[i])<<std::endl;
	}
	

	this->isInitialize = true;
	return true;
}
/*
* �X�g�����O�̗v�f�������J��Ԃ�,
* ���݃e�X�g�p�Ŏg�p,
*/
void Font::AddString(std::string string ,const glm::vec3& t, const glm::vec3& r, const glm::vec3& s) {
	//����������Ă��Ȃ��ꍇ�͎��s���Ȃ�
	if (!isInitialize) {
		std::cout << "ERROR:����������Ă܂���:Font::AddString" << std::endl;
		return;
	}
	glDisable(GL_DEPTH_TEST);

	//�`�悷�邽�߂�MeshList���擾
	MeshList& meshList = MeshList::Instance();
	this->program.Use();
	for (int i = 0; i < string.size(); ++i) {
		// HP�\��.
		this->program.BindTexture(0, this->texFont.Get());
		this->program.Draw(meshList.GetMesh(fontMap.at(string[i]) + meshList.GetFontBegin()), t+( glm::vec3(12.0f,0.0f,0.0f) * s)*(float)i, r, s);

	}

}

/*
* ���������ĕ\���ł��Ă���������Ȃ�!
* 
*/
void Font::AddString(int i, const glm::vec3& t, const glm::vec3& r, const glm::vec3& s) {
	//int�^��string�^�ɕϊ�����.
	std::ostringstream oss;
	oss << i;
	AddString(oss.str(),t,r,s);
}
int Font::MeshNum(const char)
{



	return 0;
}