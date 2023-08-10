#pragma once
#include "Enemy.h"

class Tama :
	public Enemy
{
public:
	Tama(class Game* game, const VECTOR& pos);

	~Tama();
	int SetUp() override;
	void UpdateActor() override;
	void Damage(int damage = 1)override;
	void FallOption()override;
	void Dead()override;
	//getter,setter
	float GetMoveInterval() { return Data.mInterval; }
	float GetElapsedtime() { return Data.mElapsedTime; }
	void SetElapsedTime(float time) { Data.mElapsedTime = time; }
	int GetWeaponCnt() { return Data.mWeaponCnt; }
	void SetWeaponCnt(int cnt) { Data.mWeaponCnt = cnt; }
	float GetAnimAngle() { return Data.mAnimAngle; }
	void SetAnimAngle(float angle) { Data.mAnimAngle = angle; }
	float GetAnimSpeed() { return Data.mAnimSpeed; }
	int GetDushSound() { return Data.mDushSound; }
	void SetAttackVector(const VECTOR& vec) { mAttackVector = vec; }
	const VECTOR& GetAttackVector() { return mAttackVector; }
	void SetTargetPos(const VECTOR& vec) { mTargetPos = vec; }
	const VECTOR& GetTargetPos() { return mTargetPos; }

	class SEGMENT* GetSight() { return mLine; }
	class StateComponent* GetStateCompoState() { return mState; }
	void SetNum(int num) { mNum = num; }

public:
	//Data
	struct DATA {
		float mAnimSpeed = 0.0f;
		float mJumpVelocity = 0.0f;
		float mGravity = 0.f;
		int mJumpFlag = 0;
		float mAdvSpeed = 0.0f;
		int mMaxHp = 0;
		float mAnimAngle = 0.0f;
		int mWeaponCnt = 0;
		float mElapsedTime = 0.0f;
		float mInterval = 0.0f;
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		float mMaxDamageInterval = 0.0f;
		float mBlackEyeScale = 0.0f;
		float mMaxScale = 0.0f;
		float mMaxOffsetZ = 0.0f;
		float mChangeScaleSpeed = 0.0f;
		VECTOR mOffsetPos;
		VECTOR mHpGaugeOffset;
		VECTOR mCapsulOffset;
		VECTOR mBlackEyeOffsetPos;
		COLOR mImageColor;
		VECTOR mSightSp;
		VECTOR mSightEp;
		int mDushSound = -1;
		int mDushSoundVolumeOffsset = 0;
	};

private:
	//data
	DATA Data;
private:
	VECTOR mAttackVector;
	VECTOR mTargetPos;
	//component
	class StateComponent* mState;
	float mScale;
	class TreeMeshComponent* mTc;
	class TamaBlackEye* mEye;
	class SEGMENT* mLine;
	static int mNum;
};



