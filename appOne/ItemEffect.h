#pragma once
#include "CharacterActor.h"
#include "COLOR.h"
#include <string>
#include "sound.h"
#include <chrono>

class ItemEffect : public CharacterActor
{
public:
	ItemEffect(class CharacterActor* owner);
	void UpdateActor()override;
	virtual void Dead()override;
	float GetInterval() { return Data.mInterval; }
	float GetTime() { return Data.mTime; }
	void SetInterval(float interval) { Data.mInterval = interval; }
	void SetTime(float time) { Data.mTime = time; }
	const COLOR& GetColor() { return Data.mColor; }
	void SetColor(const COLOR& color) { Data.mColor = color; }
	void SetNumber(int num) { cData.mNumber = num; }
	float GetKeepTime() { return cData.mKeepTime; }
	void SetKeepTime(float time) { cData.mKeepTime = time; }
	void SetUpLifeTime(float time) { mUpTime = time; }
	void TimeReset() { mStart = std::chrono::system_clock::now(); }
	class CharacterActor* GetOwner() { return mOwner; }
	struct IDATA
	{
		int mLevel = 0;
		int mMaxLevel = 0;
		float mTime = 0.0f;
		float mInterval = 0.0f;
		int mMaxHp = 0;
		std::string mName;
		COLOR mColor;
	};
	struct CDATA {
		float mUIOffsetPosY = 0.0f;
		float mUIPosY = 0.0f;
		float mUIPosAdvSpeed = 0.0f;
		float mUIMinPosX = 0.0f;
		float mUIPosChangeSpeed = 0.0f;
		int mNumber = 0;
		float mKeepTime = 0.0f;
	};
private:
	CDATA cData;
protected:
	IDATA Data;
	class CharacterActor* mOwner;
	const char* mMeshName;
	std::chrono::system_clock::time_point mStart;
	float mUpTime;
	int mNextParticleSpawnTime;
	bool mIsSpawnParticle;
	int mBeforeParticleSpawnTime;
};