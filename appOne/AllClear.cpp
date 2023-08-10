#include "AllClear.h"
#include "Quit.h"
#include "Title.h"
#include "Game.h"
#include "TransitionFade.h"

AllClear::AllClear(class Game* game)
	: UIMainState(game)
	, mIsChangeTitle(false)
{
	Data = mGame->GetAllData()->allClearData;

	mButtonPos = Data.mButtonPos;
	mGame->GetRenderer()->GetTransition()->inTrigger();
	mMState = State::EAllClear;

	AddRectButton(Data.mReturnTitleText,
		[this]() {
			mGame->SetPhase(mGame->GetInitPhase());
			mIsChangeTitle = true;
			ChangeState();
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	AddRectButton(Data.mQuitText,
		[this]() {
			new Quit(mGame);
		}
		, nullptr
			, mGame->GetAllData()->buttonData.mBasicButtonDim
			);

	if (mGame->GetSoundVolumeManager()->GetBgmFlag())
	{
		playLoopSound(Data.mBgm);
		setVolume(Data.mBgm, mGame->GetSoundVolumeManager()->GetVolume());
	}
}

AllClear::~AllClear()
{
	stopSound(Data.mBgm);
}

void AllClear::ChangeOption()
{
	if (mIsChangeTitle)
	{
		new Title(mGame);
	}
}

void AllClear::draw()
{
	rectMode(CORNER);
	image(Data.mImg, 0.0f, 0.0f);
	rectMode(CENTER);
}

void AllClear::Update()
{
	setVolume(Data.mBgm, mGame->GetSoundVolumeManager()->GetVolume());
	UIState::Update();
}