#pragma once
#include <functional>
#include "VECTOR2.h"
#include "sound.h"
#include "COLOR.h"
#include <string>
#include "graphic.h"
#include "UIManager.h"

class Button
{
public:
	Button(const char* name,
		std::function<void()> onClick,
		const VECTOR2& pos,
		class Game* game,
		const char* text = 0,
		const VECTOR2& textOffset = VECTOR2(0, 0)
	);
	virtual ~Button() {};

	virtual void Draw();
	void Update();
	void DrawGuide();
	void DrawRectButton();

	const VECTOR2& GetPosition() { return mPosition; }
	void SetPosition(const VECTOR2& pos) { mPosition = pos; }

	// マウスポインタがこのボタン内にあるか
	virtual bool ContainsPoint(const VECTOR2& pt, bool flag = true);
	// クリックされたときに呼び出される関数
	void OnClick();
	// Getter
	void ContainsSound();
	bool GetSound() { return mSoundFlag; }
	void SetName(const char* name) { mName = name; }
	const char* GetText() { return mText; }
	void SetGuideText(const char* text) { mText = text; }
	void SetNameOffsetPos(const VECTOR2& pos) { mNameOffset = pos; }

	void SetTextOffset(const VECTOR2& ofst) { mTextOffset = ofst; }
	const VECTOR2& GetTextOffset() { return mTextOffset; }
	void ConvertReverseButtonGuideTextPos();
	void SetRectButtonDim(const VECTOR2& dim) { mRectButtonDim = dim; }
	const VECTOR2& GetRectButtonDim() { return mRectButtonDim; }
	void SetContainsRectButtonCOLOR(const COLOR& color) { mContainsColor = color; }
	void SetNoContainsRectButtonCOLOR(const COLOR& color) { mNoContainsColor = color; }

	void ChangeCancellSound() { mCancellFlag = true; }
	struct DATA
	{
		int mClickSound = -1;
		int mContainsSound = -1;
		int mCancellSound = -1;
		int mClickSoundVolumeOffset = 0;
		int mContainsSoundVolumeOffset = 0;
		int mCancellSoundVolumeOffset = 0;
		float mTopShadowSw = 0.0f;
		float mButtonTextSize = 0.0f;
		float mGuideTextSize = 0.0f;
		float mGuideRectSw = 0.0f;
		float mBasicOffsetY = 0.0f;
		float mButtonSw = 0.0f;
		float mCenterShadowButtonPer = 0.0f;
		float mMainButtonRectButtonPer = 0.0f;
		VECTOR2 mBasicButtonDim;
		VECTOR2 mDefaultButtonDim;
		COLOR mButtonTextColor;
		COLOR mGuideTextColor;
		COLOR mGuideRectColor;
		COLOR mDraw_EnableButtonColor;
		COLOR mDeepShadowColor;
		COLOR mFaintShadowColor;
		COLOR mButtonBasicOnColor;
		COLOR mButtonBasicOffColor;
	};
	enum class ButtonState
	{
		EEnable,
		EDisable,
		EDraw_Enable
	};
	void SetState(ButtonState state) { mState = state; }
	ButtonState GetState() { return mState; }
	void SetBeforeState(ButtonState state) { mBeforeState = state; }
	ButtonState GetBeforeState() { return mBeforeState; }
protected:
	ButtonState mState;
	std::string mName;
	VECTOR2 mPosition;
	bool mHighlighted;
	const char* mText;
	VECTOR2 mTextOffset;
	VECTOR2 mNameOffset;
	bool mSoundFlag;
	bool mCancellFlag;
	std::function<void()> mOnClick;
	Game* mGame;
	VECTOR2 mRectButtonDim;
	COLOR mContainsColor;
	COLOR mNoContainsColor;
	ButtonState mBeforeState;
protected:
	DATA Data;
};

