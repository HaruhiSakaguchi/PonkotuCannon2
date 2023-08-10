#pragma once
#include "UIState.h"
class Option : public UIState
{
public:
	Option(class Game* game);
	void Closed()override;
	void draw()override;
	void SetCloseEvent(std::function<void()>func) { mCloseEvent = func; }
	struct DATA
	{
		const char* mTitle = nullptr;
		const char* mResetText = nullptr;
		const char* mResetButtonGuide = nullptr;
		const char* mPlusText = nullptr;
		const char* mMinusText = nullptr;
		const char* mCloseText = nullptr;
		const char* mCloseButtonGuide = nullptr;
		const char* mBGMSwitchText = nullptr;
		const char* mBGMSwitchButtonGuide = nullptr;
		const char* mSoundSwitchText = nullptr;
		const char* mSoundSwitchButtonGuide = nullptr;
		const char* mBGMVolumePlusButtonGuide = nullptr;
		const char* mBGMVolumeMinusButtonGuide = nullptr;
		const char* mEffectVolumePlusButtonGuide = nullptr;
		const char* mEffectVolumeMinusButtonGuide = nullptr;
		const char* mCameraSXPlusButtonGuide = nullptr;
		const char* mCameraSXMinusButtonGuide = nullptr;
		const char* mCameraSYPlusButtonGuide = nullptr;
		const char* mCameraSYMinusButtonGuide = nullptr;
		int mMinVolume = 0;
		int mOneVolume = 0;//ボリューム1段階分の数値
		int mDefaultBgmBolume = 0;
		int mDefaultEffectBolume = 0;
		float mDefaultCameraSX = 0.0f;
		float mDefaultCameraSY = 0.0f;
		float mOneCameraS = 0.0f;
		float mMaxCameraS = 0.0f;
		float mTextSize = 0.0f;
		VECTOR2 mTitlePos;
		COLOR mTitleColor;
		VECTOR2 mBackPos;
		VECTOR2 mButtonPos;
		VECTOR2 mBgmVolumeUpButtonOffsetPos;
		VECTOR2 mBgmVolumeUpButtonGuideOffsetPos;
		VECTOR2 mBgmVolumeDownButtonOffsetPos;
		VECTOR2 mBgmVolumeDownButtonGuideOffsetPos;
		VECTOR2 mEffectVolumeUpButtonOffsetPos;
		VECTOR2 mEffectVolumeUpButtonGuideOffsetPos;
		VECTOR2 mEffectVolumeDownButtonOffsetPos;
		VECTOR2 mEffectVolumeDownButtonGuideOffsetPos;
		VECTOR2 mSoundOnOffButtonOfsetPos;
		VECTOR2 mSoundOnOffButtonGuideOfsetPos;
		VECTOR2 mCameraXUpButtonOffsetPos;
		VECTOR2 mCameraXUpButtonGuideOffsetPos;
		VECTOR2 mCameraXDownButtonOffsetPos;
		VECTOR2 mCameraXDownButtonGuideOffsetPos;
		VECTOR2 mCameraYUpButtonOffsetPos;
		VECTOR2 mCameraYUpButtonGuideOffsetPos;
		VECTOR2 mCameraYDownButtonOffsetPos;
		VECTOR2 mCameraYDownButtonGuideOffsetPos;
		VECTOR2 mCloseButtonOffsetPos;
		VECTOR2 mVolumeTextOffsetPos;
		VECTOR2 mBgmTextOffsetPos;
		VECTOR2 mEffectTextOffsetPos;
		VECTOR2 mEVolTextOffsetPos;
		VECTOR2 mBVolTextOffsetPos;
		VECTOR2 mSoundOnOffTextOffsetPos;
		VECTOR2 mBgmOnOffTextOffsetPos;
		VECTOR2 mCameraSTextOffsetPos;
		VECTOR2 mCameraSXTextOffsetPos;
		VECTOR2 mCameraSYTextOffsetPos;
		VECTOR2 mCameraSXNumTextOffsetPos;
		VECTOR2 mCameraSYNumTextOffsetPos;
		VECTOR2 mResetButtonOffset;
		VECTOR2 mCloseButtonTextOffset;
		VECTOR2 mResetButtonDim;
		VECTOR2 mResetButtonTextOffset;
		COLOR mOnColor;
		COLOR mOffColor;
	};
private:
	DATA Data;
private:
	int mVolume;
	int mEffectVolume;
	std::function<void()> mCloseEvent;
};