#pragma once
#include "CharacterActor.h"
#include <chrono>

class ItemObject : public CharacterActor
{
public:
	ItemObject(class Game* game);
	virtual ~ItemObject();
	int SetUp()override;
	void UpdateActor()override;
	virtual bool update() { return true; }
	//getter
	float GetLifeTime() { return cData.mLifeTime; }
	float GetMaxLifeTime() { return cData.mMaxLifeTime; }
	int GetNum() { return iData.mNum; }
	const char* GetName() { return iData.mName; }
	void CreateMesh(const char* normalMeshName = nullptr, const char* damageMeshName = nullptr);
	void LvUpAnnounce(class ItemEffect* item);
	void ItemEffectLvUp(class ItemEffect* item);

public:
	//固有のデータ
	struct individualDATA
	{
		COLOR mColor;
		int mSound1 = -1;
		int mSound2 = -1;
		int mSound1VolumeOffset = 0;
		int mSound2VolumeOffset = 0;
		int mNum = 0;
		const char* mName = nullptr;
	};

	void PlayUseSound1(individualDATA& data);
	void PlayUseSound2(individualDATA& data);

	//共通のデータ
	struct commonDATA
	{
		float mRadius = 0.0f;
		float mJumpVelocity = 0.0f;
		float mGravity = 0.0f;
		int mJumpFlag = 0;
		float mAdvSpeed = 0.0f;
		int mHp = 0;
		float mLifeTime = 0.0f;
		float mMaxLifeTime = 0.0f;
		int mDropSound = -1;
		int mDropSoundVolumeOffset = 0;
		VECTOR mCapsulOffset;
	};
protected:
	//固有のデータ
	individualDATA iData;
	//共通のデータ
	commonDATA cData;
protected:
	class TreeMeshComponent* mTc;
	class CharacterActor* mOwner;
	std::chrono::system_clock::time_point mStart;
	float mTime;
	bool mIsSpawnParticle;
	int mBeforeTime;
	const char* mBatchName;
};