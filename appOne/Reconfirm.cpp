#include "Reconfirm.h"
#include "Game.h"
#include "TransitionFade.h"

Reconfirm::Reconfirm(class UIState* state, class Game* game, const char* name, std::function<void()>func)
	:UIState(game)
	, mName(name)
	, mOwner(state)
	, mFlag(false)
	, mYes(func)
	, mNo(nullptr)
{
	Data = mGame->GetAllData()->reconfirmData;

	mTitle = Data.mTitle;
	mBackPos = Data.mBackPos;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;
	mTitleColor = Data.mTitleColor;
	mBackImg = mGame->GetAllData()->mDialog2;

	AddRectButton(Data.mYesText,
		[this]() {
			mFlag = true;
			CloseMe();
			mGame->SetContinueFlag(false);
			mYes();
			mOwner->CloseMe();
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto no = AddRectButton(Data.mNoText,
		[this]() {
			if (mNo)
			{
				mNo();
			}
			CloseMe();
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	no->ChangeCancellSound();

}

void Reconfirm::Closed()
{
	if (mFlag)
	{
		mGame->GetRenderer()->GetTransition()->outTrigger();
	}
	if (!mNo)
	{
		SetOtherUIButtonBeforeState();
	}
}

void Reconfirm::draw()
{
	textSize(Data.mReconfirmTextSize);
	fill(Data.mReconfirmTextColor);
	text(mName.c_str(), mTitlePos.x - (mName.length() / 4.0f) * Data.mReconfirmTextSize, mTitlePos.y + Data.mReconfirmTextOffsetY);
}
