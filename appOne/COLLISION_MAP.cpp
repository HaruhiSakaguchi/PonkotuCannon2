#include "FILE_BUFFER.h"
#include "NAME.h"
#include "COLLISION_MAP.h"
#include "CELL.h"


COLLISION_MAP::COLLISION_MAP(float len, const char* filename)
	: Len(len)//CUBEなCELLの一辺の長さ
	, mGame(nullptr)
{
	//Triangle dataをロード
	loadData(filename);
	//CELLの横、前後、縦の数
	NumX = int((MaxX - MinX) / Len) + 1;
	NumZ = int((MaxZ - MinZ) / Len) + 1;
	NumY = int((MaxY - MinY) / Len) + 1;
	//CELLの３次元配列を動的確保
	Cells = new CELL * *[NumY];
	for (int y = 0; y < NumY; y++) {
		Cells[y] = new CELL * [NumZ];
		for (int z = 0; z < NumZ; z++) {
			Cells[y][z] = new CELL[NumX];
		}
	}
	//「各CELLの左奥下」の座標を設定
	// 最も「左奥下」のセルの座標はMinX,MinZ,MinY（ここが基準）
	for (int y = 0; y < NumY; y++) {
		for (int z = 0; z < NumZ; z++) {
			for (int x = 0; x < NumX; x++) {
				Cells[y][z][x].setLen_Pos(Len, MinX + Len * x, MinY + Len * y, MinZ + Len * z);
				CellS.emplace_back(&Cells[y][z][x]);
			}
		}
	}
	//「各CELL」に含まれる三角ポリゴンを登録
	for (int y = 0; y < NumY; y++) {
		for (int z = 0; z < NumZ; z++) {
			for (int x = 0; x < NumX; x++) {
				for (int i = 0; i < NumTriangles; i++) {
					Cells[y][z][x].regist(Triangles[i]);
				}
			}
		}
	}
}

COLLISION_MAP::~COLLISION_MAP()
{
	//CELLの３次元配列を開放
	for (int y = 0; y < NumY; y++) {
		for (int z = 0; z < NumZ; z++) {
			delete[] Cells[y][z];
		}
		delete[] Cells[y];
	}
	delete[] Cells;

	while (!CellS.empty())
	{
		CellS.pop_back();
	}
	while (!TriangleS.empty())
	{
		TriangleS.pop_back();
	}
	//Trianglesを開放
	SAFE_DELETE_ARRAY(Triangles);

}

void COLLISION_MAP::loadData(const char* fileName)
{
	FILE_BUFFER fb(fileName);

	//１週目でTriangle数集計とデータチェック
	NAME name;
	int cntIndices = 0;
	fb.readString();
	while (!fb.end()) {
		if (fb == 'i') {
			name = fb.readString();
			int numIndices = fb.readInt();
			NumTriangles += numIndices / 3;
			cntIndices++;
		}
		if (fb == 'v') {
			NAME vName = fb.readString();
			if (name != vName) {
				WARNING(1, "COLLISION_MAP::loadData()", "iの次にvが来ていない");
			}
		}
		fb.readString();
	}
	Triangles = new TRIANGLE[NumTriangles];
	for (int i = 0; i < NumTriangles; i++)
	{
		TriangleS.emplace_back(&Triangles[i]);
	}

	//２週目でTriangleをつくる
	fb.restart();
	int* indices;
	int numIndices;
	VECTOR* vertices;
	int numVertices;
	int idx = 0;
	while (cntIndices > 0) {
		//index
		fb.readString();
		while (fb != 'i')fb.readString();
		fb.readString();
		numIndices = fb.readUnsigned();
		indices = new int[numIndices];
		for (int i = 0; i < numIndices; i++)indices[i] = fb.readUnsigned();
		//vertex
		fb.readString();
		while (fb != 'v')fb.readString();
		fb.readString();
		fb.readString();
		numVertices = fb.readUnsigned();
		vertices = new VECTOR[numVertices];

		for (int i = 0; i < numVertices; i++) {
			vertices[i].x = fb.readFloat();
			vertices[i].y = fb.readFloat();
			vertices[i].z = fb.readFloat();
			if (vertices[i].x < MinX)MinX = vertices[i].x;
			if (vertices[i].x > MaxX)MaxX = vertices[i].x;
			if (vertices[i].y < MinY)MinY = vertices[i].y;
			if (vertices[i].y > MaxY)MaxY = vertices[i].y;
			if (vertices[i].z < MinZ)MinZ = vertices[i].z;
			if (vertices[i].z > MaxZ)MaxZ = vertices[i].z;
		}
		//triangle
		int n = 0;
		while (n < numIndices) {
			int j = indices[n++];
			int k = indices[n++];
			int l = indices[n++];
			Triangles[idx++].create(vertices[j], vertices[k], vertices[l]);
		}
		SAFE_DELETE_ARRAY(indices);
		SAFE_DELETE_ARRAY(vertices);

		cntIndices--;
	}
	if (idx != NumTriangles) {
		WARNING(1, "load error collision data ", "");
	}
}


CELL* COLLISION_MAP::SelectCell(const VECTOR* pos)
{
	int y = int((pos->y - MinY) / Len);
	int z = int((pos->z - MinZ) / Len);
	int x = int((pos->x - MinX) / Len);
	if (0 <= y && y < NumY &&
		0 <= z && z < NumZ &&
		0 <= x && x < NumX) {
		return &Cells[y][z][x];
	}
	return nullptr;
}

