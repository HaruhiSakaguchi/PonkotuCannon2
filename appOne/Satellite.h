#pragma once
#include "Enemy.h"
#include "StateComponent.h"
#include "SatelliteWing.h"

class Satellite :
	public Enemy
{
public:
	Satellite(class Game* game, const VECTOR& pos);
	int SetUp()override;
	void UpdateActor()override;
	void Damage(int damage = 1)override;
	void Dead()override;
	//getter,setter
	const VECTOR& GetTargetPosition();
	void SetElapsedTime(float time) { mElapsedTime = time; }
	float GetElapsedTime() { return mElapsedTime; }
	float GetAngleForPos() { return mAngleForPos; }
	void SetAngleForPos(float angle) { mAngleForPos = angle; }
	float GetAnimAngle() { return mAnimAngle; }
	void SetAnimAngle(float angle) { mAnimAngle = angle; }
	float GetMoveRange() { return Data.mMoveRange; }
	float GetAnimSpeed() { return Data.mAnimSpeed; }
	void SetNum(int num) { mNum = num; }
	const int GetNum() { return mNum; }
	class StateComponent* GetStateMacine() { return mState; }
	void SetRange(float range) { mRange = range; }
	float GetRange() { return mRange; }
	void SetTargetPos(const VECTOR& pos) { mTargetPos = pos; }

	const int GetId() { return mId; }
	void SetTmpRotation(const VECTOR& angle) { mTmpRotation = angle; }
	void SetTmpTargetVec(const VECTOR& target) { mTargetVec = target; }

	const VECTOR& GetTmpRotation() { return mTmpRotation; }
	const VECTOR& GetType1TargetVec() { return mTargetVec; }

	class StateComponent* GetStateCompoState() { return mState; }

	void SetAttackFlag(bool flag) { mIsAttack = flag; }
	bool IsAttack() { return mIsAttack; }
	//data
	struct DATA {
		float mAdvSpeed = 0.0f;
		float mMoveRange = 0.0f;
		float mAnimSpeed = 0.0f;
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		float mLaunchInterval = 0.0f;
		float mAngleForPos = 0.0f;
		float mMaxDamageInterval = 0.0f;
		float mGravity = 0.0f;
		float mMaxRange = 0.0f;
		int mMaxHp = 0;
		int mMaxHp2 = 0;
		int mGenerateSatelliteLvLvUpPoint = 0;
		int mSatelliteAGetPoint = 0;
		int mSatelliteBGetPoint = 0;
		int mSatelliteEveryLvUpPoint = 0;
		VECTOR mBulletOffsetPos;
		VECTOR mCapsulOffset;
		VECTOR mOffsetPos;
		VECTOR mTargetOffsetPos;
		VECTOR mMeshOffset;
		COLOR mImageColor;
	};
private:
	static int mNum;
	bool mDeadFlag;
	//data
	DATA Data;
	class StateComponent* mState;
	class CollisionMapComponent* mCollision;
	float mRange;
	int mId;
	float mElapsedTime;
	float mAnimAngle;
	float mAngleForPos;
	bool mIsAttack;
	MATRIX Master;
	MATRIX Target;
	VECTOR mTargetVec;
	VECTOR mTmpRotation;
	VECTOR mTargetPos;
	VECTOR mDeadPoint;

};



