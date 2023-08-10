#include "StageSelect.h"
#include "Reconfirm.h"
#include "Game.h"

StageSelect::StageSelect(class Game* game)
	: UIState(game)
{
	Data = mGame->GetAllData()->stageSelectData;

	mTitle = Data.mTitle;
	mTitleColor = Data.mTitleColor;
	mTextSize = Data.mTextSize;
	mBackPos = Data.mBackPos;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;

	mBackImg = mGame->GetAllData()->mDialog2;

	auto s1Button = AddRectButton(Data.mStage1Text,
		[this]() {
			auto rec = new Reconfirm(this, mGame, Data.mStage1ReconfirmGuide, [this]() {static_cast<Title*>(mGame->GetCurState())->IsChangePlay(); });
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDraw_Enable);
			}
			rec->SetNoEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				});
		}
		, Data.mStageGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	s1Button->SetTextOffset(s1Button->GetTextOffset() + Data.mStageGuideOffsetPos);

	auto s2Button = AddRectButton(Data.mStage2Text,
		[this]() {
			auto rec = new Reconfirm(this, mGame, Data.mStage2ReconfirmGuide, [this]() {static_cast<Title*>(mGame->GetCurState())->IsChangePlay(); });
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDraw_Enable);
			}
			rec->SetNoEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				});
		}
		, Data.mStageGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);
	s2Button->SetTextOffset(s2Button->GetTextOffset() + Data.mStageGuideOffsetPos);

	auto s3Button = AddRectButton(Data.mStage3Text,
		[this]() {
			auto rec = new Reconfirm(this, mGame, Data.mStage3ReconfirmGuide, [this]() {static_cast<Title*>(mGame->GetCurState())->IsChangePlay(); });
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDraw_Enable);
			}
			rec->SetNoEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				});
		}
		, Data.mStageGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	s3Button->SetTextOffset(s3Button->GetTextOffset() + Data.mStageGuideOffsetPos);


	auto Return = AddRectButton(Data.mReturnText,
		[this]() {
			CloseMe();
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);
	SetOtherUIButtonState(Button::ButtonState::EDraw_Enable);
	Return->ChangeCancellSound();

}

void StageSelect::Closed()
{
	SetOtherUIButtonBeforeState();
}


