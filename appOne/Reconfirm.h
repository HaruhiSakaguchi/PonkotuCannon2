#pragma once
#include "UIState.h"

class Reconfirm : public UIState
{
public:
	Reconfirm(class UIState* state, class Game* game, const char* name, std::function<void()>func);
	void Closed()override;
	void draw()override;
	void SetNoEvent(std::function<void()>func) { mNo = func; }
	void SetYesEvent(std::function<void()>func) { mYes = func; }

	struct DATA
	{
		const char* mTitle = nullptr;
		const char* mYesText = nullptr;
		const char* mNoText = nullptr;
		float mReconfirmTextSize = 0.0f;
		float mReconfirmTextOffsetY = 0.0f;
		VECTOR2 mBackPos;
		VECTOR2 mTitlePos;
		VECTOR2 mButtonPos;
		COLOR mTitleColor;
		COLOR mReconfirmTextColor;
	};
private:
	DATA Data;
private:
	std::string mName;
	bool mFlag;
	class UIState* mOwner;
	std::function<void()> mYes;
	std::function<void()> mNo;
};