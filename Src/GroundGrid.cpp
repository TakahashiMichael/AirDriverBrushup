#include "GroundGrid.h"
#include <iostream>
#include "Calculation.h"

//
//int GroundGrid::GridSearch(const glm::vec3& position) {
//	int x = (int)(position.x / this->gridSides);
//	int y = (int)(position.y / this->gridSides);
//	int gridNum=0;
//	gridNum = x + y * this->gridX;
//
//	return gridNum;
//}

//bool GroundGrid::GridTest(const int gridNum,const GroundUnit& polygon) {
//	float x=(float)(gridNum%this->gridX);
//	float y = (float)(gridNum/this->gridX);
//
//
//	return false;
//}

//var judgeIentersected = function(ax, ay, bx, by, cx, cy, dx, dy) {
//	var ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
//	var tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
//	var tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
//	var td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
//
//	return tc * td < 0 && ta * tb < 0;
//	// return tc * td <= 0 && ta * tb <= 0; // �[�_���܂ޏꍇ
//};


//�X�^�e�B�b�N
std::vector<Polygon> GroundGrid::polygon;
std::vector<glm::vec3> GroundGrid::vertices;
std::vector<unsigned short> GroundGrid::indices;
std::vector<Mesh> GroundGrid::meshes;

 void GroundGrid::Add(const std::vector<Vertex>& vertex,const std::vector<GLushort>& index)
{
	//Mesh m;
	//m.mode = GL_TRIANGLES;
	//m.count = iEnd - iBegin;
	//m.indices = (const GLvoid*)(indices.size() * sizeof(GLushort));
	//m.indicesCount = (indices.size() * sizeof(GLushort));
	//m.baseVertex = (GLint)vertices.size();
	//meshes.push_back(m);
	 //std::cout << "�o�^vertex�̌�:" << vertex.size() << std::endl;
	 //std::cout << "�o�^vertex�̌�:" << index.size() << std::endl;
	 for (int i = 0; i < vertex.size(); ++i) {
		
		 vertices.push_back(vertex[i].position);
	 }
	 for (int i = 0; i < index.size();++i) {
		 indices.push_back((unsigned short)index[i]);
	 }

}

//�����Ɛ����̓����蔻��.
//AB �� CD �̐������������邩�ǂ���
bool LineHit(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D ) {
	float TA = (C.x - D.x)*(A.z - C.z) + (C.z - D.z)*(C.x - A.x);
	float TB = (C.x - D.x)*(B.z - C.z) + (C.z - D.z)*(C.x - B.x);
	float TC = (A.x - B.x)*(C.z - A.z) + (A.z - B.z)*(A.x - C.x);
	float TD = (A.x - B.x)*(D.z - A.z) + (A.z - B.z)*(A.x - D.x);

	//��O�̃`�F�b�N,���S�ɐ������m������������Ɉ�v�����ꍇ.
	if ((A.x == B.x &&  C.x == D.x) || (A.z == B.z &&  C.z == D.z)) {
		return TC * TD < 0 && TA*TB < 0;
	}
	else  {
		return TC * TD <= 0 && TA*TB <= 0;
	}

}

glm::vec3 GroundGrid::Pos00(int GridNum)
{
	glm::vec3 pos= glm::vec3(this->gridSides*(float)(GridNum%this->gridX), 0, (this->gridSides*(float)(GridNum / gridX)));

	return pos;
}
glm::vec3 GroundGrid::PosX0(int GridNum)
{
	glm::vec3 pos = Pos00(GridNum) + glm::vec3(gridSides, 0, 0);
	return pos;
}
glm::vec3 GroundGrid::PosXY(int GridNum)
{
	glm::vec3 pos = Pos00(GridNum) + glm::vec3(gridSides, 0, gridSides);
	return pos;

}
glm::vec3 GroundGrid::Pos0Y(int GridNum)
{
	glm::vec3 pos = Pos00(GridNum) + glm::vec3(0, 0, gridSides);
	return pos;

}

