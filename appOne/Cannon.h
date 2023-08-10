#pragma once
#include "PSideCharacterActor.h"
#include "StateComponent.h"

class Cannon :
	public PSideCharacterActor
{
public:
	Cannon(class Game* game);
	~Cannon();
	int SetUp()override;
	void UpdateActor()override;
	const VECTOR& GetTargetPosition() { return mTargetPos; }

	void Dead()override;

	//setter,getter
	float GetTimer() { return mTimer; }
	void SetTimer(float timer) { mTimer = timer; }
	void SetInterval(float interval) { mInterval = interval; }
	float GetInterval() { return mInterval; }
	void SetLaunchTime(float time) { mLaunchTime = time; }

	int GetNextTpIndex();
	float GetRange() { return mRange; }
	void SetRange(float range) { mRange = range; }

	class StateComponent* GetStateCompoState() { return mState; }

	void AddItemNum(int num);
	void RemoveItemNum(int num);
	void SetCnt(int cnt) { this->mCnt = cnt; }
	const int GetCnt() { return mCnt; }
	const std::vector<int>& GetItemNums() { return mItemNums; }
	int GetSlide() { return Data.mSlide; }
	int GetOutOfBullets() { return Data.mOutOfBullets; }
	int GetSlideCnt() { return mSlideCnt; }
	void SetSlideCnt(int cnt) { mSlideCnt = cnt; }

	void SetCNum(int num) { mCNum = num; }
	int GetCNum() { return mCNum; }

	const int GetTPIndex() { return mTPIndex; }
	void SetTPIndex(int idx) { mTPIndex = idx; }

	//data
	struct DATA {
		VECTOR mOffsetPos;
		VECTOR mBarrelDir;
		VECTOR mInitPos;
		VECTOR mCapsulOffset;
		VECTOR mDir;
		float mAmbient = 0.0f;
		float mAdvSpeed = 0.0f;
		float mJumpVelocity = 0.0f;
		float mGravity = 0.0f;
		float mInterval = 0.0f;
		float mRange = 0.0f;
		float mMaxDamageInterval = 0.0f;
		float mCannonCapsulHeight = 0.0f;
		float mCannonCapsulRadius = 0.0f;
		float mChangeScaleSpeed = 0.0f;
		float mLaunchTime = 0.0f;
		int mMaxHp = 0;
		int mJumpFlag = 0;
		float mWheelAngleOffset = 0.0f;
		float mLaunchTimeDecreaseAdvSpeed = 0.0f;
		float mLaunchBodyScale = 0.0f;
		float mNormalBodyScale = 0.0f;
		int mItemStockMaxSize = 0;
		VECTOR mWheelOffsetPos;
		VECTOR mBodyOffsetPos;
		COLOR mImageColor;
		//âπê∫ÉfÅ[É^
		int mJumpSound = -1;
		int mJumpSoundVolumeOffset = 0;
		int mCyakuchi = -1;
		int mSlide = -1;
		int mFallSoundVolumeOffset = 0;
		int mOutOfBullets = -1;
		int mSlideSoundVolumeOffset = 0;
	};

	enum class MoveState
	{
		EStay,
		EReturn,
		EHomePatroll,
		EFieldPatroll
	};
	void SetMoveState(MoveState state) { mMoveState = state; }
	MoveState GetMoveState() { return mMoveState; }

private:
	//Data
	DATA Data;
	//component
	class StateComponent* mState;
	MoveState mMoveState;
	//Hierarchy Matrix
	MATRIX Master, Body, Target;

	std::vector<int>mItemNums;

	int mCnt;
	int mSlideCnt;
	float mScale;
	float mLaunchTime;
	float mInterval;
	float mRange;
	class CannonWheelL* mWheelL;
	class CannonWheelR* mWheelR;
	float mTimer;
	VECTOR mTargetPos;

	int mTPIndex;
	static int mCNum;
};