#include "Map.h"
#include "COLLISION_MAP.h"
#include "FILE_BUFFER.h"
#include "NAME.h"
#include "rand.h"
#include "window.h"
#include <sstream>
#include "UILog.h"
#include "UIMiniMap.h"
#include "UIScroll.h"

Map::Map(class Game* game)
	: Actor(game)
	, mMiniMap(nullptr)
	, mLog(nullptr)
	, mMaxX(nullptr)
	, mMaxZ(nullptr)
	, mMinX(nullptr)
	, mMinZ(nullptr)
	, mAreaNum(0)
	, mSecond(0)
	, mMunite(0)
	, mClearFlag(false)
	, mCenterPos(0.0f, 0.0f, 0.0f)
	, mMap(nullptr)
	, mScroll(nullptr)
{
	Data = GetGame()->GetAllData()->mapData;
	mStart = std::chrono::system_clock::now();
	mScroll = new UIScroll(GetGame());
	mLog = new UILog(GetGame());
	mTimeText = "00:00";
}

Map::~Map()
{
	if (GetGame()->GetState() != Game::GameState::EQuit)
	{
		if (mLog) { mLog->CloseMe(); }
		if (mScroll) { mScroll->CloseMe(); }
		if (mMiniMap) { mMiniMap->CloseMe(); }
	}

	MapClear();
	GetGame()->GetActorManager()->SetStage(nullptr);
}

void Map::AddCollisions(MODEL_COLLISION* model)
{
	mModelCollisions.emplace_back(model);
}

void Map::RemoveCollisions(MODEL_COLLISION* model)
{
	auto iter = std::find(mModelCollisions.begin(), mModelCollisions.end(), model);
	if (iter != mModelCollisions.end())
	{
		std::iter_swap(iter, mModelCollisions.end() - 1);
		mModelCollisions.pop_back();
	}
}

void Map::CreateCollisions(const char* filename)
{
	FILE_BUFFER fb(filename);

	NAME name;
	int cntIndices = 0;
	fb.readString();
	while (!fb.end()) {
		if (fb == 'i') {
			name = fb.readString();
			int numIndices = fb.readInt();
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

	//２週目でTriangleをつくる
	fb.restart();
	int* indices;
	int numIndices;
	VECTOR* vertices;
	int numVertices;
	int idx = 0;
	int numTriangles = 0;
	while (cntIndices > 0) {
		//index
		fb.readString();
		while (fb != 'i')fb.readString();
		name = fb.readString();
		numIndices = fb.readUnsigned();
		numTriangles = numIndices / 3;
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
		}

		new MODEL_COLLISION(this, numTriangles, numVertices, indices, vertices, name);

		SAFE_DELETE_ARRAY(indices);
		SAFE_DELETE_ARRAY(vertices);

		cntIndices--;
	}
}

void Map::CreateArea(float* maxX, float* maxZ, float* minX, float* minZ, int areaNum)
{
	//マップの範囲情報を作る
	mAreaNum = areaNum;
	mMaxX = maxX;
	mMaxZ = maxZ;
	mMinX = minX;
	mMinZ = minZ;

	float* AreaMaxX = new float[mAreaNum];
	float* AreaMinX = new float[mAreaNum];
	float* AreaMaxZ = new float[mAreaNum];
	float* AreaMinZ = new float[mAreaNum];

	for (int i = 0; i < mAreaNum; i++)
	{
		AreaMaxX[i] = mMaxX[i];
		AreaMinX[i] = mMinX[i];
		AreaMaxZ[i] = mMaxZ[i];
		AreaMinZ[i] = mMinZ[i];
	}

	//X、Z座標の最大値、最小値をソートした後、取り出す
	Sort(AreaMaxX, 0, mAreaNum - 1);
	Sort(AreaMinX, 0, mAreaNum - 1);
	Sort(AreaMaxZ, 0, mAreaNum - 1);
	Sort(AreaMinZ, 0, mAreaNum - 1);

	Data.mStageMaxX = AreaMaxX[mAreaNum - 1];
	Data.mStageMinX = AreaMinX[0];
	Data.mStageMaxZ = AreaMaxZ[mAreaNum - 1];
	Data.mStageMinZ = AreaMinZ[0];

	delete[]AreaMaxX;
	delete[]AreaMinX;
	delete[]AreaMaxZ;
	delete[]AreaMinZ;
}

void Map::UpdateActor()
{
	std::ostringstream oss;

	if (GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		auto end = std::chrono::system_clock::now();
		auto dur = end - mStart;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		float time = msec / 1000.0f;

		mMunite = (int)time / 60;
		mSecond = (int)time - 60 * mMunite;
	}

	const char* tenMunite = "";
	const char* tenSecond = "";
	if (mSecond < 10)
	{
		tenSecond = "0";
	}
	if (mMunite < 10)
	{
		tenMunite = "0";
	}
	oss << tenMunite << mMunite << ":" << tenSecond << mSecond;

	mTimeText = oss.str();

	if (!GetGame()->GetActorManager()->GetEHome() && GetGame()->GetActorManager()->GetEnemies().empty() && !mClearFlag)
	{
		mClearFlag = true;
		GetLog()->AddText("すべての敵を倒した！！");
	}

	mCenterPos = VECTOR((GetStageMaxX() + GetStageMinX()) / 2.0f, 0.0f, (GetStageMaxZ() + GetStageMinZ()) / 2.0f);
}

class UILog* Map::GetLog() { return mLog; }

void Map::MapClear()
{
	delete mMap;
}
