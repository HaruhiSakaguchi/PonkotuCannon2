#pragma once
#include "UIMainState.h"
#include <string>

class Title : public UIMainState
{
public:
	Title(class Game* game);
	~Title();
	void ChangeOption()override;
	void Update()override;
	void IsChangePlay() { mIsChangePlay = true; }
	struct DATA
	{
		int mBgm = -1;
		int mBackImg = -1;
		float mTextSize = 0.0f;
		float mButtonTextSize = 0.0f;
		int mBgmSoundVolumeOffset = 0;
		const char* mTitle = nullptr;
		const char* mStartText = nullptr;
		const char* mStartButtonGuide = nullptr;
		const char* mStageSelectText = nullptr;
		const char* mStageSelectButtonGuide = nullptr;
		const char* mQuitText = nullptr;
		const char* mQuitButtonGuide = nullptr;
		const char* mHelpText = nullptr;
		const char* mHelpButtonGuide = nullptr;
		const char* mOptionText = nullptr;
		const char* mOptionButtonGuide = nullptr;
		VECTOR2 mBackPos;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		VECTOR2 mPhaseFirstButtonOffsetPos;
		VECTOR2 mStartButtonGuideOffset;
		COLOR mTitleColor;
	};
private:
	DATA Data;
	bool mPlayBgmFlag = true;
	std::string mText;
	bool mChangeStateFlag;
	bool mIsChangePlay;
};

