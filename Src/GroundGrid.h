//ポリゴンで当たり判定を取るテスト.

#ifndef GROUNDGRID_H_INCLUDED
#define GROUNDGRID_H_INCLUDED

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "MeshList.h"


struct Polygon{
	const glm::vec3& posA;
	const glm::vec3& posB;
	const glm::vec3& posC;
	
	Polygon(const glm::vec3& vertA,  const glm::vec3& vertB,const glm::vec3& vertC) : posA(vertA),posB(vertB),posC(vertC) {};
};

struct Grid {
	
	std::vector<Polygon*> polygons;
};

class GroundGrid {
public:
	void Initialize();
	void SearchGrid();
	void SetPolyList(MeshList* meshList,const Mesh& mesh);
	void SetPolyList(Polygon& poly);
	void SetPolyList();
	static void Add(const std::vector<Vertex>& v,const std::vector<GLushort>& i);

	bool GroundFunc(glm::vec3& playerPos ,float lineheight);

private:


	int gridPos(const glm::vec3& pos);
	glm::vec3 Pos00(int GridNum);
	glm::vec3 PosX0(int GridNum);
	glm::vec3 PosXY(int GridNum);
	glm::vec3 Pos0Y(int GridNum);
	bool SearchPolygon(int PolyNum,int GridNum);

	static std::vector<Polygon> polygon;
	static std::vector<glm::vec3> vertices;
	static std::vector<unsigned short> indices;


	static std::vector<Mesh> meshes;
	std::vector<Grid> grids;

	float gridSides;
	int gridX;
	int gridY;
};



#endif // GROUNDGRID_H_INCLUDED 
