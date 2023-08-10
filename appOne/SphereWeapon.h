#pragma once
#include "ActorsWeapon.h"

class SphereWeapon :
	public ActorsWeapon
{
public:
	SphereWeapon(class CharacterActor* owner, const VECTOR& pos = VECTOR(0, 0, 0), const VECTOR& dir = VECTOR(0, 0, 0));
	virtual void UpdateActor()override;
	void SetDamage(int damage) { Data.mDamage = damage; }
public:
	//data
	struct DATA {
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		float mAdvSpeed = 0.0f;
		float mLifeTimeDecreaseSpeed = 0.0f;
		float mMaxLifeTime = 0.0f;
		int mJumpFlag = 0;
		float mGravity = 0.0f;
		float mJumpVelocity = 0.0f;
		float mSize = 0.0f;
		int mDamage = 0;
		VECTOR mOffsetPos;
		COLOR mImageColor;
	};
protected:
	//data
	DATA Data;
	//setup‚ğŒÄ‚Ño‚·‚Æ‚«‚Édata‚ğ“n‚·
	virtual int SetUp(const DATA& data);
	float mLifeTime;
};

