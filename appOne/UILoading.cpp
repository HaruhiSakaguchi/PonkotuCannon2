#include "UILoading.h"
#include "Title.h"
#include "Game.h"
#include <sstream>

UILoading::UILoading(Game* game)
	: UIScreen(game)
	, mAlpha(255.0f)
	, mTime(0.0f)
	, mAddTextCnt(0)
	, mBeforeAddTextTime(0.0f)
	, mNextAddTextTime(0.0f)
	, mTextPos(0.0f, 0.0f)
{
	mStart = std::chrono::system_clock::now();
	Data = mGame->GetAllData()->loadingData;
	mString = Data.mText;
}

void UILoading::Closed()
{
	new Title(mGame);
}

void UILoading::Draw()
{
	rectMode(CORNER);
	fill(Data.mBackColor);
	rect(0.0f, 0.0f, width, height);
	textSize(Data.mTextSize);
	fill(Data.mTextColor.r, Data.mTextColor.g, Data.mTextColor.b, mAlpha);
	text(mString.c_str(), mTextPos.x, mTextPos.y);
}

void UILoading::Update()
{
	auto end = std::chrono::system_clock::now();
	auto dur = end - mStart;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	mTime = msec / 1000.0f;

	mAlpha += Data.mRev * Data.mPlusAlpha;

	std::ostringstream oss;
	oss << mString.c_str();

	if (mNextAddTextTime <= mTime && mTime != mBeforeAddTextTime)
	{
		if (mAddTextCnt < Data.mAddTextSize)
		{
			oss << Data.mAddText[mAddTextCnt];
			mAddTextCnt++;
		}
		else
		{
			mAddTextCnt = 0;
			oss.str("");
			oss.str().clear();
			oss << Data.mText;
		}
		mBeforeAddTextTime = mTime;
		mNextAddTextTime += Data.mAddTextInterval;
	}

	mString = oss.str();

	mTextPos = VECTOR2(width - (strlen(Data.mText) + Data.mAddTextSize) * Data.mTextSize / 2.0f, height - Data.mTextSize);

	if (Data.mMaxAlpha <= mAlpha || mAlpha <= 0.0f)
	{
		Data.mRev *= -1;
	}

	if (!mGame->GetRenderer()->GetContainer())
	{
		if (Data.mContainerLoadStartTime <= mTime)
		{
			mGame->GetRenderer()->LoadContainer();
		}
	}
	else if (Data.mChangeStateTime <= mTime)
	{
		Data.mBackColor.r++;
		Data.mBackColor.g++;
		Data.mBackColor.b++;

		if (Data.mStateChangeAlpha <= Data.mBackColor.r)
		{
			CloseMe();
		}
	}
}
