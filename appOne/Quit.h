#pragma once
#include "UIState.h"

class Quit : public UIState
{
public:
	Quit(class Game* game);
	void ChangeOption()override;
	void SetNoEvent(std::function<void()>func) { mNoEvent = func; }
	struct DATA
	{
		const char* mTitle = nullptr;
		const char* mYesText = nullptr;
		const char* mNoText = nullptr;
		float mTextSize = 0.0f;
		VECTOR2 mBackPos;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		COLOR mTitleColor;
	};
private:
	DATA Data;
	std::function<void()>mNoEvent;
};
