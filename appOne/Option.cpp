#include "Option.h"
#include "Game.h"

Option::Option(class Game* game)
	: UIState(game)
	, mVolume(0)
	, mEffectVolume(0)
	, mCloseEvent(nullptr)
{
	Data = mGame->GetAllData()->optionData;
	mTitle = Data.mTitle;
	mTitlePos = Data.mTitlePos;
	mTitleColor = Data.mTitleColor;
	mBackImg = mGame->GetAllData()->mDialog1;
	mBackPos = Data.mBackPos;
	mButtonPos = Data.mButtonPos;
	mVolume = mGame->GetSoundVolumeManager()->GetVolume();
	mEffectVolume = mGame->GetSoundVolumeManager()->GetEffectVolume();

	auto bvPlusButton = AddRectButton(Data.mPlusText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetSoundFlag())
			{
				//0から-4500までで音量調節
				//最小値を下回るともっと小さい値を入れて完全に音が聞こえないようにする
				if (mVolume <= Data.mMinVolume)
				{
					mVolume = Data.mMinVolume * 2;
				}
				if (mVolume == Data.mMinVolume * 2)
				{
					mVolume = Data.mMinVolume;
				}
				mVolume += Data.mOneVolume;
				if (mVolume > 0)
				{
					mVolume = 0;
				}
				mGame->GetSoundVolumeManager()->SetVolume(mVolume);
			}
		}
		, Data.mBGMVolumePlusButtonGuide
			);

	bvPlusButton->SetPosition(bvPlusButton->GetPosition() + Data.mBgmVolumeUpButtonOffsetPos);
	bvPlusButton->SetTextOffset(VECTOR2(-bvPlusButton->GetTextOffset().x * 3.0f, bvPlusButton->GetTextOffset().y));

	auto bvMinusButton = AddRectButton(Data.mMinusText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetSoundFlag())
			{
				mVolume -= Data.mOneVolume;
				if (mVolume <= Data.mMinVolume)
				{
					mVolume = Data.mMinVolume * 2;
				}
				mGame->GetSoundVolumeManager()->SetVolume(mVolume);
			}
		},
		Data.mBGMVolumeMinusButtonGuide
	);

	bvMinusButton->SetPosition(bvMinusButton->GetPosition() + Data.mBgmVolumeDownButtonOffsetPos);
	bvMinusButton->SetTextOffset(VECTOR2(-bvMinusButton->GetTextOffset().x * 3.0f, bvMinusButton->GetTextOffset().y) + bvPlusButton->GetPosition() - bvMinusButton->GetPosition());

	auto svPlusButton = AddRectButton(Data.mPlusText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetSoundFlag())
			{
				//0から-4500までで音量調節
				if (mEffectVolume <= Data.mMinVolume)
				{
					mEffectVolume = Data.mMinVolume * 2;
				}
				if (mEffectVolume == Data.mMinVolume * 2)
				{
					mEffectVolume = Data.mMinVolume;
				}
				mEffectVolume += Data.mOneVolume;
				if (mEffectVolume > 0)
				{
					mEffectVolume = 0;
				}
				mGame->GetSoundVolumeManager()->SetEffectVolume(mEffectVolume);
			}
		}

		, Data.mEffectVolumePlusButtonGuide
			);

	svPlusButton->SetPosition(svPlusButton->GetPosition() + Data.mEffectVolumeUpButtonOffsetPos);


	auto svMinusButton = AddRectButton(Data.mMinusText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetSoundFlag())
			{
				mEffectVolume -= Data.mOneVolume;
				if (mEffectVolume <= Data.mMinVolume)
				{
					mEffectVolume = Data.mMinVolume * 2;
				}
				mGame->GetSoundVolumeManager()->SetEffectVolume(mEffectVolume);
			}
		},
		Data.mEffectVolumeMinusButtonGuide
	);

	svMinusButton->SetPosition(svMinusButton->GetPosition() + Data.mEffectVolumeDownButtonOffsetPos);

	svPlusButton->SetTextOffset(svPlusButton->GetTextOffset() + svMinusButton->GetPosition() - svPlusButton->GetPosition());

	auto soundSwitchButton = AddRectButton(Data.mSoundSwitchText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetSoundFlag())
			{
				if (mVolume <= Data.mMinVolume * 2)
				{
					mVolume = Data.mMinVolume / 2;
					mEffectVolume = Data.mMinVolume / 2;
					mGame->GetSoundVolumeManager()->SetVolume(mVolume);
					mGame->GetSoundVolumeManager()->SetEffectVolume(mEffectVolume);
				}
				mGame->GetSoundVolumeManager()->SetTmpVolume(mGame->GetSoundVolumeManager()->GetVolume());
				mGame->GetSoundVolumeManager()->SetTmpEffectVolume(mGame->GetSoundVolumeManager()->GetEffectVolume());
				mVolume = Data.mMinVolume * 2;
				mEffectVolume = Data.mMinVolume * 2;
				mGame->GetSoundVolumeManager()->SetVolume(mVolume);
				mGame->GetSoundVolumeManager()->SetEffectVolume(mEffectVolume);
				mGame->GetSoundVolumeManager()->SetSoundFlag(false);
			}
			else
			{
				mVolume = mGame->GetSoundVolumeManager()->GetTmpVolume();
				mEffectVolume = mGame->GetSoundVolumeManager()->GetTmpEffectVolume();
				mGame->GetSoundVolumeManager()->SetVolume(mVolume);
				mGame->GetSoundVolumeManager()->SetEffectVolume(mEffectVolume);
				mGame->GetSoundVolumeManager()->SetSoundFlag(true);
			}

		},
		Data.mSoundSwitchButtonGuide
		, mGame->GetAllData()->buttonData.mBasicButtonDim
	);

	soundSwitchButton->SetPosition(soundSwitchButton->GetPosition() + Data.mSoundOnOffButtonOfsetPos);
	soundSwitchButton->SetTextOffset(soundSwitchButton->GetTextOffset() + VECTOR2(65.0f, 0.0f));

	auto bgmSwitchButton = AddRectButton(Data.mBGMSwitchText,
		[this]()
		{
			if (mGame->GetSoundVolumeManager()->GetBgmFlag())
			{
				mGame->GetSoundVolumeManager()->SetBgmFlag(false);
			}
			else
			{
				mGame->GetSoundVolumeManager()->SetBgmFlag(true);
			}
		},
		Data.mBGMSwitchButtonGuide
		, mGame->GetAllData()->buttonData.mBasicButtonDim

	);

	bgmSwitchButton->SetPosition(bgmSwitchButton->GetPosition() + Data.mSoundOnOffButtonOfsetPos);
	bgmSwitchButton->SetTextOffset(bgmSwitchButton->GetTextOffset() + VECTOR2(100.0f, 0.0f));

	auto camSyPlusButton = AddRectButton(Data.mPlusText,
		[this]()
		{
			if (mGame->GetCameraManager()->GetCameraSX() < Data.mMaxCameraS)
			{
				float cameraX = mGame->GetCameraManager()->GetCameraSX();
				cameraX += Data.mOneCameraS;
				mGame->GetCameraManager()->SetCameraSX(cameraX);
			}
		},
		Data.mCameraSYPlusButtonGuide
	);
	camSyPlusButton->SetPosition(camSyPlusButton->GetPosition() + Data.mCameraYUpButtonOffsetPos);

	auto camSyMinusButton = AddRectButton(Data.mMinusText,
		[this]()
		{
			if (mGame->GetCameraManager()->GetCameraSX() > Data.mOneCameraS)
			{
				float cameraX = mGame->GetCameraManager()->GetCameraSX();
				cameraX -= Data.mOneCameraS;
				mGame->GetCameraManager()->SetCameraSX(cameraX);
			}
		},
		Data.mCameraSYMinusButtonGuide
	);

	camSyMinusButton->SetPosition(camSyMinusButton->GetPosition() + Data.mCameraYDownButtonOffsetPos);
	camSyPlusButton->SetTextOffset(camSyPlusButton->GetTextOffset() + camSyMinusButton->GetPosition() - camSyPlusButton->GetPosition());

	auto camSxPlusButton = AddRectButton(Data.mPlusText,
		[this]()
		{
			if (mGame->GetCameraManager()->GetCameraSY() < Data.mMaxCameraS)
			{
				float cameraY = mGame->GetCameraManager()->GetCameraSY();
				cameraY += Data.mOneCameraS;
				mGame->GetCameraManager()->SetCameraSY(cameraY);
			}
		}
		,
			Data.mCameraSXPlusButtonGuide
	);

	camSxPlusButton->SetPosition(camSxPlusButton->GetPosition() + Data.mCameraXUpButtonOffsetPos);
	camSxPlusButton->SetTextOffset(VECTOR2(-camSxPlusButton->GetTextOffset().x * 3.0f, camSxPlusButton->GetTextOffset().y));

	auto camSxMinusButton = AddRectButton(Data.mMinusText,
		[this]()
		{
			if (mGame->GetCameraManager()->GetCameraSY() > Data.mOneCameraS)
			{
				float cameraY = mGame->GetCameraManager()->GetCameraSY();
				cameraY -= Data.mOneCameraS;
				mGame->GetCameraManager()->SetCameraSY(cameraY);
			}
		},
		Data.mCameraSXMinusButtonGuide
	);

	camSxMinusButton->SetPosition(camSxMinusButton->GetPosition() + Data.mCameraXDownButtonOffsetPos);
	camSxMinusButton->SetTextOffset(VECTOR2(-camSxMinusButton->GetTextOffset().x * 3.0f, camSxMinusButton->GetTextOffset().y) + camSxPlusButton->GetPosition() - camSxMinusButton->GetPosition());

	auto closeButton = AddRectButton(Data.mCloseText,
		[this]()
		{
			CloseMe();
		},
		Data.mCloseButtonGuide
		, mGame->GetAllData()->buttonData.mBasicButtonDim
	);

	closeButton->SetTextOffset(closeButton->GetTextOffset() + Data.mCloseButtonTextOffset);

	closeButton->SetPosition(closeButton->GetPosition() + Data.mCloseButtonOffsetPos);
	closeButton->ChangeCancellSound();

	auto resetButton = AddRectButton(Data.mResetText,
		[this]()
		{
			mGame->GetSoundVolumeManager()->SetVolume(Data.mDefaultBgmBolume);
			mGame->GetSoundVolumeManager()->SetEffectVolume(Data.mDefaultEffectBolume);
			mGame->GetSoundVolumeManager()->SetBgmFlag(true);
			mGame->GetSoundVolumeManager()->SetSoundFlag(true);
			mGame->GetCameraManager()->SetCameraSX(Data.mDefaultCameraSX);
			mGame->GetCameraManager()->SetCameraSY(Data.mDefaultCameraSY);

		}
		, Data.mResetButtonGuide
			, Data.mResetButtonDim
			);

	resetButton->SetPosition(closeButton->GetPosition() + Data.mResetButtonOffset);
	resetButton->SetTextOffset(resetButton->GetTextOffset() + Data.mResetButtonTextOffset);
}

