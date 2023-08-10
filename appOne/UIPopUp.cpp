#include "UIPopUp.h"
#include "window.h"
#include "graphic.h"

UIPopUp::UIPopUp(Game* game, const char* text, const VECTOR2& pos, int lifeSpan, const VECTOR2& vec)
	: UIScreen(game)
	, mLifeSpan(lifeSpan)
	, mPos(pos)
	, mVec(vec)
	, mTextSize(10.0f)
	, mTextColor(0, 0, 0)
	, mRectColor(0, 0, 0)
	, mTime(0)
	, mIsStrokeRect(true)
{
	mTitle = text;
	mStart = std::chrono::system_clock::now();
}

void UIPopUp::Update()
{
	mPos += mVec;
	--mRectColor.a;
	--mTextColor.a;

	if (mTime < mLifeSpan)
	{
		auto end = std::chrono::system_clock::now();
		auto dur = end - mStart;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		float time = msec / 1000.0f;
		mTime = (int)time;
	}
	else
	{
		CloseMe();
	}
}

void UIPopUp::Draw()
{
	textSize(mTextSize);
	rectMode(CENTER);

	if (mIsStrokeRect)
	{
		stroke(mRectColor);
		fill(0, 0, 0, 0);
		rect(mPos.x, mPos.y, mTextSize * mTitle.length() / 2.0f, mTextSize);
	}

	fill(mTextColor);
	text(mTitle.c_str(), mPos.x - (mTextSize * mTitle.length() / 2.0f) / 2.0f, mPos.y + mTextSize / 2.0f);
}
