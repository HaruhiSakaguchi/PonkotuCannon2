#include "Title.h"
#include "Game.h"
#include "input.h"
#include <sstream>
#include "sound.h" 
#include "Quit.h"
#include "Option.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "UIHelp.h"
#include "TransitionFade.h"

Title::Title(Game* game)
	: UIMainState(game)
	, mChangeStateFlag(false)
	, mIsChangePlay(false)
{
	Data = mGame->GetAllData()->titleData;
	mTitle = Data.mTitle;
	mTitleColor = Data.mTitleColor;
	mTextSize = Data.mTextSize;
	mBackImg = Data.mBackImg;
	mBackPos = Data.mBackPos;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;
	mMState = State::ETitle;
	mGame->SetCurState(this);
	mGame->SetState(Game::GameState::EPaused);

	if (mGame->GetRenderer()->GetTransition())
	{
		mGame->GetRenderer()->GetTransition()->inTrigger();
	}

	auto start = AddRectButton(Data.mStartText,
		[this]() {
			mGame->SetPhase(mGame->GetInitPhase());
			ChangeState();
			mGame->SetContinueFlag(true);
			mIsChangePlay = true;
		}
		, Data.mStartButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	start->SetTextOffset(start->GetTextOffset() + Data.mStartButtonGuideOffset);

	auto select = AddRectButton(Data.mStageSelectText,
		[this]() {
			new StageSelect(mGame);
		}
		, Data.mStageSelectButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	AddRectButton(Data.mOptionText,
		[this]()
		{
			auto option = new Option(mGame);
			option->SetCloseEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				}
			);
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDraw_Enable);
			}
		}
		, Data.mOptionButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	AddRectButton(Data.mQuitText,
		[this]() {
			new Quit(mGame);
		}
		, Data.mQuitButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto help = AddRectButton(Data.mHelpText,
		[this]() {
			new UIHelp(mGame);
		}
		, Data.mHelpButtonGuide
			);

	help->SetPosition(help->GetPosition() + Data.mPhaseFirstButtonOffsetPos);
	help->SetTextOffset(VECTOR2(-Data.mButtonTextSize * strlen(help->GetText()) / 2.0f - Data.mButtonTextSize * 1.5f, Data.mButtonTextSize / 2.0f));

	playLoopSound(Data.mBgm);
	setVolume(Data.mBgm, mGame->GetSoundVolumeManager()->GetVolume() + Data.mBgmSoundVolumeOffset);

}

Title::~Title()
{
	stopSound(Data.mBgm);
}

void Title::ChangeOption()
{
	if (mIsChangePlay)
	{
		new GamePlay(mGame);
	}
}

void Title::Update()
{
	if (!mChangeStateFlag)
	{
		mChangeStateFlag = true;
		ChangeState();
	}

	if (mGame->GetSoundVolumeManager()->GetBgmFlag())
	{
		setVolume(Data.mBgm, mGame->GetSoundVolumeManager()->GetVolume() + Data.mBgmSoundVolumeOffset);
		if (!mPlayBgmFlag)
		{
			playLoopSound(Data.mBgm);
			mPlayBgmFlag = true;
		}
	}
	else
	{
		stopSound(Data.mBgm);
		mPlayBgmFlag = false;
	}


	UIState::Update();

}




