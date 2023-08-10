#pragma once
#include "UIState.h"
#include "sound.h"

class Pause :
	public UIState
{
public:
	Pause(class Game* game);
	void Closed()override;
	void ProcessInput() override;
	void Draw() override;
	void ChangeOption()override;
	struct DATA
	{
		int mSound = -1;
		const char* mTitle = nullptr;
		const char* mReStartText = nullptr;
		const char* mReStertButtonGuide = nullptr;
		const char* mOptionText = nullptr;
		const char* mOptionButtonGuide = nullptr;
		const char* mReturnTitleText = nullptr;
		const char* mReturnTitleButtonGuide = nullptr;
		const char* mQuitText = nullptr;
		const char* mQuitButtonGuide = nullptr;
		const char* mHelpText = nullptr;
		const char* mHelpButtonGuide = nullptr;
		int mPauseSoundVolumeOffset = 0;
		float mTextSize = 0.0f;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		VECTOR2 mHelpButtonPosOffset;
	};
private:
	DATA Data;
	bool mQuitFlag;
};
