#pragma once
#include "ActorsWeapon.h"
#include "Satellite.h"

class SatelliteWing :
	public ActorsWeapon
{
public:
	SatelliteWing(class Satellite* satellite);
	void UpdateActor()override;
	int SetUp()override;
	void damage()override;
	void Dead()override;
	struct DATA
	{
		int mClashSound = -1;
		int mId = 0;
		const char* mClashText = nullptr;
		float mGravity = 0.0f;
		float mWingAmbient = 0.0f;
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		float mAdvSpeed = 0.0f;
		float mMaxOffsetZ = 0.0f;
		float mChangePosSpeed = 0.0f;
		float mChangeOffsetPosSpeed = 0.0f;
		int mClashSoundVolumeOffset = 0;
		COLOR mImageColor;
		VECTOR mWingScale1;
		VECTOR mWingScale2;
		VECTOR mS0IdW0IdOffsetPos;
		VECTOR mS0IdW1IdOffsetPos;
		VECTOR mS0IdW2IdOffsetPos;
		VECTOR mS0IdW3IdOffsetPos;
		VECTOR mS1IdOffsetPos;
		VECTOR mS0IdAttackOffsetPos;
		VECTOR mOffsetPos;
	};
private:
	DATA Data;
private:
	static int mNum;
	bool mAttackFlag;
	MATRIX Wing;
	class TreeMeshComponent* mTc;
	std::string mOwnerName;
	static int mGurdSound;
	static int mClashSound;

};

