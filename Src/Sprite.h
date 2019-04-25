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
* �ړI,2D�e�N�X�`����`�悷��,
* �ꖇ�̃e�N�X�`������͈͎w��Ő؂��肻���`�悷��,
*
* �Ƃ肠�����O�搶������Ă����݂����Ɉ��𖈃t���[���o�^���Ă������@���Ƃ�
*
*
*/
class SpriteRenderer;
class Sprite2D {
public:
	friend class SpriteRenderer;

	struct Rect;
	Sprite2D() = default;
	explicit Sprite2D(std::string);				//�t�@�C����o�^.
	Sprite2D(std::string,Rect,glm::vec3);		//�R���X�g���N�^.
	Sprite2D(std::string, glm::vec3);
	Sprite2D(std::string,Rect);

	void Update();					//�s�{�ӂȂ���K�v�ɂȂ���2/24
	void SetPos(const glm::vec3& newPos) { position = newPos; }
	void SetColor(glm::vec4* c) { color = c; }	//�d�l��ŐÓI�ɍ�����̂��Ƃ肠�����o�^���Ăق���.
	void SetRotate(const glm::vec3& rotate);
	void SetScale(const glm::vec3& scale);
	bool AnimActive();
	struct Rect
	{
		glm::vec2 origin;	//���_�̃e�N�X�`�����W
		glm::vec2 length;	//���_����̒���(�e�N�X�`�����W��),

		Rect() :origin(glm::vec2()),length(glm::vec2(1)) {};
	};
	void SetTweener(const glm::vec2& pos,float speed);
private:
	GLuint texId=0;			//�`��Ɏg�p����e�N�X�`��id;
	Rect rect;				//�`��Ɏg�p����e�N�X�`���̍��W,
	glm::vec3 position;
	glm::vec4* color;		//�`��.����ۂ̐F�𒲐�.
	std::unique_ptr<glm::vec3> rotate;
	std::unique_ptr<glm::vec3> scale;

	/*
	* �X�^�e�B�b�N�ɂ��ēc���搶�Ɏ��₵����,
	* Texture::Image2D�̃f�X�g���N�^�͂��ʂ�̂�?
	* A. ���C���֐��̌�ɂ����ƃf�X�g���N�^�ɒʂ�炵��.
	*/
	static std::map<std::string, Texture::Image2D> texList;  //�e�N�X�`���̖��O��id��R�t�����郊�X�g,key=filename
	GLuint CheckSameTexture(std::string);
	std::unique_ptr<Tweener::TweenAnimation> moveAnimptr;		//
};


/*
* 2D�X�v���C�g����肭�ł����̂Ŗ����߂܂���
*
* 3D�ł������悤�ɂ���Ă݂�.
*/
class Actor;		//�Q�Ƃ��邽�߂ɑO���錾.
class Sprite3D {
public:
	Sprite3D()=default;
	Sprite3D(std::string);

private:
	Actor* actorptr;
};

/* �`������ۂɍs���N���X
* �V���O���g���C���X�^���X
* 
*
*
*
*/
class SpriteRenderer {
public:
	static SpriteRenderer& Instance();

	bool Init();					//������.
	void Draw();					//�`�揈��,
	void AddSprite(Sprite2D*);		//�X�v���C�g�̓o�^,
	void AddSprite(Sprite3D*);


	void SetColor(const glm::vec4& c) { color = c; }
private:
	SpriteRenderer() = default;
	~SpriteRenderer();
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	MeshList& meshList = MeshList::Instance();	//�`�悷�邽�߂Ƀ��b�V�����X�g�̒ǉ�.
	Shader::Program program2D;		//2Dsprite�p�̃V�F�[�_�[,
	Shader::Program program3D;		//3Dsprite�p�̃V�F�[�_.
	std::vector<Sprite2D*> SpriteList2D;
	std::vector<Sprite3D*> SpriteList3D;
	
	glm::vec4 color;			//�X�v���C�g�S�̂̃J���[�𒲐�.
	void Draw2D();			//2D�X�v���C�g��`��,Draw�œ���.
	void Draw3D();			//3D�X�v���C�g��`��,Draw�œ���.

};




#endif // !SPRITE2D_H_INCLUDED