void Option::Closed()
{
	if (mCloseEvent)
	{
		mCloseEvent();
	}
}


void Option::draw()
{
	int bVol = 0;
	int eVol = 0;
	COLOR color = Data.mOnColor;
	if (mGame->GetSoundVolumeManager()->GetSoundFlag())
	{
		bVol = mGame->GetSoundVolumeManager()->GetVolume() / Data.mOneVolume + 10;
		if (mGame->GetSoundVolumeManager()->GetVolume() == Data.mMinVolume * 2)
		{
			bVol = 0;
		}
		eVol = mGame->GetSoundVolumeManager()->GetEffectVolume() / Data.mOneVolume + 10;
		if (mGame->GetSoundVolumeManager()->GetEffectVolume() == Data.mMinVolume * 2)
		{
			eVol = 0;
		}
	}
	else
	{
		bVol = mGame->GetSoundVolumeManager()->GetTmpVolume() / Data.mOneVolume + 10;
		if (mGame->GetSoundVolumeManager()->GetTmpVolume() == Data.mMinVolume * 2)
		{
			bVol = 0;
		}
		eVol = mGame->GetSoundVolumeManager()->GetTmpEffectVolume() / Data.mOneVolume + 10;
		if (mGame->GetSoundVolumeManager()->GetTmpEffectVolume() == Data.mMinVolume * 2)
		{
			eVol = 0;
		}
		color = Data.mOffColor;
	}

	float bOffset = 0;
	float eOffset = 0;
	//Volumeの値が2桁なら値を表示する場所をずらす
	if (bVol < 10)
	{
		bOffset = -Data.mTextSize / 4.0f;
	}
	else
	{
		bOffset = -Data.mTextSize / 2.0f;
	}

	if (eVol < 10)
	{
		eOffset = -Data.mTextSize / 4.0f;
	}
	else
	{
		eOffset = -Data.mTextSize / 2.0f;
	}

	textSize(Data.mTextSize);
	fill(color);
	text("volume", Data.mVolumeTextOffsetPos.x, Data.mVolumeTextOffsetPos.y);
	text("BGM", Data.mBgmTextOffsetPos.x, Data.mBgmTextOffsetPos.y);
	text("効果音", Data.mEffectTextOffsetPos.x, Data.mEffectTextOffsetPos.y);
	text(bVol, bOffset + Data.mBVolTextOffsetPos.x, Data.mBVolTextOffsetPos.y);
	text(eVol, eOffset + Data.mEVolTextOffsetPos.x, Data.mEVolTextOffsetPos.y);

	const char* onOff;
	if (mGame->GetSoundVolumeManager()->GetSoundFlag())
	{
		onOff = "SOUND : ON";
	}
	else
	{
		onOff = "SOUND : OFF";
	}

	text(onOff, Data.mSoundOnOffTextOffsetPos.x, Data.mSoundOnOffTextOffsetPos.y);

	if (mGame->GetSoundVolumeManager()->GetBgmFlag())
	{
		onOff = "BGM : ON";
	}
	else
	{
		onOff = "BGM : OFF";
	}

	text(onOff, Data.mBgmOnOffTextOffsetPos.x, Data.mBgmOnOffTextOffsetPos.y);

	fill(Data.mOnColor);
	text("カメラ感度", Data.mCameraSTextOffsetPos.x, Data.mCameraSTextOffsetPos.y);
	text("X", Data.mCameraSXTextOffsetPos.x, Data.mCameraSXTextOffsetPos.y);
	text("Y", Data.mCameraSYTextOffsetPos.x, Data.mCameraSYTextOffsetPos.y);

	//100倍して小数点以下切り捨て
	int sx = (int)roundf(mGame->GetCameraManager()->GetCameraSX() * 100.0f);
	int sy = (int)roundf(mGame->GetCameraManager()->GetCameraSY() * 100.0f);

	float offsetXX = 0.0f;
	float offsetYX = 0.0f;
	if (sx == 10)
	{
		offsetXX = -Data.mTextSize / 4.0f;
	}
	if (sy == 10)
	{
		offsetYX = -Data.mTextSize / 4.0f;
	}

	text(sx, Data.mCameraSXNumTextOffsetPos.x + offsetXX, Data.mCameraSXNumTextOffsetPos.y);
	text(sy, Data.mCameraSYNumTextOffsetPos.x + offsetYX, Data.mCameraSYNumTextOffsetPos.y);

}