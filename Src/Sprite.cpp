#include "Sprite.h"
#include <iostream>
#include "Actor.h"
#include "FileNameData.h"


std::map<std::string,Texture::Image2D> Sprite2D::texList;


/*
* �����ς��R���X�g���N�^���邯��ǂƂ肠����filename��������Α��͌ォ��ݒ�ł���
* 
* @param filename:	�e�N�X�`�����쐬����t�@�C��
* @param rect:		�����e�N�X�`������͈͐؂��������Ȃ�ݒ�.
* @param position;  ��ʏ�ɕ\������ʒu���.
*
* (* *)<<���������X�g�ŋ�����.
*
* ����,rect�̃e�N�X�`�����W�͎��͂Ōv�Z���Ď���͂ł��肢���܂�<<�g���˂�...
*/
Sprite2D::Sprite2D(std::string fn):Sprite2D(fn,Rect(),glm::vec3()) {}
Sprite2D::Sprite2D(std::string fn,Rect rect):Sprite2D(fn,rect,glm::vec3()) {}
Sprite2D::Sprite2D(std::string fn,glm::vec3 pos):Sprite2D(fn,Rect(),pos) {}
Sprite2D::Sprite2D(std::string filename,Rect rec,glm::vec3 pos):rect(rec),
position(pos), texId(CheckSameTexture(filename)) {
	this->color = nullptr;	//�J���[�ɂ�null��ݒ�.�K�v�Ȃ���Ă��Ċ���.
}


/*
* �e�N�X�`�����d�ɍ��Ȃ��悤�Ɋm�F����
* ���Ƀt�@�C����ǂݍ���ł���ꍇ�̓e�N�X�`�����쐬���Ȃ�
*
*/
GLuint Sprite2D::CheckSameTexture(std::string filename) {
	if (texList.count(filename)) {
		std::cout << "Sprite2D::CheckSameTexture ���ɓǂݍ��ݍς̃e�N�X�`���ł�: " << filename << std::endl;
	}
	else
	{
		texList.insert(std::make_pair(filename,Texture::Image2D()));
		texList.at(filename).Reset(Texture::LoadImage2D(filename.c_str()));
	}
	return texList.at(filename).Get();
}

/*
* ��]��ݒ�.�����ݒ肳��Ă��Ȃ��Ȃ�V���ɐݒ肷��.
* @param rotate :��]
*/
void Sprite2D::SetRotate(const glm::vec3& rotate) {
	//���Ɏ��Ԃ�����Ώ㏑��
	if(this->rotate) {
		*this->rotate = rotate;
	}
	else {
		this->rotate.reset(new glm::vec3(rotate));
	}
}
/*
* �g��k����ݒ�,�����ݒ肳��Ă��Ȃ��Ȃ�new
* @param scale :�g��k��
*/
void Sprite2D::SetScale(const glm::vec3& scale) {
	//���Ɏ��Ԃ�����Ȃ�㏑��
	if (this->scale) {
		*this->scale = scale;
	}//�Ȃ��Ȃ瓮�I�Ɋm��.
	else {
		this->scale.reset(new glm::vec3(scale));
	}

}

/*
* Update
*
* �A�j���[�V������ݒ肵�Ă���̂ł���Ύg��/
*
*
*/
void Sprite2D::Update() {
	if (moveAnimptr) {
		moveAnimptr->Update();
	}
	////�����A�j���[�V�������I����Ă���Ȃ�A�j���[�V�������������
	//if (!moveAnimptr->GetActive()) {
	//	moveAnimptr.reset();
	//}
}

/*
* �A�j���[�V������ݒ肷��
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
* �A�j���[�V�������ݒ肳��Ă��邩�ǂ���
* 
* @retval	true: �ݒ肳��Ă���,
* @retval	false: �ݒ肳��Ă��Ȃ�,
*/
bool Sprite2D::AnimActive() {
	return moveAnimptr->GetActive();
}

/*
*�V���O���g���C���X�^���X�̐���.
*
*
*/
SpriteRenderer& SpriteRenderer::Instance()
{
	static SpriteRenderer instance;
	return instance;
}


/*
* �������֐�
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
//�f�X�g���N�^.
SpriteRenderer::~SpriteRenderer()
{

}


/*
* �X�v���C�g��ǉ�����
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
* �X�v���C�g��`�悷��.
*
* ���t���[���`�悷��e�N�X�`���͍폜�����
*
* ����x���ǂ��t���ĂȂ��ĂƂ肠�������̃V�[����mesh�������Ŏg��.�ł���Ή��P������
*/
void SpriteRenderer::Draw()
{
	Draw2D();
	//Draw3d();
}

//2D�X�v���C�g��`�悷��.
void SpriteRenderer::Draw2D() {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	program2D.Use();

	for (int i = 0; i < SpriteList2D.size(); ++i) {
		program2D.SetUniColor(color);	//�X�v���C�g�̐�������邱�ƂɂȂ邯���.
		//���M����s����쐬.
		glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(SpriteList2D[i]->rect.origin, 0));
		glm::mat4 matTex = glm::scale(t, glm::vec3(SpriteList2D[i]->rect.length, 1));
		program2D.SetTextureMatrix(matTex);//�e�N�X�`���ɍs����V�F�[�_�ɓ]��.

		program2D.BindTexture(0, SpriteList2D[i]->texId);
		//�����X�v���C�g�ɃJ���[���ݒ肳��Ă���̂ł���΃V�F�[�_�ɑ���t����
		if (SpriteList2D[i]->color != nullptr) {
			program2D.SetUniColor(*SpriteList2D[i]->color);
		}
		//�����X�v���C�g�ɑ傫�����]���ݒ肳��Ă���̂ł���΂�����g�p����
		glm::vec3 rotation = SpriteList2D[i]->rotate != nullptr ? *SpriteList2D[i]->rotate : glm::vec3(0);
		glm::vec3 scale = SpriteList2D[i]->scale != nullptr ? *SpriteList2D[i]->scale : glm::vec3(2);
		program2D.Draw(meshList[meshList.GetSprite2D()], SpriteList2D[i]->position, rotation, scale);

	}

	SpriteList2D.clear();
}


