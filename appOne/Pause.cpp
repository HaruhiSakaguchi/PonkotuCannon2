#include "Pause.h"
#include "Game.h"
#include "graphic.h"
#include "input.h"
#include "Quit.h"
#include "Title.h"
#include "Option.h"
#include "UIHelp.h"
#include "UIMainState.h"

Pause::Pause(Game* game)
	: UIState(game)
	, mQuitFlag(false)
{
	Data = mGame->GetAllData()->pauseData;
	mGame->SetState(Game::GameState::EPaused);

	mTitle = Data.mTitle;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;

	AddRectButton(Data.mReStartText,
		[this]() {
			SetOtherUIButtonBeforeState();
			mGame->SetState(Game::GameState::EGameplay);
			CloseMe();
		}
		, Data.mReStertButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto option = AddRectButton(Data.mOptionText,
		[this]() {
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDraw_Enable);
			}
			auto option = new Option(mGame);
			option->SetCloseEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				});
		}
		, Data.mOptionButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim

			);

	AddRectButton(Data.mReturnTitleText,
		[this]() {
			ChangeState();
		}
		, Data.mReturnTitleButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	AddRectButton(Data.mQuitText,
		[this]() {
			mQuitFlag = true;
			SetOtherUIButtonBeforeState();
			auto quit = new Quit(mGame);
			quit->SetNoEvent([this]()
				{
					for (auto button : mButtons)
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				}
			);
		}
		, Data.mQuitButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto help = AddRectButton(Data.mHelpText,
		[this]() {
			SetOtherUIButtonBeforeState();
			new UIHelp(mGame);
		}
		, Data.mHelpButtonGuide
			);

	help->SetPosition(help->GetPosition() + Data.mHelpButtonPosOffset);
	help->SetTextOffset(VECTOR2(-Data.mTextSize * strlen(help->GetText()) / 2.0f - Data.mTextSize * 1.5f, Data.mTextSize * 1.5f));

	setVolume(Data.mSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mPauseSoundVolumeOffset);
	playSound(Data.mSound);

	SetOtherUIButtonState(Button::ButtonState::EDisable);
}

void Pause::Closed()
{
	if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		setVolume(Data.mSound, mGame->GetSoundVolumeManager()->GetEffectVolume() + Data.mPauseSoundVolumeOffset);
		playSound(Data.mSound);
	}

}

void Pause::ProcessInput()
{
	UIScreen::ProcessInput();

	if (isTrigger(KEY_ENTER))
	{
		mGame->SetState(Game::GameState::EGameplay);
		CloseMe();
		SetOtherUIButtonBeforeState();
	}
}

void Pause::Draw()
{
	fill(mGame->GetAllData()->mPauseDisplayColor);
	rectMode(CORNER);
	noStroke();
	rect(0.0f, 0.0f, width, height);
	UIScreen::Draw();
}

void Pause::ChangeOption()
{
	if (!mQuitFlag)
	{
		mGame->GetActorManager()->ActorClear();
		mGame->GetCurState()->CloseMe();
		new Title(mGame);
		mGame->SetState(Game::GameState::EGameplay);
	}

}