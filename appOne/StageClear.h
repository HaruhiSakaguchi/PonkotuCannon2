#pragma once
#include "UIMainState.h"

class StageClear : public UIMainState
{
public:
	StageClear(class Game* game);
	void ChangeOption()override;
	void Draw()override;
	void Closed();
	struct DATA
	{
		int mSound = -1;
		int mSound2 = -1;
		float mTextSize = 0.0f;
		float mClearTimeTextSize = 0.0f;
		const char* mTitle = nullptr;
		const char* mNextText = nullptr;
		const char* mNextButtonGuide = nullptr;
		const char* mReturnTitleText = nullptr;
		const char* mReturnTitleButtonGuide = nullptr;
		const char* mQuitText = nullptr;
		const char* mQuitButtonGuide = nullptr;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		COLOR mTitleColor;
	};
private:
	DATA Data;
	std::string mClearTimeText;
	bool mIsChangeTitle;
	bool mIsChangeAllClear;
};