//�|���S��num+�O���b�hnum
bool GroundGrid::SearchPolygon(int PolyNum, int GridNum) {
	////��1�ƃO���b�h�̓����蔻��(�ڐ�).
	//std::cout << "�f�o�b�O,�O�̂��߃O���b�hpos���m�F����" << std::endl;
	//std::cout << GridNum << "�Ԃ̃O���b�h�̎l�_�̊m�F" << std::endl;
	//std::cout << "�_A:" << Pos00(GridNum).x <<"/"<< Pos00(GridNum).y<<
	//	" �_B:" << PosX0(GridNum).x <<"/"<< PosX0(GridNum).y<<
	//	" �_C:" << Pos0Y(GridNum).x <<"/"<< Pos0Y(GridNum).y<<
	//	" �_D:" << PosXY(GridNum).x <<"/"<< PosXY(GridNum).y<<
	//	std::endl;
	if (LineHit(Pos00(GridNum),PosX0(GridNum),this->polygon[PolyNum].posA,this->polygon[PolyNum].posB)) {
		//std::cout << "�����Ɛ����Œǉ�:�O���b�h00:�|��AB" << std::endl;
		return true;
	}else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "�����Ɛ����Œǉ�:�O���b�hX0:�|��AB" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), PosXY(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "�����Ɛ����Œǉ�:�O���b�hXY:�|��AB" << std::endl;
		return true;
	}
	else if (LineHit(Pos00(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "�����Ɛ����Œǉ�:�O���b�h0Y:�|��AB" << std::endl;
		return true;
	}

	//����ɕ�2�ł�����
	else if (LineHit(Pos00(GridNum), PosX0(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��BC" << std::endl;
		return true;
	}
	else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��BC" << std::endl;
		return true;
	}
	else if (LineHit(PosXY(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��BC" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), Pos00(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��BC" << std::endl;
		return true;
	}

	//����ɕ�3�ł�����
	else if (LineHit(Pos00(GridNum), PosX0(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��CA" << std::endl;
		return true;
	}
	else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��CA" << std::endl;
		return true;
	}
	else if (LineHit(PosXY(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��CA" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), Pos00(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "�����Ɛ����Œǉ�:�|��CA" << std::endl;
		return true;
	}

	//�Ō�̏���.�����S�Ă̒��_���O���b�h�̒��ɔ[�܂��Ă����ꍇ���l������1�_�����O���b�h�̒��ɓ����Ă��邩���m���߂Ă���.
	else if (Pos00(GridNum).x <= this->polygon[PolyNum].posA.x &&
			PosXY(GridNum).x >= this->polygon[PolyNum].posA.x &&
			Pos00(GridNum).z <= this->polygon[PolyNum].posA.z &&
			PosXY(GridNum).z >= this->polygon[PolyNum].posA.z){
		//std::cout << "�O���b�h�̒��Ƀ|���S�������S�ɓ����Ă�����@�Œǉ�" << std::endl;
		return true;
	}
	//�t�ɂ����|���S���̒��ɑS�ẴO���b�h�̒��_�������ĂȂ��������ׂ�.
	else if (!(Cal::crossProductXZ(this->polygon[PolyNum].posA,this->polygon[PolyNum].posB,Pos00(GridNum))) &&
		!(Cal::crossProductXZ(this->polygon[PolyNum].posB, this->polygon[PolyNum].posC, Pos00(GridNum))) &&
		!(Cal::crossProductXZ(this->polygon[PolyNum].posC, this->polygon[PolyNum].posA, Pos00(GridNum))) 
		) {
		//std::cout << "�|���S���̒��ɃO���b�h�����S�ɓ����Ă�����@�Œǉ�" << std::endl;
		return true;
	}


	return false;
}

void GroundGrid::SearchGrid() {
	//std::cout << "SearchGrid��ʂ��Ă���" << std::endl;
	for (int gridNum = 0; gridNum < this->grids.size(); ++gridNum) {
		//std::cout << "�O���b�h�̃��[�v " << i << "���" << std::endl;

		//std::cout << "�f�o�b�O,�O�̂��߃O���b�hpos���m�F����" << std::endl;
		//std::cout << i << "�Ԃ̃O���b�h�̎l�_�̊m�F" << std::endl;
		//std::cout << "�_A:" << Pos00(i).x << "/" << Pos00(i).y <<
		//	" �_B:" << PosX0(i).x << "/" << PosX0(i).y <<
		//	" �_C:" << Pos0Y(i).x << "/" << Pos0Y(i).y <<
		//	" �_D:" << PosXY(i).x << "/" << PosXY(i).y <<
		//	std::endl;
		//i�̓O���b�h�̓Y����
		for (int polyNum = 0; polyNum < this->polygon.size();++polyNum) {
			//j�̓|���S�����X�g�̓Y����.
			//std::cout << "�|���S���̃��[�v " << j << "���" << std::endl;
			int Num=0;
			if (this->SearchPolygon(polyNum,gridNum)) {
				//�O���b�h�̃|���S�����X�g�ɔ͈͓��̃|���S����o�^����.
				//std::cout << "pushbuck�O" << std::endl;
				this->grids[gridNum].polygons.push_back(&this->polygon[polyNum]);
				//std::cout << "�f�o�b�O:�O���b�h�ɒǉ�: gridnum=" << gridNum << "  :polygonnum=" << polyNum << std::endl;
				//std::cout << "�ǉ������|���S���̍��W���m�F����" << std::endl;
				//std::cout << polyNum << "���ڂ̃|���S�����W" << std::endl;
				//std::cout << "PosA.x:" << grids[gridNum].polygons[Num]->posA.x << " PosA.y:" << grids[gridNum].polygons[Num]->posA.y << " PosA.z:" << grids[gridNum].polygons[Num]->posA.z << std::endl;
				//std::cout << "PosB.x:" << grids[gridNum].polygons[Num]->posB.x << " PosB.y:" << grids[gridNum].polygons[Num]->posB.y << " PosB.z:" << grids[gridNum].polygons[Num]->posB.z << std::endl;
				//std::cout << "PosC.x:" << grids[gridNum].polygons[Num]->posC.x << " PosC.y:" << grids[gridNum].polygons[Num]->posC.y << " PosC.z:" << grids[gridNum].polygons[Num]->posC.z << std::endl;
				++Num;
			}
			else {
				//std::cout << "�f�o�b�O:�ǉ����Ȃ�: gridnum=" << i << "  :polygonnum=" << j << std::endl;

			}

		}
	}
	for (int i = 0; i < this->grids.size(); ++i) {
		//std::cout << "�O���b�h�֓o�^�����v�Z���ʂ�\��" << std::endl;
		//std::cout <<i<< "�Ԗڂ̃O���b�h�ɓo�^�����|���S����:" << grids[i].polygons.size() << std::endl;
	}
}

void GroundGrid::Initialize() {
	//std::cout << "SetPolyList��ʂ��Ă���" << std::endl;


	this->gridX = 10;
	this->gridY = 10;
	this->gridSides = 10.0f;
	this->grids.resize(gridX*gridY);
}

//���@�p
void GroundGrid::SetPolyList() {
	//�C���f�b�N�X�i���o�[
	int indexNum=0;
	for (int i = 0; i < ( indices.size()/ 3); ++i) {
		int num = indices[indexNum];
		const glm::vec3& PosA = vertices[num];
		++indexNum;
		num = indices[indexNum];
		const glm::vec3& PosB = vertices[num];
		++indexNum;
		num = indices[indexNum];
		const glm::vec3& PosC = vertices[num];
		++indexNum;
		this->polygon.push_back(Polygon(PosA, PosB, PosC));
		//std::cout << "�ǉ������|���S���̍��W���m�F����" << std::endl;
		//std::cout << i << "���ڂ̃|���S�����W" << std::endl;
		//std::cout << "PosA.x:" << PosA.x << " PosA.y:" << PosA.y << " PosA.z:" << PosA.z << std::endl;
		//std::cout << "PosB.x:" << PosB.x << " PosB.y:" << PosB.y << " PosB.z:" << PosB.z << std::endl;
		//std::cout << "PosC.x:" << PosC.x << " PosC.y:" << PosC.y << " PosC.z:" << PosC.z << std::endl;
	}
}


//�e�X�g�p
void GroundGrid::SetPolyList(Polygon& poly) {
	polygon.push_back({ poly.posA,poly.posB,poly.posC });
}
/**
* @param meshList �o�^���郁�b�V�����X�g
* @param mesh	  �o�^���郁�b�V��.
* 
* 
* ���i�K�̃��[��.�n�ʂ̓����蔻��Ƃ��ēo�^���钸�_��
* ��{�I�ɂ�vertex�̈ʒu���Ȃǂ͕ς��Ă͂����Ȃ�
* 
* 
* 
**/
void GroundGrid::SetPolyList(MeshList* meshList,const Mesh& mesh) {
	//�n�ʂɒǉ����郂�f���̃C���f�b�N�X����int�^�ɕϊ�.
	int indexSize = (int)(mesh.count);
	//std::cout << "�C���f�b�N�X���̊m�F" << indexSize << std::endl;


	int indices = (int)mesh.baseVertex;
	//std::cout << "���_�f�[�^�����Ԗڂ���Ȃ̂��̊m�F"<<indices<< std::endl;

	int indicesCount = (int(mesh.indices) / sizeof(GLushort));
	//std::cout <<"�C���f�b�N�X�f�[�^�̉��Ԗڂ���Ȃ̂����擾"<< indicesCount<< std::endl;

	//std::cout << meshList->tmpIndices.size() << std::endl;

	int indexNum = indicesCount;
	//�|���S�����擾���Ă���.
	for (int i = 0; i < (indexSize/3); ++i) {
		int num = meshList->tmpIndices[indexNum];
		const glm::vec3& PosA = meshList->tmpVertices[num].position;
		++indexNum;
		num = meshList->tmpIndices[indexNum];
		const glm::vec3& PosB = meshList->tmpVertices[num].position;
		++indexNum;
		num = meshList->tmpIndices[indexNum];
		const glm::vec3& PosC = meshList->tmpVertices[num].position;
		++indexNum;
		this->polygon.push_back(Polygon(PosA, PosB, PosC));
		//std::cout << "�ǉ������|���S���̍��W���m�F����" << std::endl;
		//std::cout << i << "���ڂ̃|���S�����W" << std::endl;
		//std::cout << "PosA.x:" << PosA.x << " PosA.y:" << PosA.y << " PosA.z:" << PosA.z << std::endl;
		//std::cout << "PosB.x:" << PosB.x << " PosB.y:" << PosB.y << " PosB.z:" << PosB.z << std::endl;
		//std::cout << "PosC.x:" << PosC.x << " PosC.y:" << PosC.y << " PosC.z:" << PosC.z << std::endl;
	}

}



/*
* ����������G���A(�O���b�h)���������Ĕԍ���Ԃ�.
* 
* @param pos ��������|�W�V����(���f�����̂�x,z���W�̂�)
* 
* 
* 
* @return val :�����ΏۂƂȂ�O���b�h�̔ԍ�.
*/
int GroundGrid::gridPos(const glm::vec3& pos) {
	//X,Z�̍��W����ԍ��ɕϊ�,
	int X = 0;
	if ((pos.x>= 0) && (pos.x<=gridSides*gridX)) { X = (int)(pos.x / this->gridSides); }
	int Z = 0;
	if ((pos.z>=0)&&(pos.z<=gridSides*gridY)) { Z = (int)(pos.z / this->gridSides); }

	return (X+(Z * gridX));
}

/*
* �Ώۂ̐����ƒn�ʂ̓����蔻������,�����n�ʂ�Ώۂ��ђʂ��Ă���Ε\�ʂɖ߂�,
* 
* 
* 
*/
bool GroundGrid::GroundFunc(glm::vec3& playerPos, float lineHeight) {

	//�v���C���[�̈ʒu�����.

	int gridNum = gridPos(playerPos);
	
	//�v���C���[���O���b�h�͈̔͊O�Ȃ�v�Z���Ȃ�,
	if (gridNum<0 || gridNum>=grids.size()) {
		return false;
	}
	//std::cout << "��������O���b�h�i���o�[;" << gridNum << std::endl;
	bool isGround=false;
	for (int i = 0; i < this->grids[gridNum].polygons.size(); ++i) {
		//std::cout << "��������|���S����" << this->grids[gridNum].polygons.size();

		//�O���b�h�ɓo�^����Ă���|���S���̐������J��Ԃ�,
		//�Ȃ�!�����Ȃ��Ƃ����Ȃ��̂��͂킩��Ȃ�,�������W�n�̖��Ȃ̂��낤.
		if (!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posA,grids[gridNum].polygons[i]->posB,playerPos)) &&
			!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posB, grids[gridNum].polygons[i]->posC, playerPos)) &&
			!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posC, grids[gridNum].polygons[i]->posA, playerPos))){
			//Y���W���_�Ō���playerPos�������Ώۂ����m�F����.
			//std::cout << "�Ώۂ̃|���S���𔭌�" << std::endl;
			//���̊֐��ł��悤����̂ŎO�p�`�̖@��������Ă���(vNormal)
			glm::vec3 AB = grids[gridNum].polygons[i]->posB - grids[gridNum].polygons[i]->posA, AC = grids[gridNum].polygons[i]->posC - grids[gridNum].polygons[i]->posA;
			glm::vec3 vNormal = glm::normalize(glm::cross(AB, AC));
			//�v���C���[�̓����蔻��̍����𑫂����_������Ă���
			glm::vec3 playerHeight = playerPos + glm::vec3(0,lineHeight,0);
			if (Cal::HitPolyAndLine(vNormal, grids[gridNum].polygons[i]->posA,playerPos,playerHeight)) {
				//�����ڐG���Ă���̂ł���΃|���S���̍������v�Z���č������v���C���[�ɑ������,
				playerPos.y = Cal::HeightOfPolygon(vNormal, grids[gridNum].polygons[i]->posA, playerPos);
				isGround = true;
			}
		}
	}
	return isGround;
}

///**
//* OBJ�t�@�C�����璸�_�f�[�^�݂̂�ǂݍ���(meshList����Q�Ƃ���,)
//*
//* @param path �ǂݍ���OBJ�t�@�C���̃p�X.
//*
//* @retval true  �ǂݍ��ݐ���.
//* @retval false �ǂݍ��ݎ��s.
//*/
//bool MeshList::AddFromObjFile(const char* path)
//{
//	// �t�@�C�����J��.
//	std::ifstream ifs(path);
//	if (!ifs) {
//		std::cerr << "ERROR: " << path << "���J���܂���\n";
//		return false;
//	}
//
//	// �f�[�^�ǂݎ��p�̕ϐ�������.
//	struct Face {
//		int v;
//		int vt;
//		int vn;
//	};
//	std::vector<Face> faceList;
//	std::vector <glm::vec3> positionList;
//	std::vector<Vector2> texCoordList;
//	std::vector<Vector3> normalList;
//	faceList.reserve(1000);
//	positionList.reserve(1000);
//	texCoordList.reserve(1000);
//	normalList.reserve(1000);
//
//	// �t�@�C�����烂�f���̃f�[�^��ǂݍ���.
//	while (!ifs.eof()) {
//		std::string line;
//		getline(ifs, line);
//		if (line[0] == '#') {
//			continue;
//		}
//		glm::vec3 v;
//		Vector2 vt;
//		Vector3 vn;
//		Face f[3];
//		if (sscanf_s(line.data(), "v %f %f %f", &v.x, &v.y, &v.z) == 3) {
//			positionList.push_back(v);
//		}
//		else if (sscanf_s(line.data(), "vt %f %f", &vt.x, &vt.y) == 2) {
//			texCoordList.push_back(vt);
//		}
//		else if (sscanf_s(line.data(), "vn %f %f %f", &vn.x, &vn.y, &vn.z) == 3) {
//			const float length = sqrt(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
//			normalList.push_back(Vector3{ vn.x / length, vn.y / length, vn.z / length });
//		}
//		else if (sscanf_s(line.data(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
//			&f[0].v, &f[0].vt, &f[0].vn,
//			&f[1].v, &f[1].vt, &f[1].vn,
//			&f[2].v, &f[2].vt, &f[2].vn) == 9) {
//			faceList.push_back(f[0]);
//			faceList.push_back(f[1]);
//			faceList.push_back(f[2]);
//		}
//	}
//
//	if (positionList.empty()) {
//		std::cerr << "WARNING: " << path << "�ɂ͒��_���W�̒�`������܂���.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//	if (texCoordList.empty()) {
//		std::cerr << "WARNING: " << path << "�ɂ̓e�N�X�`�����W�̒�`������܂���.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//	if (normalList.empty()) {
//		std::cerr << "WARNING: " << path << "�ɂ͖@���̒�`������܂���.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//
//	// ���_�f�[�^�ƃC���f�b�N�X�f�[�^�p�̕ϐ�������.
//	std::vector<Face> faceToVertexList;
//	std::vector<Vertex> vertices;
//	std::vector<GLushort> indices;
//	faceToVertexList.reserve(faceList.size());
//	vertices.reserve(faceList.size());
//	indices.reserve(faceList.size());
//
//	// ���f���̃f�[�^�𒸓_�f�[�^�ƃC���f�b�N�X�f�[�^�ɕϊ�����.
//	for (size_t i = 0; i < faceList.size(); ++i) {
//		size_t n = 0;
//		for (; n < faceToVertexList.size(); ++n) {
//			if (faceToVertexList[n].v == faceList[i].v &&
//				faceToVertexList[n].vt == faceList[i].vt &&
//				faceToVertexList[n].vn == faceList[i].vn) {
//				break;
//			}
//		}
//
//		if (n < faceToVertexList.size()) {
//			indices.push_back((GLushort)n);
//		}
//		else {
//			indices.push_back((GLushort)vertices.size());
//
//			faceToVertexList.push_back(faceList[i]);
//
//			Vertex vertex;
//			int v = faceList[i].v - 1;
//			if (v < 0 || v >= (int)positionList.size()) {
//				std::cerr << "WARNING: �s����v�C���f�b�N�X(" << v << ")\n";
//				v = 0;
//			}
//			int vt = faceList[i].vt - 1;
//			if (vt < 0 || vt >= (int)texCoordList.size()) {
//				std::cerr << "WARNING: �s����vt�C���f�b�N�X(" << vt << ")\n";
//				vt = 0;
//			}
//			int vn = faceList[i].vn - 1;
//			if (vn < 0 || vn >= (int)normalList.size()) {
//				std::cerr << "WARNING: �s����vn�C���f�b�N�X(" << vn << ")\n";
//				vn = 0;
//			}
//			vertex.position = positionList[v];
//			vertex.color = { 1,1,1,1 };
//			vertex.texCoord = texCoordList[vt];
//			vertex.normal = normalList[vn];
//			vertices.push_back(vertex);
//		}
//
//		if (vertices.size() >= USHRT_MAX - 1) {
//			std::cerr << "WARNING: " << path << "�̒��_����GLushort�ň�����͈͂𒴉߂��Ă��܂�.\n";
//			break;
//		}
//	}
//
//	std::cout << "INFO: " << path << " [���_��=" << vertices.size() << " �C���f�b�N�X��=" << indices.size() << "]\n";
//
//	Add(vertices.data(), vertices.data() + vertices.size(), indices.data(), indices.data() + indices.size());
//
//	return true;
//}
//
