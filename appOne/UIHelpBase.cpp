#include "UIHelpBase.h"
#include "UIButton.h"
#include "Game.h"

UIHelpBase::UIHelpBase(class Game* game)
	: UIScreen(game)
	, mImgNum(0)
	, mNextButton(nullptr)
	, mReturnButton(nullptr)
{
	Data = mGame->GetAllData()->helpData;
	auto CloseButton = AddRectButton(
		Data.mCloseText,
		[this]() {
			CloseMe();
		}
		, Data.mCloseButtonGuide
			);

	CloseButton->SetPosition(Data.mCloseButtonPos);
	CloseButton->SetTextOffset(VECTOR2(-CloseButton->GetTextOffset().x * 3.0f + mGame->GetAllData()->buttonData.mButtonTextSize * 2.5f, CloseButton->GetTextOffset().y));
	CloseButton->ChangeCancellSound();
	SetOtherUIButtonState(Button::ButtonState::EDisable);

	AddNextButton();
	AddReturnButton();
}

UIHelpBase::~UIHelpBase()
{
	mImgs.clear();
}

void UIHelpBase::Update()
{
	if (0 < mImgNum)
	{
		mReturnButton->SetState(Button::ButtonState::EEnable);
	}
	else
	{
		mReturnButton->SetState(Button::ButtonState::EDisable);
	}

	if (mImgNum < mImgs.size() - 1)
	{
		mNextButton->SetState(Button::ButtonState::EEnable);
	}
	else
	{
		mNextButton->SetState(Button::ButtonState::EDisable);
	}
}

void UIHelpBase::draw()
{
	rectMode(CORNER);
	if (!mImgs.empty())
	{
		image(mImgs[mImgNum], 0.0f, 0.0f);
	}
	rectMode(CENTER);
}

void UIHelpBase::Closed()
{
	SetOtherUIButtonBeforeState();
}

void UIHelpBase::AddNextButton()
{
	mNextButton = AddRectButton(
		Data.mNextText,
		[this]() {
			mImgNum++;
		}
		, Data.mNextButtonGuide
			);

	mNextButton->SetPosition(Data.mNextButtonPos);
	mNextButton->SetTextOffset(VECTOR2(-mNextButton->GetTextOffset().x * 3.0f, mNextButton->GetTextOffset().y));

}

void UIHelpBase::AddReturnButton()
{
	mReturnButton = AddRectButton(
		Data.mReturnText,
		[this]() {
			mImgNum--;
		}
		, Data.mReturnButtonGuide
			);

	mReturnButton->SetPosition(Data.mReturnButtonPos);
}
