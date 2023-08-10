#pragma once
#include "Actor.h"
#include "MODEL_COLLISION.h"
#include <chrono>
#include <string>
#include "graphic.h"

class Map :
	public Actor
{
public:
	Map(class Game* game);
	virtual ~Map();
	void UpdateActor()override;
	void AddCollisions(class MODEL_COLLISION* model);
	void RemoveCollisions(class MODEL_COLLISION* model);
	void Draw() {};
	float* GetMaxX() { return mMaxX; }
	float* GetMaxZ() { return mMaxZ; }
	float* GetMinX() { return mMinX; }
	float* GetMinZ() { return mMinZ; }
	int GetAreaNum() { return mAreaNum; }

	//マップモデルを作る
	void CreateCollisions(const char* filename);

	//getter,setter

	const std::vector<class MODEL_COLLISION*>& GetModelCollisions() { return mModelCollisions; }
	class UIMiniMap* GetMiniMap() { return mMiniMap; }

	//Mapを継承したクラスで最初に呼び出すマップデータロード用関数
	void SetCollisionText(const char* text) { Data.CollisionText = text; }

	void CreateArea(float* maxX, float* maxZ, float* minX, float* minZ, int areaNum);

	void MapClear();
	void SetCollisionMap(class COLLISION_MAP* map) { mMap = map; }

	class COLLISION_MAP* GetCollisionMap() { return mMap; }

	float GetStageMinX() { return Data.mStageMinX; }
	float GetStageMaxX() { return Data.mStageMaxX; }
	float GetStageMinZ() { return Data.mStageMinZ; }
	float GetStageMaxZ() { return Data.mStageMaxZ; }

	const VECTOR& GetCenterPos() { return mCenterPos; }
	int GetSecond() { return mSecond; }
	int GetMunite() { return mMunite; }
	std::string& GetTimeText() { return mTimeText; }
	class UILog* GetLog();
	class UIScroll* GetScroll() { return mScroll; }
private:
	float* mMaxX;
	float* mMaxZ;
	float* mMinX;
	float* mMinZ;
	int mAreaNum;
protected:
	//ui
	class UIMiniMap* mMiniMap;
	class UILog* mLog;
	class UIScroll* mScroll;
private:
	std::vector<class MODEL_COLLISION*> mModelCollisions;
public:
	struct DATA
	{
		const char* CollisionText = nullptr;
		float mStageMaxX = 0.0f;
		float mStageMinX = 0.0f;
		float mStageMaxZ = 0.0f;
		float mStageMinZ = 0.0f;
	};
private:
	DATA Data;
	int mSecond;
	int mMunite;
	std::chrono::system_clock::time_point mStart;
	std::string mTimeText;
	bool mClearFlag;
	VECTOR mCenterPos;
	class COLLISION_MAP* mMap;
};

