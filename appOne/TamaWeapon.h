#pragma once
#include "SphereWeapon.h"
#include "Tama.h"

class TamaWeapon :
	public SphereWeapon
{
public:
	TamaWeapon(class Tama* owner, const VECTOR& pos = VECTOR(0, 0, 0), const VECTOR& dir = VECTOR(0, 0, 0));
	~TamaWeapon();
	void UpdateActor()override;
	struct IDATA
	{
		int mAttackSound = -1;
		int mAttackSoundOffset = 0;
		float mAttackTime = 0.0f;
	};

private:
	IDATA iData;
private:
	static int mNum;
	int mId;
	float mTime;
};