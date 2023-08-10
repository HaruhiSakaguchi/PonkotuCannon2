#include "GameOver.h"
#include "Title.h"
#include "Quit.h"
#include "GamePlay.h"
#include "Reconfirm.h"
#include "Game.h"
#include "TransitionFade.h"

GameOver::GameOver(Game* game)
	: UIMainState(game)
	, mTime(0.0f)
	, mIsRetryFlag(false)
	, mIsChangeTitleFlag(false)
{
	Data = mGame->GetAllData()->overData;

	mTitle = Data.mTitle;
	mTitleColor = Data.mTitleColor;
	mTextSize = Data.mTitleTextSize;
	mTitlePos = Data.mTitlePos;
	mButtonPos = Data.mButtonPos;
	mMState = State::EGameOver;

	mGame->GetRenderer()->GetTransition()->inTrigger();

	AddRectButton(Data.mReturnTitleText,
		[this]() {
			mIsChangeTitleFlag = true;
			ChangeState();
		}
		, Data.mReturnTitleButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	auto retryButton = AddRectButton(Data.mRetryText,
		[this]() {
			mIsRetryFlag = true;
			ChangeState();
		}
		, Data.mRetryButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	retryButton->SetTextOffset(retryButton->GetTextOffset() + Data.mRetryButtonPosOffset);

	AddRectButton(Data.mQuitText,
		[this]() {
			new Quit(mGame);
		}
		, Data.mQuitButtonGuide
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	if (mGame->GetSoundVolumeManager()->GetBgmFlag())
	{
		playSound(Data.mSound);
		setVolume(Data.mSound, mGame->GetSoundVolumeManager()->GetVolume());
	}
}

void GameOver::Update()
{
	setVolume(Data.mSound, mGame->GetSoundVolumeManager()->GetVolume());
	mTime += Data.mTitlePosAdvSpeed;
	VECTOR2 prePos = mTitlePos;
	VECTOR2 pos = VECTOR2(mTitlePos.x, mTitlePos.y + sinf(mTime) * Data.mMaxOffsetPosY);
	mTitlePos = prePos + (pos - prePos) * Data.mTitlePosAdvSpeed;
	UIState::Update();
}

void GameOver::ChangeOption()
{
	if (mIsRetryFlag && !mIsChangeTitleFlag)
	{
		mGame->GetActorManager()->ActorClear();
		new GamePlay(mGame);
		mGame->SetState(Game::GameState::EGameplay);
	}
	else if (!mIsRetryFlag && mIsChangeTitleFlag)
	{
		mGame->GetActorManager()->ActorClear();
		new Title(mGame);
		mGame->SetState(Game::GameState::EGameplay);
	}
}