int COLLISION_MAP::capsule_triangles(VECTOR* pos, float* dirY, int* jumpFlag,
	float speed, float radius, float height, float degree, float* floor)
{
	//オブジェクトのAABBと重なるCELLとの当たり判定-------------------------
	//オブジェクトのposからAABBの座標を作る
	float offset = radius + 0.1f;
	float offsetY = height;
	int flag = 0;
	VECTOR p[8] = {
		VECTOR(pos->x - offset, pos->y + offsetY, pos->z - offset),
		VECTOR(pos->x + offset, pos->y + offsetY, pos->z - offset),
		VECTOR(pos->x - offset, pos->y + offsetY, pos->z + offset),
		VECTOR(pos->x + offset, pos->y + offsetY, pos->z + offset),
		VECTOR(pos->x - offset, pos->y, pos->z - offset),
		VECTOR(pos->x + offset, pos->y, pos->z - offset),
		VECTOR(pos->x - offset, pos->y, pos->z + offset),
		VECTOR(pos->x + offset, pos->y, pos->z + offset),
	};
	//処理済みCELLのポインタ配列。重複処理を避けるためのもの。
	CELL* processedCells[8] = { 0 };
	int step = 0;//階段かもしれないフラッグ
	int idx = 0;
	for (int i = 0; i < 8; i++) {
		//p[ i ]がいるCELLを決定する
		//AABBの頂点それぞれがcellのAABBに入っているかを判別する。入っていたら当たり判定（床以外を）。
		CELL* cell = SelectCell(&p[i]);
		if (cell) {//p[i]がcellのAABBに入っていたら
			//このcellが処理済みかチェックする
			int j;
			for (j = 0; j < idx; j++) {
				if (processedCells[j] == cell) {
					break;
				}
			}
			//処理済みでないので当たり判定（床以外）
			if (j == idx) {
				flag = cell->capsule_triangles(pos, dirY, jumpFlag,
					radius, height, degree, &step);
				processedCells[idx++] = cell;
			}
		}
	}
	//posがいるCELLを選択し、着地の処理を行う（床のみ当たり判定）
	CELL* cell = SelectCell(pos);
	if (cell) {
		flag = cell->capsule_floor_triangles(pos, dirY, jumpFlag, speed,
			radius, height, degree, step, floor);
	}

	return flag;
}

int COLLISION_MAP::capsule_triangles_walls(CharacterActor* actor)
{
	float offset = actor->GetRadius();
	float offsetY = actor->GetHeight();
	VECTOR pos = actor->GetPosition();
	float dirY = 0;
	int jumpFlag = 0;
	int flag = 0;
	float speed = 0.0f;
	float radius = offset;
	float height = offsetY;
	float degree = 0.0f;
	VECTOR p[8] = {
		VECTOR(pos.x - offset, pos.y + offsetY, pos.z - offset),
		VECTOR(pos.x + offset, pos.y + offsetY, pos.z - offset),
		VECTOR(pos.x - offset, pos.y + offsetY, pos.z + offset),
		VECTOR(pos.x + offset, pos.y + offsetY, pos.z + offset),
		VECTOR(pos.x - offset, pos.y, pos.z - offset),
		VECTOR(pos.x + offset, pos.y, pos.z - offset),
		VECTOR(pos.x - offset, pos.y, pos.z + offset),
		VECTOR(pos.x + offset, pos.y, pos.z + offset),
	};
	//処理済みCELLのポインタ配列。重複処理を避けるためのもの。
	CELL* processedCells[8] = { 0 };
	int step = 0;//階段かもしれないフラッグ
	int idx = 0;
	for (int i = 0; i < 8; i++) {
		//p[ i ]がいるCELLを決定する
		CELL* cell = SelectCell(&p[i]);
		if (cell) {
			//このcellが処理済みかチェックする
			int j;
			for (j = 0; j < idx; j++) {
				if (processedCells[j] == cell) {
					break;
				}
			}
			//処理済みでないので当たり判定
			if (j == idx) {
				flag = cell->capsule_triangles(&pos, &dirY, &jumpFlag,
					radius, height, degree, &step);
				processedCells[idx++] = cell;
			}
		}
	}

	return flag;
}

//カメラがマップに食い込まないようにする。（ポリゴンとの交点が線分の終点epになる）
int COLLISION_MAP::segment_triangles(VECTOR& sp, VECTOR* ep, float correct)
{
	for (int y = 0; y < NumY; y++) {
		for (int z = 0; z < NumZ; z++) {
			for (int x = 0; x < NumX; x++) {
				if (Cells[y][z][x].select(sp, *ep)) {
					if (Cells[y][z][x].segment_triangles(sp, ep, correct))
						return 1;
				}
			}
		}
	}
	return 0;
}
int COLLISION_MAP::segment_trianglesEco(VECTOR& sp, VECTOR* ep, float correct)
{
	//キャラのいるセルとカメラのいるセルが同じか、隣接している場合はこれぐらいでいい
	int flag = 0;
	CELL* cell = SelectCell(&sp);
	if (cell) {
		if (cell->segment_triangles(sp, ep, correct)) {
			flag = 1;
		}
	}
	if (flag == 0) {
		CELL* cell = SelectCell(ep);
		if (cell) {
			if (cell->segment_triangles(sp, ep, correct)) {
				flag = 1;
			}
		}
	}
	return flag;
}

