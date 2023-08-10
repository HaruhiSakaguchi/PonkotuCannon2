#include "Quit.h"
#include "Game.h"

Quit::Quit(Game* game)
	: UIState(game)
	, mNoEvent(nullptr)
{
	Data = mGame->GetAllData()->quitData;

	mBackPos = Data.mBackPos;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;
	mBackImg = mGame->GetAllData()->mDialog2;
	mTitle = Data.mTitle;
	mTitleColor = Data.mTitleColor;
	mTextSize = Data.mTextSize;

	AddRectButton(Data.mYesText,
		[this]() {

			ChangeState();
			mGame->GetCurState()->SetMState(UIMainState::State::EQuit);
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto no = AddRectButton(Data.mNoText,
		[this]() {
			CloseMe();
			if (mNoEvent)
			{
				mNoEvent();
			}

		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	no->ChangeCancellSound();

	mNoEvent = ([this]()
		{
			SetOtherUIButtonBeforeState();
		}
	);

	SetOtherUIButtonState(Button::ButtonState::EDraw_Enable);

}

void Quit::ChangeOption()
{
	mGame->SetState(Game::GameState::EQuit);
}



