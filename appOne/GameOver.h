#pragma once
#include "UIMainState.h"

class GameOver : public UIMainState
{
public:
	GameOver(class Game* game);
	void Update()override;
	void ChangeOption()override;
	struct DATA
	{
		const char* mTitle = nullptr;
		int mSound = -1;
		float mTitleTextSize = 0.0f;
		float mTitlePosAdvSpeed = 0.0f;
		float mMaxOffsetPosY = 0.0f;
		const char* mReturnTitleText;
		const char* mRetryText = nullptr;
		const char* mQuitText = nullptr;
		const char* mReturnTitleButtonGuide = nullptr;
		const char* mRetryButtonGuide = nullptr;
		const char* mQuitButtonGuide = nullptr;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		VECTOR2 mRetryButtonPosOffset;
		COLOR mTitleColor;
	};
private:
	DATA Data;
private:
	float mTime;
	bool mIsRetryFlag;
	bool mIsChangeTitleFlag;
};
