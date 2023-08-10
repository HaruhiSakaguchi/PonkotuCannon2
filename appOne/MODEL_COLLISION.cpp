#include "MODEL_COLLISION.h"

//ミニマップデータを作る用のクラス　作ったら消去する。
MODEL_COLLISION::MODEL_COLLISION(class Map* map, int numTriangles, int numVertices, int* indices, VECTOR* vertices, const char* name)
	: mMap(map)
	, mOPositions(nullptr)
	, mONormals(nullptr)
	, mIndices(nullptr)
	, mNumVertices(0)
	, mNumTriangles(0)
	, mNumIndices(0)
	, mAddFlag(true)
{
	mMap->AddCollisions(this);

	SetName(name);

	mNumTriangles = numTriangles;
	mNumVertices = numVertices;

	allocateMemory();

	for (int i = 0; i < mNumVertices; i++)
	{
		mOPositions[i] = vertices[i];
	}

	for (int i = 0; i < mNumIndices; i++)
	{
		mIndices[i] = indices[i];
	}

	for (int i = 0; i < mNumVertices; i++)
	{
		mONormals[i].set(0.0f, 1.0f, 0.0f);
	}

}


MODEL_COLLISION::~MODEL_COLLISION()
{
	if (mOPositions)delete[] mOPositions;
	if (mONormals)delete[] mONormals;
	if (mIndices)delete[] mIndices;
	mMap->RemoveCollisions(this);
}

void MODEL_COLLISION::allocateMemory()
{
	//位置と法線ベクトル（頂点バッファ）
	mOPositions = new VECTOR[mNumVertices];
	mONormals = new VECTOR[mNumVertices];
	mNumIndices = mNumTriangles * 3;
	mIndices = new int[mNumIndices];
}
