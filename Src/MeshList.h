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
* メッシュ管理クラス.
*/
class MeshList
{
public:
	//シングルトン
	static MeshList& Instance();

  bool Allocate();
  bool Allocate(const std::vector<std::string>&);
  void Free();
  void Add(const Vertex* vBegin, const Vertex* vEnd, const GLushort* iBegin, const GLushort* iEnd);
  bool AddFromObjFile(const char* filename);


  void BindVertexArray();
  const Mesh& operator[](size_t index) const;
  const Mesh& GetMesh(int)const;				//上の関数版.
  const Mesh& GetMesh(std::string)const;		//上のファイル名検索.
  void VertexTest(glm::vec3 scale);//テスト.
  glm::vec3& GetVertex(int num);//テスト.
  int GetIndices(int num);//テスト.
  std::vector<Vertex> tmpVertices;
  std::vector<GLushort> tmpIndices;
  int GetFontBegin() { return this->FontBegin; }
  int GetSprite2D() { return sprite2D; }
private:
	MeshList();
	~MeshList();
	MeshList(const MeshList&) = delete;
	MeshList& operator=(const MeshList&) = delete;

	void AddFontVertex();//フォントに使う頂点データをバッファーに登録,
	void AddSprite2DVertex();		//スプライトに使う頂点データの登録.

  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint ibo = 0;
  std::vector<Mesh> meshes;
  unsigned int FontBegin=0;			//メッシュリストに登録したフォントで使うデータの先頭の添え字番号
  unsigned int sprite2D = 0;		//メッシュリストに登録したスプライトで使う以下略.
  std::map<std::string, unsigned int> meshId;		//メッシュリストに登録した以下略を名前で記録.

};

#endif // MESHLIST_H_INCLUDED