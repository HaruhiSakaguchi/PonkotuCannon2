#include "GamePlay.h"
#include "StageClear.h"
#include "GameOver.h"
#include "Game.h"
#include "TransitionFade.h"
#include "Container.h"
#include "Stage.h"
#include "PlayerHome.h"
#include "Pause.h"

GamePlay::GamePlay(Game* game) :
	UIMainState(game)
	, mGameOverFlag(0)
	, mGameClearFlag(0)
	, mMap(nullptr)
	, mPlayBgmFlag(false)
	, mBgm(0)
	, mPauseButton(nullptr)
{
	Data = mGame->GetAllData()->playData;

	mBgm = Data.mBgm1;
	mSoundOffset = Data.mBgm1SoundVolumeOffset;
	mMState = State::EGamePlay;

	mMap = new Stage(mGame);
	mGame->GetActorManager()->SetStage(mMap);
	mMap->SetUp();

	mGame->GetRenderer()->GetTransition()->inTrigger();

	setVolume(mBgm, mGame->GetSoundVolumeManager()->GetVolume() + mSoundOffset);
	playLoopSound(mBgm);

	mGame->SetState(Game::GameState::EGameplay);
	mPauseButton = AddRectButton(Data.mPauseButtonText
		, [this]() {
			new Pause(mGame);
		});

	mPauseButton->SetPosition(VECTOR2(mPauseButton->GetPosition().x, mGame->GetAllData()->buttonData.mButtonTextSize));

}

GamePlay::~GamePlay()
{
	stopSound(mBgm);
}

void GamePlay::Update()
{
	if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay && mGameClearFlag == 0 && mGameOverFlag == 0)
	{
		if ((mGame->GetActorManager()->GetEnemies().empty() && mGame->GetActorManager()->GetWeapons().empty()) && !mGame->GetActorManager()->GetEHome())
		{
			new StageClear(mGame);
			stopSound(mBgm);
			mGameClearFlag = 1;
			CloseMe();
		}
		else if (mGame->GetActorManager()->GetPSide().empty())
		{
			new GameOver(mGame);
			stopSound(mBgm);
			mGameOverFlag = 1;
			CloseMe();
		}
	}

	if (mGame->GetSoundVolumeManager()->GetBgmFlag())
	{
		setVolume(mBgm, mGame->GetSoundVolumeManager()->GetVolume() + mSoundOffset);
		if (!mPlayBgmFlag)
		{
			playLoopSound(mBgm);
			mPlayBgmFlag = true;
		}
	}
	else
	{
		stopSound(mBgm);
		mPlayBgmFlag = false;
	}

	if (mGame->GetState() != Game::GameState::EGameplay)
	{
		mPauseButton->SetState(Button::ButtonState::EDraw_Enable);
	}
	else
	{
		mPauseButton->SetState(Button::ButtonState::EEnable);
	}

}

void GamePlay::ChangeBgm()
{
	stopSound(mBgm);
	mBgm = Data.mBgm2;
	mSoundOffset = Data.mBgm2SoundVolumeOffset;
	setVolume(mBgm, mGame->GetSoundVolumeManager()->GetVolume() + mSoundOffset);
	playLoopSound(mBgm);
}

void GamePlay::Draw()
{
	UIScreen::Draw();
	textSize(mGame->GetAllData()->buttonData.mButtonTextSize);
	fill(mGame->GetAllData()->buttonData.mGuideTextColor);
	text(Data.mPauseHelpText, mPauseButton->GetPosition().x + mGame->GetAllData()->buttonData.mButtonTextSize, mPauseButton->GetPosition().y + mGame->GetAllData()->buttonData.mButtonTextSize / 2.0f);
}
