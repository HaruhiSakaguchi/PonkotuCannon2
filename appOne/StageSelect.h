#pragma once
#include "UIState.h"

class StageSelect : public UIState
{
public:
	StageSelect(class Game* game);
	void Closed()override;
	struct DATA
	{
		float mTextSize = 0.0f;
		const char* mTitle = nullptr;
		const char* mStageGuide = nullptr;
		const char* mStage1Text = nullptr;
		const char* mStage2Text = nullptr;
		const char* mStage3Text = nullptr;
		const char* mStage1ReconfirmGuide = nullptr;
		const char* mStage2ReconfirmGuide = nullptr;
		const char* mStage3ReconfirmGuide = nullptr;
		const char* mReturnText = nullptr;
		VECTOR2 mBackPos;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		VECTOR2 mStageGuideOffsetPos;
		COLOR mTitleColor;
	};
private:
	DATA Data;
};
