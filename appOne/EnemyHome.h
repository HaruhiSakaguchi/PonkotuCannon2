#pragma once
#include "CharacterActor.h"
#include "Dore.h"

class EnemyHome :
	public CharacterActor
{
public:
	EnemyHome(class Game* game);
	~EnemyHome();
	int SetUp()override;
	void UpdateActor()override;
	void Damage(int damage = 1);
	void Dead()override;
	bool InEnemyArea(const VECTOR& pos);

	void SetTamaGenerateLevel(int lv) { mGenerateTamaLevel = lv; }
	void SetSatelliteGenerateLevel(int lv) { mGenerateSatelliteLevel = lv; }
	int GetTamaGenerateLevel() { return mGenerateTamaLevel; }
	int GetSatelliteGenerateLevel() { return mGenerateSatelliteLevel; }
	int GetBattlePoints() { return mBattlePoints; }
	int GetMaxBattlePoints() { return mMaxBattlePoints; }

	void SetBattlePoints(int pt) { mBattlePoints = pt; }

	void SetGenerateFlag(int flag) { mGenerateFlag = flag; }
	int GetGenerateFlag() { return mGenerateFlag; }

	float GetElapsedTime() { return mElapsedTime; }
	void SetElapsedTime(float time) { mElapsedTime = time; }
	float GetInterval() { return mInterval; }
	void  SetInterval(float interval) { mInterval = interval; }

	void GenerateTama(const VECTOR& pos);
	void GenerateSatellite(const VECTOR& pos);

	int GetGenerateTamaLv() { return mGenerateTamaLevel; }
	int GetGenerateSatelliteLv() { return mGenerateSatelliteLevel; }
	void SetGenerateTamaLv(int lv) { mGenerateTamaLevel = lv; }
	void SetGenerateSatelliteLv(int lv) { mGenerateSatelliteLevel = lv; }

	bool GetSpecialFlag() { return mSpecialFlag; }
	void SetSpecialFlag(bool flag) { mSpecialFlag = flag; }

	void HomeLvUp();
	void EnemyLvUp(class Enemy* enemy);
	class Dore* GetDore() { return mDore; }

	class EnemyFlag* GetFlag1() { return mFlag1; }
	class EnemyFlag* GetFlag2() { return mFlag2; }

	void CreateHomeArea();
	struct DATA
	{
		VECTOR mFlag1Offset;
		VECTOR mFlag2Offset;
		VECTOR mDoreOffset;
		VECTOR mHpGaugeOffset;
		int mMaxHp = 0;
		float mRadius = 0.0f;
		float mHeight = 0.0f;
		float mMaxDamageInterval = 0.00f;
		float mGenerateInterval = 0.0f;
		int mUnitLvUpBasePoint = 0;
		int mUnitLvUpEveryLvPoint = 0;
		int mInitMaxPoint = 0;
		int mHomeLvUpUsePoint = 0;
		int mSatelliteGenerateBasePoint = 0;
		int mTamaGenerateBasePoint = 0;
		int mGenerateLvLvUpPoint = 0;
		int mSpecialReleaseSound = -1;
		int mSpecialReleaseSoundVolumeOffset = 0;
		COLOR mImageColor;
	};
private:
	DATA Data;
	class TreeMeshComponent* mTc;
	class EnemyFlag* mFlag1;
	class EnemyFlag* mFlag2;
	class Dore* mDore;
	int mBattlePoints;
	int mMaxBattlePoints;
	int mGenerateTamaLevel;
	int mGenerateSatelliteLevel;
	float mInterval;
	float mElapsedTime;
	int mGenerateFlag;
	int mFirstSatelliteGenerateFlag;
	int mFirstTamaGenerateFlag;
	bool mSpecialFlag;
	std::vector<Actor*>mProps;
};

