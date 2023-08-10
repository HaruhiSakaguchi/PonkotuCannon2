#pragma once
#include "SphereWeapon.h"

class SatelliteBullet :
	public SphereWeapon
{
public:
	SatelliteBullet(class Satellite* satellite, const VECTOR& pos, const VECTOR& dir);
	void UpdateActor() override;
	struct IDATA
	{
		int mLaunchSound = -1;
		int mImpactSound = -1;
		int mLaunchSoundVolumeOffset = 0;
		int mImpactSoundVolumeOffset = 0;
		int mChangeFlame = 0;
	};
private:
	IDATA iData;
	int mCnt;
	VECTOR mDefDir;
};

