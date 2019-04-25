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
//	// return tc * td <= 0 && ta * tb <= 0; // 端点を含む場合
//};


//スタティック
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
	 //std::cout << "登録vertexの個数:" << vertex.size() << std::endl;
	 //std::cout << "登録vertexの個数:" << index.size() << std::endl;
	 for (int i = 0; i < vertex.size(); ++i) {
		
		 vertices.push_back(vertex[i].position);
	 }
	 for (int i = 0; i < index.size();++i) {
		 indices.push_back((unsigned short)index[i]);
	 }

}

//線分と線分の当たり判定.
//AB と CD の線分が交差するかどうか
bool LineHit(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D ) {
	float TA = (C.x - D.x)*(A.z - C.z) + (C.z - D.z)*(C.x - A.x);
	float TB = (C.x - D.x)*(B.z - C.z) + (C.z - D.z)*(C.x - B.x);
	float TC = (A.x - B.x)*(C.z - A.z) + (A.z - B.z)*(A.x - C.x);
	float TD = (A.x - B.x)*(D.z - A.z) + (A.z - B.z)*(A.x - D.x);

	//例外のチェック,完全に線分同士が同じ直線上に一致した場合.
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

//ポリゴンnum+グリッドnum
bool GroundGrid::SearchPolygon(int PolyNum, int GridNum) {
	////辺1とグリッドの当たり判定(接線).
	//std::cout << "デバッグ,念のためグリッドposを確認する" << std::endl;
	//std::cout << GridNum << "番のグリッドの四点の確認" << std::endl;
	//std::cout << "点A:" << Pos00(GridNum).x <<"/"<< Pos00(GridNum).y<<
	//	" 点B:" << PosX0(GridNum).x <<"/"<< PosX0(GridNum).y<<
	//	" 点C:" << Pos0Y(GridNum).x <<"/"<< Pos0Y(GridNum).y<<
	//	" 点D:" << PosXY(GridNum).x <<"/"<< PosXY(GridNum).y<<
	//	std::endl;
	if (LineHit(Pos00(GridNum),PosX0(GridNum),this->polygon[PolyNum].posA,this->polygon[PolyNum].posB)) {
		//std::cout << "線分と線分で追加:グリッド00:ポリAB" << std::endl;
		return true;
	}else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "線分と線分で追加:グリッドX0:ポリAB" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), PosXY(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "線分と線分で追加:グリッドXY:ポリAB" << std::endl;
		return true;
	}
	else if (LineHit(Pos00(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posA, this->polygon[PolyNum].posB)) {
		//std::cout << "線分と線分で追加:グリッド0Y:ポリAB" << std::endl;
		return true;
	}

	//さらに辺2でも検索
	else if (LineHit(Pos00(GridNum), PosX0(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "線分と線分で追加:ポリBC" << std::endl;
		return true;
	}
	else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "線分と線分で追加:ポリBC" << std::endl;
		return true;
	}
	else if (LineHit(PosXY(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "線分と線分で追加:ポリBC" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), Pos00(GridNum), this->polygon[PolyNum].posB, this->polygon[PolyNum].posC)) {
		//std::cout << "線分と線分で追加:ポリBC" << std::endl;
		return true;
	}

	//さらに辺3でも検索
	else if (LineHit(Pos00(GridNum), PosX0(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "線分と線分で追加:ポリCA" << std::endl;
		return true;
	}
	else if (LineHit(PosX0(GridNum), PosXY(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "線分と線分で追加:ポリCA" << std::endl;
		return true;
	}
	else if (LineHit(PosXY(GridNum), Pos0Y(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "線分と線分で追加:ポリCA" << std::endl;
		return true;
	}
	else if (LineHit(Pos0Y(GridNum), Pos00(GridNum), this->polygon[PolyNum].posC, this->polygon[PolyNum].posA)) {
		//std::cout << "線分と線分で追加:ポリCA" << std::endl;
		return true;
	}

	//最後の条件.もし全ての頂点がグリッドの中に納まっていた場合を考慮して1点だけグリッドの中に入っているかを確かめておく.
	else if (Pos00(GridNum).x <= this->polygon[PolyNum].posA.x &&
			PosXY(GridNum).x >= this->polygon[PolyNum].posA.x &&
			Pos00(GridNum).z <= this->polygon[PolyNum].posA.z &&
			PosXY(GridNum).z >= this->polygon[PolyNum].posA.z){
		//std::cout << "グリッドの中にポリゴンが完全に入っている方法で追加" << std::endl;
		return true;
	}
	//逆にもしポリゴンの中に全てのグリッドの頂点が入ってないかも調べる.
	else if (!(Cal::crossProductXZ(this->polygon[PolyNum].posA,this->polygon[PolyNum].posB,Pos00(GridNum))) &&
		!(Cal::crossProductXZ(this->polygon[PolyNum].posB, this->polygon[PolyNum].posC, Pos00(GridNum))) &&
		!(Cal::crossProductXZ(this->polygon[PolyNum].posC, this->polygon[PolyNum].posA, Pos00(GridNum))) 
		) {
		//std::cout << "ポリゴンの中にグリッドが完全に入っている方法で追加" << std::endl;
		return true;
	}


	return false;
}

void GroundGrid::SearchGrid() {
	//std::cout << "SearchGridを通っている" << std::endl;
	for (int gridNum = 0; gridNum < this->grids.size(); ++gridNum) {
		//std::cout << "グリッドのループ " << i << "回目" << std::endl;

		//std::cout << "デバッグ,念のためグリッドposを確認する" << std::endl;
		//std::cout << i << "番のグリッドの四点の確認" << std::endl;
		//std::cout << "点A:" << Pos00(i).x << "/" << Pos00(i).y <<
		//	" 点B:" << PosX0(i).x << "/" << PosX0(i).y <<
		//	" 点C:" << Pos0Y(i).x << "/" << Pos0Y(i).y <<
		//	" 点D:" << PosXY(i).x << "/" << PosXY(i).y <<
		//	std::endl;
		//iはグリッドの添え字
		for (int polyNum = 0; polyNum < this->polygon.size();++polyNum) {
			//jはポリゴンリストの添え字.
			//std::cout << "ポリゴンのループ " << j << "回目" << std::endl;
			int Num=0;
			if (this->SearchPolygon(polyNum,gridNum)) {
				//グリッドのポリゴンリストに範囲内のポリゴンを登録する.
				//std::cout << "pushbuck前" << std::endl;
				this->grids[gridNum].polygons.push_back(&this->polygon[polyNum]);
				//std::cout << "デバッグ:グリッドに追加: gridnum=" << gridNum << "  :polygonnum=" << polyNum << std::endl;
				//std::cout << "追加したポリゴンの座標を確認する" << std::endl;
				//std::cout << polyNum << "枚目のポリゴン座標" << std::endl;
				//std::cout << "PosA.x:" << grids[gridNum].polygons[Num]->posA.x << " PosA.y:" << grids[gridNum].polygons[Num]->posA.y << " PosA.z:" << grids[gridNum].polygons[Num]->posA.z << std::endl;
				//std::cout << "PosB.x:" << grids[gridNum].polygons[Num]->posB.x << " PosB.y:" << grids[gridNum].polygons[Num]->posB.y << " PosB.z:" << grids[gridNum].polygons[Num]->posB.z << std::endl;
				//std::cout << "PosC.x:" << grids[gridNum].polygons[Num]->posC.x << " PosC.y:" << grids[gridNum].polygons[Num]->posC.y << " PosC.z:" << grids[gridNum].polygons[Num]->posC.z << std::endl;
				++Num;
			}
			else {
				//std::cout << "デバッグ:追加しない: gridnum=" << i << "  :polygonnum=" << j << std::endl;

			}

		}
	}
	for (int i = 0; i < this->grids.size(); ++i) {
		//std::cout << "グリッドへ登録した計算結果を表示" << std::endl;
		//std::cout <<i<< "番目のグリッドに登録したポリゴン数:" << grids[i].polygons.size() << std::endl;
	}
}

void GroundGrid::Initialize() {
	//std::cout << "SetPolyListを通っている" << std::endl;


	this->gridX = 10;
	this->gridY = 10;
	this->gridSides = 10.0f;
	this->grids.resize(gridX*gridY);
}

//実機用
void GroundGrid::SetPolyList() {
	//インデックスナンバー
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
		//std::cout << "追加したポリゴンの座標を確認する" << std::endl;
		//std::cout << i << "枚目のポリゴン座標" << std::endl;
		//std::cout << "PosA.x:" << PosA.x << " PosA.y:" << PosA.y << " PosA.z:" << PosA.z << std::endl;
		//std::cout << "PosB.x:" << PosB.x << " PosB.y:" << PosB.y << " PosB.z:" << PosB.z << std::endl;
		//std::cout << "PosC.x:" << PosC.x << " PosC.y:" << PosC.y << " PosC.z:" << PosC.z << std::endl;
	}
}


//テスト用
void GroundGrid::SetPolyList(Polygon& poly) {
	polygon.push_back({ poly.posA,poly.posB,poly.posC });
}
/**
* @param meshList 登録するメッシュリスト
* @param mesh	  登録するメッシュ.
* 
* 
* 現段階のルール.地面の当たり判定として登録する頂点は
* 基本的にはvertexの位置情報などは変えてはいけない
* 
* 
* 
**/
void GroundGrid::SetPolyList(MeshList* meshList,const Mesh& mesh) {
	//地面に追加するモデルのインデックス数をint型に変換.
	int indexSize = (int)(mesh.count);
	//std::cout << "インデックス数の確認" << indexSize << std::endl;


	int indices = (int)mesh.baseVertex;
	//std::cout << "頂点データが何番目からなのかの確認"<<indices<< std::endl;

	int indicesCount = (int(mesh.indices) / sizeof(GLushort));
	//std::cout <<"インデックスデータの何番目からなのかを取得"<< indicesCount<< std::endl;

	//std::cout << meshList->tmpIndices.size() << std::endl;

	int indexNum = indicesCount;
	//ポリゴンを取得していく.
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
		//std::cout << "追加したポリゴンの座標を確認する" << std::endl;
		//std::cout << i << "枚目のポリゴン座標" << std::endl;
		//std::cout << "PosA.x:" << PosA.x << " PosA.y:" << PosA.y << " PosA.z:" << PosA.z << std::endl;
		//std::cout << "PosB.x:" << PosB.x << " PosB.y:" << PosB.y << " PosB.z:" << PosB.z << std::endl;
		//std::cout << "PosC.x:" << PosC.x << " PosC.y:" << PosC.y << " PosC.z:" << PosC.z << std::endl;
	}

}



/*
* 引数がいるエリア(グリッド)を検索して番号を返す.
* 
* @param pos 検索するポジション(反映されるのはx,z座標のみ)
* 
* 
* 
* @return val :検索対象となるグリッドの番号.
*/
int GroundGrid::gridPos(const glm::vec3& pos) {
	//X,Zの座標をを番号に変換,
	int X = 0;
	if ((pos.x>= 0) && (pos.x<=gridSides*gridX)) { X = (int)(pos.x / this->gridSides); }
	int Z = 0;
	if ((pos.z>=0)&&(pos.z<=gridSides*gridY)) { Z = (int)(pos.z / this->gridSides); }

	return (X+(Z * gridX));
}

/*
* 対象の線分と地面の当たり判定を取る,もし地面を対象が貫通していれば表面に戻す,
* 
* 
* 
*/
bool GroundGrid::GroundFunc(glm::vec3& playerPos, float lineHeight) {

	//プレイヤーの位置を入力.

	int gridNum = gridPos(playerPos);
	
	//プレイヤーがグリッドの範囲外なら計算しない,
	if (gridNum<0 || gridNum>=grids.size()) {
		return false;
	}
	//std::cout << "検索するグリッドナンバー;" << gridNum << std::endl;
	bool isGround=false;
	for (int i = 0; i < this->grids[gridNum].polygons.size(); ++i) {
		//std::cout << "検索するポリゴン数" << this->grids[gridNum].polygons.size();

		//グリッドに登録されているポリゴンの数だけ繰り返し,
		//なぜ!をつけないといけないのかはわからない,多分座標系の問題なのだろう.
		if (!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posA,grids[gridNum].polygons[i]->posB,playerPos)) &&
			!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posB, grids[gridNum].polygons[i]->posC, playerPos)) &&
			!(Cal::crossProductXZ(grids[gridNum].polygons[i]->posC, grids[gridNum].polygons[i]->posA, playerPos))){
			//Y座標視点で見てplayerPosが処理対象かを確認する.
			//std::cout << "対象のポリゴンを発見" << std::endl;
			//先二つの関数でしようするので三角形の法線を取っておく(vNormal)
			glm::vec3 AB = grids[gridNum].polygons[i]->posB - grids[gridNum].polygons[i]->posA, AC = grids[gridNum].polygons[i]->posC - grids[gridNum].polygons[i]->posA;
			glm::vec3 vNormal = glm::normalize(glm::cross(AB, AC));
			//プレイヤーの当たり判定の高さを足した点を作っておく
			glm::vec3 playerHeight = playerPos + glm::vec3(0,lineHeight,0);
			if (Cal::HitPolyAndLine(vNormal, grids[gridNum].polygons[i]->posA,playerPos,playerHeight)) {
				//もし接触しているのであればポリゴンの高さを計算して高さをプレイヤーに代入する,
				playerPos.y = Cal::HeightOfPolygon(vNormal, grids[gridNum].polygons[i]->posA, playerPos);
				isGround = true;
			}
		}
	}
	return isGround;
}

///**
//* OBJファイルから頂点データのみを読み込む(meshListから参照した,)
//*
//* @param path 読み込むOBJファイルのパス.
//*
//* @retval true  読み込み成功.
//* @retval false 読み込み失敗.
//*/
//bool MeshList::AddFromObjFile(const char* path)
//{
//	// ファイルを開く.
//	std::ifstream ifs(path);
//	if (!ifs) {
//		std::cerr << "ERROR: " << path << "を開けません\n";
//		return false;
//	}
//
//	// データ読み取り用の変数を準備.
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
//	// ファイルからモデルのデータを読み込む.
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
//		std::cerr << "WARNING: " << path << "には頂点座標の定義がありません.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//	if (texCoordList.empty()) {
//		std::cerr << "WARNING: " << path << "にはテクスチャ座標の定義がありません.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//	if (normalList.empty()) {
//		std::cerr << "WARNING: " << path << "には法線の定義がありません.\n";
//		Add(nullptr, nullptr, nullptr, nullptr);
//		return false;
//	}
//
//	// 頂点データとインデックスデータ用の変数を準備.
//	std::vector<Face> faceToVertexList;
//	std::vector<Vertex> vertices;
//	std::vector<GLushort> indices;
//	faceToVertexList.reserve(faceList.size());
//	vertices.reserve(faceList.size());
//	indices.reserve(faceList.size());
//
//	// モデルのデータを頂点データとインデックスデータに変換する.
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
//				std::cerr << "WARNING: 不正なvインデックス(" << v << ")\n";
//				v = 0;
//			}
//			int vt = faceList[i].vt - 1;
//			if (vt < 0 || vt >= (int)texCoordList.size()) {
//				std::cerr << "WARNING: 不正なvtインデックス(" << vt << ")\n";
//				vt = 0;
//			}
//			int vn = faceList[i].vn - 1;
//			if (vn < 0 || vn >= (int)normalList.size()) {
//				std::cerr << "WARNING: 不正なvnインデックス(" << vn << ")\n";
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
//			std::cerr << "WARNING: " << path << "の頂点数はGLushortで扱える範囲を超過しています.\n";
//			break;
//		}
//	}
//
//	std::cout << "INFO: " << path << " [頂点数=" << vertices.size() << " インデックス数=" << indices.size() << "]\n";
//
//	Add(vertices.data(), vertices.data() + vertices.size(), indices.data(), indices.data() + indices.size());
//
//	return true;
//}
//
