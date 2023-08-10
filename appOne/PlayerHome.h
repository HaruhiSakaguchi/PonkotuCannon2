#pragma once
#include "PSideCharacterActor.h"
#include "Dore.h"

class PlayerHome :
	public PSideCharacterActor
{
public:
	PlayerHome(class Game* game, const VECTOR& pos = VECTOR(0.0f, 0.0f, 0.0f));
	~PlayerHome();
	int SetUp()override;
	void UpdateActor()override;
	void Dead()override;

	VECTOR* GetHomeTargetPoints() { return mHomeTargetPoints; }
	VECTOR* GetFieldTargetPoints() { return mFieldTargetPoints; }
	VECTOR* GetHomeMoveTargetPoints() { return mMyTargetPoints; }
	void SetTargetPoint(const VECTOR& pos) { mHomeTargetPoint = pos; }
	int GoToTargetPoint(const VECTOR& pos);
	int GetMoveCompleteFlag() { return mMoveCompleteFlag; }

	int GetTargetPosIdx() { return mCurMyTpIdx; }
	void SetTargetPosIdx(int idx) { mCurMyTpIdx = idx; }

	void SetGenerateFlag(int flag) { mGenerateFlag = flag; }
	int GetGenerateFlag() { return mGenerateFlag; }

	int GetBattlePoints() { return mBattlePoints; }
	int GetMaxBattlePoints() { return mMaxBattlePoints; }
	void SetBattlePoints(int point) { mBattlePoints = point; }
	bool InPlayerArea(const VECTOR& pos);

	class PlayerFlag* GetFlag1() { return mFlag1; }
	class PlayerFlag* GetFlag2() { return mFlag2; }

	void SetFirstGenerateBarricadeFlag(int flag) { mFirstGenerateBarricadeFlag = flag; }
	void SetFirstGenerateCannonFlag(int flag) { mFirstGenerateCannonFlag = flag; }
	int GetFirstGenerateBarricadeFlag() { return mFirstGenerateBarricadeFlag; }
	int GetFirstGenerateCannonFlag() { return mFirstGenerateCannonFlag; }
	void CreateHomeArea();

	class Dore* GetDore() { return mDore; }
	struct DATA
	{
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		int mMaxHp = 0;
		int mCannonBasePoint = 0;
		int mBarricadeBasePoint = 0;
		int mLvUpBasePoint = 0;
		int mLvEveryUpPoint = 0;
		int mInitMaxBattlePoint = 0;
		float mMaxDamageInterval = 0.0f;
		VECTOR mFlag1Offset;
		VECTOR mFlag2Offset;
		VECTOR mDoreOffset;
		VECTOR mHpGaugeOffset;
		VECTOR mHomeTargetPointOffsets[4];
		VECTOR mFieldTargetPointOffsets[4];
		COLOR mImageColor;
	};
private:
	DATA Data;
	class PlayerFlag* mFlag1;
	class PlayerFlag* mFlag2;
	class Dore* mDore;
	VECTOR mHomeTargetPoints[4];
	VECTOR mFieldTargetPoints[4];
	VECTOR mMyTargetPoints[3];
	int mCurMyTpIdx;
	int mMoveCompleteFlag;
	VECTOR mHomeTargetPoint;

	class TreeMeshComponent* mTc;
	int mGenerateFlag;
	std::vector<Actor*>mProps;

	int mBattlePoints;
	int mMaxBattlePoints;

	int mFirstGenerateBarricadeFlag;
	int mFirstGenerateCannonFlag;
};

