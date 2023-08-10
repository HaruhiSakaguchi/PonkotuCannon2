#include "UIButton.h"
#include "Game.h"
#include "input.h"

Button::Button(const char* name, std::function<void()> onClick,
	const VECTOR2& pos, Game* game, const char* text, const VECTOR2& textOffset)
	: mGame(game)
	, mName(name)
	, mPosition(pos)
	, mOnClick(onClick)
	, mText(text)
	, mTextOffset(textOffset)
	, mHighlighted(false)
	, mSoundFlag(false)
	, mState(Button::ButtonState::EEnable)
	, mBeforeState(mState)
	, mCancellFlag(false)
{
	Data = mGame->GetAllData()->buttonData;

	if (mText)
	{
		mTextOffset = VECTOR2(strlen(mText) / 4.0f * Data.mGuideTextSize, Data.mGuideTextSize / 2.0f);
	}
}

bool Button::ContainsPoint(const VECTOR2& pt, bool flag)
{
	bool no = true;

	no = pt.x < (mPosition.x - mRectButtonDim.x / 2.0f) ||
		pt.x >(mPosition.x + mRectButtonDim.x / 2.0f) ||
		pt.y < (mPosition.y - mRectButtonDim.y / 2.0f) ||
		pt.y >(mPosition.y + mRectButtonDim.y / 2.0f);

	if (mState != ButtonState::EEnable)
	{
		no = true;
	}

	mHighlighted = !no;

	//ボタンの外にマウスカーソルがあったら次にボタンに触れたときに音声を再生するようにする
	if (no)
	{
		mSoundFlag = false;
	}


	return !no;
}

void Button::OnClick()
{
	// アタッチされた関数ハンドラがあれば呼び出す。
	if (mOnClick && mState == Button::ButtonState::EEnable)
	{
		mOnClick();
		if (!mCancellFlag)
		{
			setVolume(Data.mClickSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mClickSoundVolumeOffset);
			playSound(Data.mClickSound);
		}
		else
		{
			setVolume(Data.mCancellSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mCancellSoundVolumeOffset);
			playSound(Data.mCancellSound);
		}
	}
}

void Button::Draw()
{
	// ボタン画像表示
	int buttonImg = 0;
	bool mChangeImageFlag = false;

	if (mState != Button::ButtonState::EDisable)
	{
		if (!mChangeImageFlag)
		{
			VECTOR2 mousePos = VECTOR2(mouseX, mouseY);
			if (ContainsPoint(mousePos) && GetText())
			{
				DrawGuide();
			}
		}


		DrawRectButton();


		// ボタン文字表示
		textSize(Data.mButtonTextSize);
		VECTOR2 pos;
		pos.x = mPosition.x - mName.length() * Data.mButtonTextSize / 4.0f + mNameOffset.x;//半角文字のみ対応
		pos.y = mPosition.y + Data.mButtonTextSize / 2.0f - Data.mTopShadowSw + mNameOffset.y;
		fill(Data.mButtonTextColor);
		if (mRectButtonDim.x < mRectButtonDim.y)
		{
			pos.x = mPosition.x - Data.mButtonTextSize / 2.0f + mNameOffset.x;
			pos.y = mPosition.y + mNameOffset.y;
			for (int i = 0; i < (int)(mName.length() / 2); i++)
			{
				std::string name = mName.substr(i * 2, 2);//全角なので2倍する
				pos.y += Data.mButtonTextSize * i;
				text(name.c_str(), pos.x, pos.y);
			}
		}
		else
		{
			text(mName.c_str(), pos.x, pos.y);
		}
	}

	if (mState == Button::ButtonState::EDraw_Enable)
	{
		VECTOR2 Dim;
		Dim = mRectButtonDim;

		noStroke();
		fill(Data.mDraw_EnableButtonColor);
		rect(mPosition.x, mPosition.y, Dim.x, Dim.y);
	}
}

void Button::Update()
{
	//ボタンの上にマウスカーソルがあったら一度だけ呼び出す。ボタンの外に出るとまた音を鳴らすことができるようになる。
	ContainsSound();
	mSoundFlag = true;
	setVolume(Data.mClickSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mClickSoundVolumeOffset);
	setVolume(Data.mContainsSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mContainsSoundVolumeOffset);
	setVolume(Data.mCancellSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mCancellSoundVolumeOffset);
}

void Button::DrawGuide()
{
	if (mState == Button::ButtonState::EEnable)
	{
		VECTOR2 pos = mPosition + mTextOffset;

		fill(Data.mGuideTextColor);
		textSize(Data.mGuideTextSize);
		text(mText, pos.x, pos.y);
		stroke(Data.mGuideTextColor);
		strokeWeight(Data.mGuideRectSw);
		rectMode(CORNER);
		fill(Data.mGuideRectColor);
		rect(pos.x, pos.y - Data.mGuideTextSize, strlen(mText) * Data.mGuideTextSize / 2.0f, Data.mGuideTextSize);
		rectMode(CENTER);
	}
}

void Button::DrawRectButton()
{
	if (mName.length() * Data.mButtonTextSize / 2.0f > mRectButtonDim.x)
	{
		mRectButtonDim.x = mName.length() * Data.mButtonTextSize / 2.0f;
	}

	COLOR color = mHighlighted ? mContainsColor : mNoContainsColor;
	stroke(color);
	strokeWeight(Data.mButtonSw);
	fill(color);
	rect(mPosition.x, mPosition.y, mRectButtonDim.x, mRectButtonDim.y);
	fill(Data.mDeepShadowColor);
	noStroke();
	rect(mPosition.x, mPosition.y + mRectButtonDim.y / 4.0f, mRectButtonDim.x + Data.mButtonSw, mRectButtonDim.y / 4.0f + Data.mButtonSw);
	fill(Data.mFaintShadowColor);
	noStroke();
	rect(mPosition.x, mPosition.y + mRectButtonDim.y * (1.0f - Data.mCenterShadowButtonPer) / 2.0f, mRectButtonDim.x + Data.mButtonSw, mRectButtonDim.y * Data.mCenterShadowButtonPer + Data.mButtonSw);
	fill(color);
	stroke(color);
	rect(mPosition.x, mPosition.y + mRectButtonDim.y * (1.0f - Data.mMainButtonRectButtonPer) / 2.0f - (mRectButtonDim.y * Data.mCenterShadowButtonPer + Data.mButtonSw), mRectButtonDim.x + Data.mButtonSw, mRectButtonDim.y * Data.mMainButtonRectButtonPer + Data.mButtonSw);
	VECTOR2 sp = mPosition - mRectButtonDim / 2.0f - VECTOR2(Data.mTopShadowSw, Data.mTopShadowSw);
	VECTOR2 ep = sp + VECTOR2(mRectButtonDim.x + Data.mTopShadowSw, 0.0f);
	fill(Data.mFaintShadowColor);
	stroke(Data.mFaintShadowColor);
	strokeWeight(Data.mTopShadowSw);
	line(sp.x, sp.y, ep.x, ep.y);
}

void Button::ContainsSound()
{
	if (mState == Button::ButtonState::EEnable)
	{
		setVolume(Data.mContainsSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mContainsSoundVolumeOffset);
		playSound(Data.mContainsSound);
	}
}

void Button::ConvertReverseButtonGuideTextPos()
{
	mTextOffset = (VECTOR2(mTextOffset.x * -3.0f, mTextOffset.y));
}
