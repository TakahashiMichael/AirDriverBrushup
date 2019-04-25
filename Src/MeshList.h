/**
* @file MeshList.h
*/
#ifndef MESHLIST_H_INCLUDED
#define MESHLIST_H_INCLUDED
#include <GL/glew.h>
#include "Geometry.h"
#include <vector>
#include <string>
#include <glm/matrix.hpp>
#include <map>

/**
* ���b�V���Ǘ��N���X.
*/
class MeshList
{
public:
	//�V���O���g��
	static MeshList& Instance();

  bool Allocate();
  bool Allocate(const std::vector<std::string>&);
  void Free();
  void Add(const Vertex* vBegin, const Vertex* vEnd, const GLushort* iBegin, const GLushort* iEnd);
  bool AddFromObjFile(const char* filename);


  void BindVertexArray();
  const Mesh& operator[](size_t index) const;
  const Mesh& GetMesh(int)const;				//��̊֐���.
  const Mesh& GetMesh(std::string)const;		//��̃t�@�C��������.
  void VertexTest(glm::vec3 scale);//�e�X�g.
  glm::vec3& GetVertex(int num);//�e�X�g.
  int GetIndices(int num);//�e�X�g.
  std::vector<Vertex> tmpVertices;
  std::vector<GLushort> tmpIndices;
  int GetFontBegin() { return this->FontBegin; }
  int GetSprite2D() { return sprite2D; }
private:
	MeshList();
	~MeshList();
	MeshList(const MeshList&) = delete;
	MeshList& operator=(const MeshList&) = delete;

	void AddFontVertex();//�t�H���g�Ɏg�����_�f�[�^���o�b�t�@�[�ɓo�^,
	void AddSprite2DVertex();		//�X�v���C�g�Ɏg�����_�f�[�^�̓o�^.

  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint ibo = 0;
  std::vector<Mesh> meshes;
  unsigned int FontBegin=0;			//���b�V�����X�g�ɓo�^�����t�H���g�Ŏg���f�[�^�̐擪�̓Y�����ԍ�
  unsigned int sprite2D = 0;		//���b�V�����X�g�ɓo�^�����X�v���C�g�Ŏg���ȉ���.
  std::map<std::string, unsigned int> meshId;		//���b�V�����X�g�ɓo�^�����ȉ����𖼑O�ŋL�^.

};

#endif // MESHLIST_H_INCLUDED