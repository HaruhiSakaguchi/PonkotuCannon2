#include "Container.h"
#include "graphic.h"

void SetAllData(struct Container& ad)
{
	//manager
	{
		ad.mWidth = 1920.0f;
		ad.mHeight = 1080.0f;
		ad.mFullScreenFlag = 1;
		ad.mInitAllSoundVolume = -450;
		ad.mInitEffectSoundVolume = -1300;
		ad.mBackGroundColor = COLOR(64, 128, 255);
		ad.mNormalDisplayColor = COLOR(0, 0, 0, 0);
		ad.mPauseDisplayColor = COLOR(0, 0, 0, 128);
	}
	//actor共通
	{
		ad.mDeadSoundVolumeOffset = -600;
		ad.mGurdSoundVolumeOffset = -700;
		ad.mCloseSoundVolumeOffset = -300;
		ad.mDamageSoundVolumeOffset = -1050;
	}
	//renderer
	{
		ad.rendererData.mAmbient = 0.8f;
		ad.rendererData.mPerspectiveAngle = 0.6f;
		ad.rendererData.mPerspectiveAspect = 1.7777777f;
		ad.rendererData.mPerspectiveNear = 0.1f;
		ad.rendererData.mPerspectiveFar = 100.0f;
		ad.rendererData.mCamPos = VECTOR(0.0f, 1.0f, 0.0f);
		ad.rendererData.mLookat = VECTOR(0.0f, 2.0f, 0.0f);
		ad.rendererData.mUp = VECTOR(0.0f, 1.0f, 0.0f);
		ad.rendererData.mLightPos = VECTOR(0.0f, 1.0f, 0.1f);
		ad.rendererData.mDiffuse = COLOR(1, 1, 1, 1);
	}
	//button
	{
		ad.buttonData.mButtonTextSize = 30.0f;
		ad.buttonData.mGuideTextSize = 30.0f;
		ad.buttonData.mClickSoundVolumeOffset = -1350;
		ad.buttonData.mContainsSoundVolumeOffset = -1000;
		ad.buttonData.mCancellSoundVolumeOffset = -1200;

		ad.buttonData.mGuideRectSw = 1.0f;
		ad.buttonData.mBasicOffsetY = 69.0f;
		ad.buttonData.mTopShadowSw = 2.0f;
		ad.buttonData.mButtonSw = 5.0f;
		ad.buttonData.mMainButtonRectButtonPer = 0.0125f;
		ad.buttonData.mCenterShadowButtonPer = 0.05f;
		ad.buttonData.mDefaultButtonDim = VECTOR2(44.0f, 44.0f);
		ad.buttonData.mBasicButtonDim = VECTOR2(240.0f, 49.0f);
		ad.buttonData.mButtonTextColor = COLOR(0, 0, 0);
		ad.buttonData.mGuideTextColor = COLOR(0, 0, 0);
		ad.buttonData.mGuideRectColor = COLOR(0, 0, 0, 0);
		ad.buttonData.mDraw_EnableButtonColor = COLOR(128, 128, 128, 128);
		ad.buttonData.mDeepShadowColor = COLOR(128, 128, 128, 64);
		ad.buttonData.mFaintShadowColor = COLOR(64, 64, 64, 64);
		ad.buttonData.mButtonBasicOnColor = COLOR(200, 180, 116);
		ad.buttonData.mButtonBasicOffColor = COLOR(99, 163, 200);
	}
	//title
	{
		ad.titleData.mTitle = "Ponkotu Cannon2";
		ad.titleData.mStartText = "はじめから";
		ad.titleData.mStartButtonGuide = "ゲームを始めます";
		ad.titleData.mStageSelectText = "ステージセレクト";
		ad.titleData.mStageSelectButtonGuide = "ステージを選んで始めます";
		ad.titleData.mQuitText = "ゲームを終わる";
		ad.titleData.mQuitButtonGuide = "ゲームを終わります";
		ad.titleData.mHelpText = "？";
		ad.titleData.mHelpButtonGuide = "ヘルプを開きます";
		ad.titleData.mOptionText = "オプション";
		ad.titleData.mOptionButtonGuide = "オプションを開きます";
		ad.titleData.mTextSize = 200.0f;
		ad.titleData.mBgmSoundVolumeOffset = -950;
		ad.titleData.mButtonTextSize = 30.0f;
		ad.titleData.mBackPos = VECTOR2(ad.mWidth / 2, ad.mHeight / 2);
		ad.titleData.mTitlePos = VECTOR2(ad.mWidth / 2, ad.mHeight / 2 - 100.0f);
		ad.titleData.mButtonPos = VECTOR2(ad.mWidth / 2, ad.titleData.mTitlePos.y + 200.0f);
		ad.titleData.mPhaseFirstButtonOffsetPos = VECTOR2(ad.mWidth / 2.0f - 50.0f, -ad.mHeight + 200.0f);
		ad.titleData.mStartButtonGuideOffset = VECTOR2(30.0f, 0.0f);
		ad.titleData.mTitleColor = COLOR(128, 128, 50);
	}
	//quit
	{
		ad.quitData.mTitle = "ゲームを終了しますか？";
		ad.quitData.mYesText = "はい";
		ad.quitData.mNoText = "いいえ";
		ad.quitData.mTextSize = 40.0f;
		ad.quitData.mBackPos = VECTOR2(ad.mWidth / 2, 400.0f);
		ad.quitData.mTitlePos = VECTOR2(ad.mWidth / 2, ad.quitData.mBackPos.y - 70.0f);
		ad.quitData.mButtonPos = VECTOR2(ad.mWidth / 2, ad.quitData.mTitlePos.y + 140.0f);
		ad.quitData.mTitleColor = COLOR(0, 0, 0);
	}
	//option
	{
		ad.optionData.mTitle = "オプション";
		ad.optionData.mResetText = "リセット";
		ad.optionData.mResetButtonGuide = "デフォルトの状態に戻します";
		ad.optionData.mPlusText = "＋";
		ad.optionData.mMinusText = "ー";
		ad.optionData.mCloseText = "閉じる";
		ad.optionData.mCloseButtonGuide = "オプションを閉じます";
		ad.optionData.mBGMSwitchText = "BGM ON/OFF";
		ad.optionData.mBGMSwitchButtonGuide = "BGMのON/OFFを切り替えます";
		ad.optionData.mSoundSwitchText = "SOUND ON/OFF";
		ad.optionData.mSoundSwitchButtonGuide = "すべての音声のON/OFFを切り替えます";
		ad.optionData.mBGMVolumePlusButtonGuide = "BGMの音量を上げます";
		ad.optionData.mBGMVolumeMinusButtonGuide = "BGMの音量を下げます";
		ad.optionData.mEffectVolumePlusButtonGuide = "効果音の音量を上げます";
		ad.optionData.mEffectVolumeMinusButtonGuide = "効果音の音量を下げます";
		ad.optionData.mCameraSXPlusButtonGuide = "カメラX軸の感度を上げます";
		ad.optionData.mCameraSXMinusButtonGuide = "カメラX軸の感度を下げます";
		ad.optionData.mCameraSYPlusButtonGuide = "カメラY軸の感度を上げます";
		ad.optionData.mCameraSYMinusButtonGuide = "カメラY軸の感度を下げます";
		ad.optionData.mMinVolume = -4500;
		ad.optionData.mOneVolume = 450;
		ad.optionData.mOneCameraS = 0.01f;
		ad.optionData.mMaxCameraS = 0.09f;
		ad.optionData.mTextSize = 30.0f;
		ad.optionData.mDefaultBgmBolume = -1300;
		ad.optionData.mDefaultEffectBolume = -450;
		ad.optionData.mDefaultCameraSX = 0.04f;
		ad.optionData.mDefaultCameraSY = 0.02f;
		ad.optionData.mTitlePos = VECTOR2(ad.mWidth / 2, 300.0f);
		ad.optionData.mBackPos = VECTOR2(ad.optionData.mTitlePos.x, ad.optionData.mTitlePos.y + 200.0f);
		ad.optionData.mButtonPos = VECTOR2(ad.optionData.mBackPos.x, ad.optionData.mBackPos.y - 100.0f);
		ad.optionData.mBgmVolumeUpButtonOffsetPos = VECTOR2(-100.0f, 0.0f);
		ad.optionData.mBgmVolumeUpButtonGuideOffsetPos = VECTOR2(-600 + 30 / 4 + 30 / 2 + 69 * 0.75f - 69.0f / 2 - 3.525f);
		ad.optionData.mBgmVolumeDownButtonOffsetPos = VECTOR2(-200.0f, -69.0f);
		ad.optionData.mBgmVolumeDownButtonGuideOffsetPos = VECTOR2(-500 + 30 / 4 + 30 / 2 + 69 * 0.75f - 69.0f / 2 - 3.525f);
		ad.optionData.mEffectVolumeUpButtonOffsetPos = VECTOR2(200.0f, -138.0f);
		ad.optionData.mEffectVolumeUpButtonGuideOffsetPos = VECTOR2(-150.0f + 69.0f / 4.0f, 0);
		ad.optionData.mEffectVolumeDownButtonOffsetPos = VECTOR2(100.0f, -207.0f);
		ad.optionData.mEffectVolumeDownButtonGuideOffsetPos = VECTOR2(-50.0f + 69.0f / 4.0f, 0);
		ad.optionData.mSoundOnOffButtonOfsetPos = VECTOR2(0.0f, -207.0f);
		ad.optionData.mSoundOnOffButtonGuideOfsetPos = VECTOR2(100.0f, 0);
		ad.optionData.mCameraYUpButtonOffsetPos = VECTOR2(200.0f, -138.0f);
		ad.optionData.mCameraYUpButtonGuideOffsetPos = VECTOR2(-175 + 30 / 4 + 30 / 2 + 3.525f, 0);
		ad.optionData.mCameraXUpButtonOffsetPos = VECTOR2(-100.0f, -69.0f * 4);
		ad.optionData.mCameraXUpButtonGuideOffsetPos = VECTOR2(-750 + 30 / 4 + 30 / 2 + 69 * 0.75f - 15 + 3.75f - 69.0f / 4.0f, 0);
		ad.optionData.mCameraYDownButtonOffsetPos = VECTOR2(100.0f, -207.0f);
		ad.optionData.mCameraYDownButtonGuideOffsetPos = VECTOR2(-75 + 30 / 4 + 30 / 2 + 3.525f, 0);
		ad.optionData.mCameraXDownButtonOffsetPos = VECTOR2(-200, -69.0f * 5);
		ad.optionData.mCameraXDownButtonGuideOffsetPos = VECTOR2(-650 + 30 / 4 + 30 / 2 + 69 * 0.75f - 15 + 3.75f - 69.0f / 4.0f, 0);
		ad.optionData.mCloseButtonOffsetPos = VECTOR2(0, -69.0f * 5);
		ad.optionData.mVolumeTextOffsetPos = VECTOR2(ad.mWidth / 2.0f - 45.0f, ad.mHeight / 2.0f - 185.0f);
		ad.optionData.mBgmTextOffsetPos = VECTOR2(ad.mWidth / 2.0f - 173.5f, ad.mHeight / 2.0f - 175.0f);
		ad.optionData.mEffectTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + 104.0f, ad.mHeight / 2.0f - 175.0f);
		ad.optionData.mBVolTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + -151.0f, ad.mHeight / 2.0f - 125.0f);
		ad.optionData.mEVolTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + +149.0f, ad.mHeight / 2.0f - 125.0f);
		ad.optionData.mSoundOnOffTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + 150.0f, ad.mHeight / 2.0f - 59.0f);
		ad.optionData.mBgmOnOffTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + 150.0f, ad.mHeight / 2.0f + 10.0f);
		ad.optionData.mCameraSTextOffsetPos = VECTOR2(ad.mWidth / 2.0f - 75.0f, ad.mHeight / 2.0f + 79.0f);
		ad.optionData.mCameraSXTextOffsetPos = VECTOR2(ad.mWidth / 2.0f - 158.5f, ad.mHeight / 2.0f + 99.0f);
		ad.optionData.mCameraSYTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + 141.5f, ad.mHeight / 2.0f + 99.0f);
		ad.optionData.mCameraSXNumTextOffsetPos = VECTOR2(ad.mWidth / 2.0f + 141.5f, ad.mHeight / 2.0f + 148.0f);
		ad.optionData.mCameraSYNumTextOffsetPos = VECTOR2(ad.mWidth / 2.0f - 158.5f, ad.mHeight / 2.0f + 148.0f);
		ad.optionData.mResetButtonOffset = VECTOR2(265.0f, 0.0f);
		ad.optionData.mCloseButtonTextOffset = VECTOR2(280.0f, 0.0f);
		ad.optionData.mResetButtonDim = VECTOR2(200.0f, 30.0f);
		ad.optionData.mResetButtonTextOffset = VECTOR2(-30.0f, 0.0f);
		ad.optionData.mTitleColor = COLOR(0, 0, 0);
		ad.optionData.mOnColor = COLOR(0, 0, 0);
		ad.optionData.mOffColor = COLOR(128, 128, 128);
	}
	//recconfirm
	{
		ad.reconfirmData.mTitle = "確認";
		ad.reconfirmData.mYesText = "はい";
		ad.reconfirmData.mNoText = "いいえ";
		ad.reconfirmData.mReconfirmTextSize = 30.0f;
		ad.reconfirmData.mReconfirmTextOffsetY = 100.0f;
		ad.reconfirmData.mBackPos = VECTOR2(ad.mWidth / 2, 350.0f);
		ad.reconfirmData.mTitlePos = VECTOR2(ad.mWidth / 2, ad.reconfirmData.mBackPos.y - 150.0f);
		ad.reconfirmData.mButtonPos = VECTOR2(ad.mWidth / 2, ad.reconfirmData.mTitlePos.y + 190.0f);
		ad.reconfirmData.mReconfirmTextColor = COLOR(0, 0, 0);
		ad.reconfirmData.mTitleColor = COLOR(0, 0, 0);
	}
	//stageSelect
	{
		ad.stageSelectData.mTitle = "ステージセレクト";
		ad.stageSelectData.mStageGuide = "※ステージはすべて同じものです";
		ad.stageSelectData.mStage1ReconfirmGuide = "『ステージ１』から始めますか？";
		ad.stageSelectData.mStage2ReconfirmGuide = "『ステージ２』から始めますか？";
		ad.stageSelectData.mStage3ReconfirmGuide = "『ステージ３』から始めますか？";
		ad.stageSelectData.mStage1Text = "ステージ１";
		ad.stageSelectData.mStage2Text = "ステージ２";
		ad.stageSelectData.mStage3Text = "ステージ３";
		ad.stageSelectData.mReturnText = "戻る";
		ad.stageSelectData.mTextSize = 40.0f;
		ad.stageSelectData.mBackPos = VECTOR2(ad.mWidth / 2, 400.0f);
		ad.stageSelectData.mTitlePos = VECTOR2(ad.mWidth / 2, ad.stageSelectData.mBackPos.y - 150.0f);
		ad.stageSelectData.mButtonPos = VECTOR2(ad.mWidth / 2, ad.stageSelectData.mTitlePos.y + 100.0f);
		ad.stageSelectData.mStageGuideOffsetPos = VECTOR2(-60.0f, 0.0f);
		ad.stageSelectData.mTitleColor = COLOR(0, 0, 0);

	}
	//help
	{
		ad.helpData.mCloseText = "×";
		ad.helpData.mCloseButtonGuide = "ヘルプを閉じます";
		ad.helpData.mNextText = "→";
		ad.helpData.mNextButtonGuide = "次のページへ";
		ad.helpData.mReturnText = "←";
		ad.helpData.mReturnButtonGuide = "前のページへ";
		ad.helpData.mCloseButtonPos = VECTOR2(ad.mWidth - 50.0f, 35.0f);
		ad.helpData.mNextButtonPos = VECTOR2(ad.mWidth - 100.0f, ad.mHeight / 2.0f);
		ad.helpData.mReturnButtonPos = VECTOR2(100.0f, ad.mHeight / 2.0f);

	}
	//pause
	{
		ad.pauseData.mTitle = "Pause";
		ad.pauseData.mReStartText = "再開";
		ad.pauseData.mReStertButtonGuide = "プレイを再開します";
		ad.pauseData.mOptionText = "オプション";
		ad.pauseData.mOptionButtonGuide = "オプションを開きます";
		ad.pauseData.mReturnTitleText = "タイトルに戻る";
		ad.pauseData.mReturnTitleButtonGuide = "タイトルに戻ります";
		ad.pauseData.mQuitText = "ゲームを終わる";
		ad.pauseData.mQuitButtonGuide = "ゲームを終了します";
		ad.pauseData.mHelpText = "？";
		ad.pauseData.mHelpButtonGuide = "ヘルプを開きます";
		ad.pauseData.mTextSize = 30.0f;
		ad.pauseData.mPauseSoundVolumeOffset = -850;
		ad.pauseData.mTitlePos = VECTOR2(ad.mWidth / 2, ad.mHeight / 2);
		ad.pauseData.mButtonPos = VECTOR2(ad.pauseData.mTitlePos.x, ad.pauseData.mTitlePos.y + 200.0f);
		ad.pauseData.mHelpButtonPosOffset = VECTOR2(ad.mWidth / 2.0f - 50.0f, -ad.mHeight + 100.0f);
	}
	//stageClear
	{
		ad.stageClearData.mTextSize = 300.0f;
		ad.stageClearData.mTitlePos.set(ad.mWidth / 2, ad.mHeight / 2 - 100.0f);
		ad.stageClearData.mButtonPos.set(ad.mWidth / 2, ad.stageClearData.mTitlePos.y + 200.0f);
		ad.stageClearData.mClearTimeTextSize = 50.0f;
		ad.stageClearData.mTitle = "StageClear!!";
		ad.stageClearData.mNextText = "次へ";
		ad.stageClearData.mNextButtonGuide = "エンディングに進みます";
		ad.stageClearData.mReturnTitleText = "タイトルに戻る";
		ad.stageClearData.mReturnTitleButtonGuide = "タイトルに戻ります";
		ad.stageClearData.mQuitText = "ゲームを終わる";
		ad.stageClearData.mQuitButtonGuide = "ゲームを終わります";
		ad.stageClearData.mTitleColor = COLOR(128, 50, 50);
	}
	//gamePlay
	{
		ad.playData.mBgm1SoundVolumeOffset = -950;
		ad.playData.mBgm2SoundVolumeOffset = -1300;
		ad.playData.mPauseButtonText = "停";
		ad.playData.mPauseHelpText = "Pause Click or EnterKey";
	}
	//gameOver
	{
		ad.overData.mTitle = "GameOver";
		ad.overData.mReturnTitleText = "タイトルに戻る";
		ad.overData.mRetryText = "リトライ";
		ad.overData.mQuitText = "ゲームを終わる";
		ad.overData.mReturnTitleButtonGuide = "タイトルに戻ります";
		ad.overData.mRetryButtonGuide = "もう一度ステージをやり直します";
		ad.overData.mQuitButtonGuide = "ゲームを終わります";
		ad.overData.mTitleTextSize = 300.0f;
		ad.overData.mTitlePosAdvSpeed = 0.04f;
		ad.overData.mMaxOffsetPosY = -150.0f;
		ad.overData.mTitlePos = VECTOR2(ad.mWidth / 2.0f, ad.mHeight / 2.0f - 100.0f);
		ad.overData.mButtonPos = VECTOR2(ad.mWidth / 2.0f, ad.overData.mTitlePos.y + 200.0f);
		ad.overData.mRetryButtonPosOffset = VECTOR2(-70.0f, 0.0f);
		ad.overData.mTitleColor = COLOR(128, 50, 50);
	}
	//allData
	{
		ad.allClearData.mButtonPos.set(ad.mWidth / 2, ad.mHeight / 2 - 100.0f + 300.0f);
		ad.allClearData.mQuitText = "終わる";
		ad.allClearData.mReturnTitleText = "タイトルに戻る";
	}
	//UIpSideCharaStatus
	{
		ad.psData.mWidth = 260.0f;
		ad.psData.mHeight = 150.0f;
		ad.psData.mRadius = 50.0f;
		ad.psData.mDiamiter = 10.0f;
		ad.psData.mAngleOffset = 90.0f;
		ad.psData.mAngle = 0.0f;
		ad.psData.mChangeTimeSpeed = 0.04f;
		ad.psData.mChangeAngleSpeed = 0.5f;
		ad.psData.mBarrierHpGaugeOffsetPosY = 130.0f;
		ad.psData.mBarrierHpGaugeHeight = 5.0f;
		ad.psData.mBarrierHpGaugeMaxWidth = 50.0f;
		ad.psData.mLineSw = 1.0f;
		ad.psData.mNameandLvTextSize = 15.0f;
		ad.psData.mStateCursorDim = 69.0f;
		ad.psData.mStateCursorSw = 5.0f;
		ad.psData.mLaunchRingRadius = 20.0f;
		ad.psData.mLaunchRingSw = 5.0f;
		ad.psData.mStockItemWeight = 10.0f;
		ad.psData.mItemCylinderRadius = 75.0f / 2.0f;
		ad.psData.mItemIconRadius = 45.0f;
		ad.psData.mMaxItemNum = 6;
		ad.psData.mItemLvTextSize = 30.0f;
		ad.psData.mWindowEdgeSw = 15.0f;
		ad.psData.mItemGaugeWindowDim = 100.0f;
		ad.psData.mHpGaugeMaxWidth = 100.0f;
		ad.psData.mHpGaugeHeight = 10.0f;
		ad.psData.mPopUpTextSize = 30.0f;
		ad.psData.mUIOffsetPosY = 100.0f;

		ad.psData.mCloseButtonText = "△";
		ad.psData.mOpenButtonText = "▽";
		ad.psData.mLvUpButtonText = "+LV";
		ad.psData.mReturnHomeButtonText = "R";
		ad.psData.mHomePatrollButtonText = "H";
		ad.psData.mFieldPatrollButtonText = "F";
		ad.psData.mStayButtonText = "S";
		ad.psData.mLvUpButtonGuide = "キャラクターのレベルを上げます。";
		ad.psData.mReturnHomeButtonGuide = "Homeの近くまで戻って停止します。";
		ad.psData.mHomePatrollButtonGuide = "Homeの周りを巡回します。";
		ad.psData.mFieldPatrollButtonGuide = "敵味方のHomeの間を巡回します。";
		ad.psData.mStayButtonGuide = "巡回をやめ、その場にとどまります。";

		ad.psData.mUIInitPos = VECTOR2(2600.0f, 100.0f);
		ad.psData.mCloseLvUpButtonOffset = VECTOR2(225.0f, 25.0f);
		ad.psData.mOpenLvUpButtonOffset = VECTOR2(50.0f + 200.0f - 25.0f, 195.0f + 50.0f - 25.0f / 2.0f);
		ad.psData.mCloseButtonOffset = VECTOR2(50.0f + 200.0f - 25.0f - 50.0f, 195.0f + 50.0f - 25.0f / 2.0f);
		ad.psData.mOpenButtonOffset = VECTOR2(175.0f, 25.0f);
		ad.psData.mSpeedGaugeOffset = VECTOR2(175.0f, 45.0f);
		ad.psData.mPowerGaugeOffset = VECTOR2(225.0f, 45.0f);
		ad.psData.mRapidGaugeOffset = VECTOR2(175.0f, 95.0f);
		ad.psData.mBarrierGaugeOffset = VECTOR2(225.0f, 95.0f);
		ad.psData.mStayButtonOffset = VECTOR2(50.0f, 195.0f - 25.0f / 2.0f);
		ad.psData.mReturnButtonOffset = VECTOR2(50.0f + 50.0f, 195.0f - 25.0f / 2.0f);
		ad.psData.mHomePatrollButtonOffset = VECTOR2(50.0f + 100.0f, 195.0f - 25.0f / 2.0f);
		ad.psData.mFieldPatrollButtonOffset = VECTOR2(50.0f + 150.0f, 195.0f - 25.0f / 2.0f);
		ad.psData.mHpGaugeOffset = VECTOR2(0.0f, 105.0f);
		ad.psData.mLaunchRingOffset = VECTOR2(75.0f, 75.0f);
		ad.psData.mItemGaugeWindowOffset = VECTOR2(150.0f, 20.0f);
		ad.psData.mHpGaugeInitOffset = VECTOR2(25.0f, 20.0f);

		ad.psData.mUIWindowColor = COLOR(128, 255, 255, 128);
		ad.psData.mTimeGaugeColor = COLOR(255, 0, 0, 128);
		ad.psData.mBarrierHpGaugeColor = COLOR(50, 50, 255);
		ad.psData.mRingOnLineColor = COLOR(0, 0, 0);
		ad.psData.mItemNameTextColor = COLOR(0, 0, 0);
		ad.psData.mStateCursorColor = COLOR(255, 0, 0);
		ad.psData.mWhiteRingColor = COLOR(255, 255, 255);
		ad.psData.mGaugeRingColor = COLOR(255, 0, 0, 128);
		ad.psData.mItemColors[0] = COLOR(0, 0, 0);
		ad.psData.mItemColors[1] = COLOR(0, 255, 0);
		ad.psData.mItemColors[2] = COLOR(255, 255, 0);
		ad.psData.mItemColors[3] = COLOR(0, 0, 255);
		ad.psData.mItemColors[4] = COLOR(255, 0, 0);
		ad.psData.mItemColors[5] = COLOR(255, 0, 255);
		ad.psData.mNoItemColor = COLOR(128, 128, 128);
		ad.psData.mOpenWindowEdgeColor = COLOR(255, 255, 255);
		ad.psData.mWindowColor = COLOR(50, 150, 255);
		ad.psData.mHpNormalColor = COLOR(50, 255, 50);
		ad.psData.mHpDyingColor = COLOR(255, 50, 50);
		ad.psData.mHpDangarColor = COLOR(255, 255, 50);
		ad.psData.mPopUpPositiveColor = COLOR(255, 255, 128);
		ad.psData.mPopUpNegativeColor = COLOR(50, 50, 255);
	}
	//UIPlayerHome
	{
		ad.uiPHomeData.mHpGaugeMaxWidth = 1000.0f;
		ad.uiPHomeData.mHpGaugeHeight = 50.0f;
		ad.uiPHomeData.mBarrierHpGaugeMaxWidth = 500.0f;
		ad.uiPHomeData.mBarrierHpGaugeHeight = 25.0f;
		ad.uiPHomeData.mMoveOnInterval = 10.0f;
		ad.uiPHomeData.mReturnInterval = 5.0f;
		ad.uiPHomeData.mPopUpTextSize = 30.0f;
		ad.uiPHomeData.mHomeLvUpUsePoint = 300;
		ad.uiPHomeData.mCanItemGenerateHomeLv = 5;
		ad.uiPHomeData.mHpGaugeEdgeSw = 5.0f;
		ad.uiPHomeData.mIntervalGaugeRingAngleOffset = 90.0f;
		ad.uiPHomeData.mIntervalGaugeRingSw = 5.0f;
		ad.uiPHomeData.mIntervalGaugeRingRadius = 20.0f;
		ad.uiPHomeData.mSpecialButtonRadius = 75.0f;
		ad.uiPHomeData.mPopUpNotMoveOnText = "これ以上進めない！！";
		ad.uiPHomeData.mPopUpNotReturnText = "これ以上下がれない！！";
		ad.uiPHomeData.mPopUpPHomeMoveNotGenerateText = "移動中はユニットの追加ができません";
		ad.uiPHomeData.mPopUpPHomeGenerateNotMoveText = "ユニットの追加中に移動することはできません";
		ad.uiPHomeData.mMoveOnButtonText = "∧∧";
		ad.uiPHomeData.mMoveOnButtonGuide = "PlayerHomeを前進させます。";
		ad.uiPHomeData.mReturnButtonText = "∨∨";
		ad.uiPHomeData.mReturnButtonGuide = "PlayerHomeを後退させます。";
		ad.uiPHomeData.mGenerateUnitButtonText = "キャラクター+";
		ad.uiPHomeData.mGenerateItemButtonText = "アイテム+";
		ad.uiPHomeData.mPopUpFullUnitText = "ユニットがいっぱいです";
		ad.uiPHomeData.mHomeLvUpButtonText = "HomeLv+";
		ad.uiPHomeData.mHomeLvUpButtonGuide = "300ポイントでHomeをLvUp。";
		ad.uiPHomeData.mPopUpHomeLvUpText = "PlayerHomeのLvが上がった！！";
		ad.uiPHomeData.mPopUpCanGenerateItemText = "アイテムが追加できるようになった！！";
		ad.uiPHomeData.mPopUpNotEnoughPointText = "ポイントが足りない";
		ad.uiPHomeData.mPopUpNotGenerateInGenerateText = "ユニットの追加中に新たにユニットを追加することはできません";
		ad.uiPHomeData.mPopUpNotHomeLvUpText = "HomeのLvはこれ以上上がらない！！";
		ad.uiPHomeData.mCanGenerateItemLogText = "アイテムの追加ができるようになりました。";
		ad.uiPHomeData.mSpecialButtonText = "Special";
		ad.uiPHomeData.mSpecialButtonGuide = "必殺技を使用できます";
		ad.uiPHomeData.mPopUpCanUseSpecialText = "一度だけ、必殺技が使用できます";
		ad.uiPHomeData.mLogUseSpecialText = "必殺技を発動！！";
		ad.uiPHomeData.mPopUpEmemyEmptyText = "敵がいないと発動できない";
		ad.uiPHomeData.mPopUpReleaseSpecialText = "必殺技が使用できるようになった！！";
		ad.uiPHomeData.mPopUpGenerateSpecialText = "キャラクターの追加中は必殺技を撃てません";
		ad.uiPHomeData.mPopUpMoveSpecialText = "移動中は必殺技を撃てません";
		ad.uiPHomeData.mSpecialButtonOffset = VECTOR2(175.0f, 0.0f);
		ad.uiPHomeData.mHomeMoveButtonDim = VECTOR2(44.0f, 64.0f);
		ad.uiPHomeData.mMoveOnButtonOffset = VECTOR2(700.0f, -169.0f - 75.0f);
		ad.uiPHomeData.mReturnButtonOffset = VECTOR2(0.0f, 150.0f);
		ad.uiPHomeData.mHomeLvUpButtonOffset = VECTOR2(875.0f, -238.0f);
		ad.uiPHomeData.mGenerateUnitButtonOffset = VECTOR2(875.0f, -169.0f);
		ad.uiPHomeData.mGenerateItemButtonOffset = VECTOR2(875.0f, -100.0f);
		ad.uiPHomeData.mPointTextPos = VECTOR2(0.0f, 50.0f);
		ad.uiPHomeData.mUnitSizeTextPos = VECTOR2(1600.0f, 50.0f);
		ad.uiPHomeData.mHpGaugeEdgeColor = COLOR(255, 255, 255);
		ad.uiPHomeData.mSpecialGuideOffset = VECTOR2(0.0f, 125.0f);
		ad.uiPHomeData.mPopUpNegativeColor = COLOR(50, 50, 255);
		ad.uiPHomeData.mPopUpPositiveColor = COLOR(255, 255, 128);
		ad.uiPHomeData.mNormalColor = COLOR(0, 255, 0);
		ad.uiPHomeData.mDyingColor = COLOR(255, 0, 0);
		ad.uiPHomeData.mDangarColor = COLOR(255, 255, 0);
		ad.uiPHomeData.mHpWindowColor = COLOR(200, 200, 200);
		ad.uiPHomeData.mOverMaxHpColor = COLOR(50, 255, 255);
		ad.uiPHomeData.mBarrierHpGaugeColor = COLOR(50, 50, 255, 128);
		ad.uiPHomeData.mIntervalGaugeRingRadiusColor = COLOR(128, 128, 128, 128);
	}
	//uiGenerate
	{
		ad.uiGenerateData.mLvEveryUpCannonPoint = 100;
		ad.uiGenerateData.mLvEveryUpBarricadePoint = 50;
		ad.uiGenerateData.mCannonGenerateBasePoint = 300;
		ad.uiGenerateData.mBarricadeGenerateBasePoint = 100;
		ad.uiGenerateData.mItemGeneratePoint = 150;
		ad.uiGenerateData.mGenerateMouseCenterDistX = 340.0f;
		ad.uiGenerateData.mItemButtonOffsetY = 69.0f;
		ad.uiGenerateData.mCancellText = "キャンセル";
		ad.uiGenerateData.mChangeItemText = "アイテムに切り替え";
		ad.uiGenerateData.mChangeCharacterText = "キャラクターに切り替え";
		ad.uiGenerateData.mChangeUnitTexts[0] = "Barricadeに切り替え";
		ad.uiGenerateData.mChangeUnitTexts[1] = "Cannonに切り替え";
		ad.uiGenerateData.mReconfirmTexts[0] = "Cannonをどこに出撃させますか？ ";
		ad.uiGenerateData.mReconfirmTexts[1] = "Barricadeをどこに設置しますか？ ";
		ad.uiGenerateData.mReconfirmTexts[2] = "BarrierItemをどこに設置しますか？ ";
		ad.uiGenerateData.mReconfirmTexts[3] = "PowerItemをどこに設置しますか？ ";
		ad.uiGenerateData.mReconfirmTexts[4] = "SpeedItemをどこに設置しますか？ ";
		ad.uiGenerateData.mReconfirmTexts[5] = "RapidItemをどこに設置しますか？ ";
		ad.uiGenerateData.mReconfirmTexts[6] = "RecoverItemをどこに設置しますか？ ";
		ad.uiGenerateData.mPopUpSuccessText = "Generated！！";
		ad.uiGenerateData.mPopUpAreaOutText = "マップの外に出すことができない";
		ad.uiGenerateData.mPopUpInEnemyAreaText = "敵のエリアには出すことができない";
		ad.uiGenerateData.mItemNames[0] = "Barrier";
		ad.uiGenerateData.mItemNames[1] = "Power";
		ad.uiGenerateData.mItemNames[2] = "Speed";
		ad.uiGenerateData.mItemNames[3] = "Rapid";
		ad.uiGenerateData.mItemNames[4] = "Recover";
		ad.uiGenerateData.mItemTexts[0] = "ダメージを数回無効化します。";
		ad.uiGenerateData.mItemTexts[1] = "弾丸の威力を上げます。";
		ad.uiGenerateData.mItemTexts[2] = "移動速度を上げます。";
		ad.uiGenerateData.mItemTexts[3] = "発射間隔を短くします。";
		ad.uiGenerateData.mItemTexts[4] = "体力を少し回復します。";
		ad.uiGenerateData.mResetLvText = "Reset";
		ad.uiGenerateData.mPlusLvText = "Lv+";
		ad.uiGenerateData.mMinusLvText = "Lv-";
		ad.uiGenerateData.mMaxLvText = "Max";
		ad.uiGenerateData.mPopUpLimitLvText = "PlayerHomeのレベルを超えることはできません";
		ad.uiGenerateData.mPopUpZeroLvText = "レベルをこれ以上下げることはできません";
		ad.uiGenerateData.mChangeItemButtonOffset = VECTOR2(0.0f, 169.0f);
		ad.uiGenerateData.mCancellButtonOffset = VECTOR2(400.0f, 0.0f);
		ad.uiGenerateData.mUnitChangeButtonOffset = VECTOR2(0.0f, 69.0f * 2.0f);
		ad.uiGenerateData.mBPTextPos = VECTOR2(ad.mWidth / 2.0f, ad.mHeight / 2.0f + 150.0f);
		ad.uiGenerateData.mGenerateReconfirmTextPos = VECTOR2(ad.mWidth / 2.0f, ad.mHeight / 2.0f + 200.0f);
		ad.uiGenerateData.mDropUnitPositionOffset = VECTOR(0.0f, 10.0f, 0.0f);
		ad.uiGenerateData.mItemButtonInitOffset = VECTOR2(0.0f, 69.0f);
		ad.uiGenerateData.mChangeItemButtonOffset = VECTOR2(0.0f, 69.0f);
		ad.uiGenerateData.mLvPlusButtonOffset = VECTOR2(-69.0f, 69.0f * 2.0f);
		ad.uiGenerateData.mLvMinusButtonOffset = VECTOR2(-69.0f + 69.0f * 2.0f, 69.0f * 2.0f);
		ad.uiGenerateData.mLvTUButtonPosOffset = VECTOR2(80.0f, 0.0f);
		ad.uiGenerateData.mGenerateButtonDim = VECTOR2(15.0f * 22.0f, 49.0f);
		ad.uiGenerateData.mGenerateItemButtonDim = VECTOR2(15.0f * 7.0f, 49.0f);

	}
	//uiMiniMap
	{
		ad.miniMapData.mMiniMapWindowWidth = 0.0f;
		ad.miniMapData.mMiniMapWindowHeight = 0.0f;
		ad.miniMapData.mNumModels = 0;
		ad.miniMapData.mOffsetX = 350.0f;
		ad.miniMapData.mOffsetY = 525.0f;
		ad.miniMapData.mMiniMapEdgeWidth = 10.0f;
		ad.miniMapData.mSw = 10.0f;
		ad.miniMapData.mMinPosX = 0.0f;
		ad.miniMapData.mMinPosY = 0.0f;
		ad.miniMapData.mMiniMapOffsetX = 0.0f;
		ad.miniMapData.mMiniMapOffsetY = 0.0f;
		ad.miniMapData.mMiniMapWindowLength = 538.0f;
		ad.miniMapData.mItemSw = 1.0f;
		ad.miniMapData.mWeaponSw = 5.0f;
		ad.miniMapData.mItemCircleRadius = 10.0f;
		ad.miniMapData.m3DCoordinate2DConvertRate = 7.0f;
		ad.miniMapData.mStage1OffsetX = 288.0f;
		ad.miniMapData.mStage1OffsetY = 450.0f;
		ad.miniMapData.mStage2OffsetX = 293.5f;
		ad.miniMapData.mStage2OffsetY = 440.0f;
		ad.miniMapData.mStage3OffsetX = 293.5f;
		ad.miniMapData.mMiniHpGaugeMaxWidth = 30.0f;
		ad.miniMapData.mMiniHpGaugeHeight = 5.0f;
		ad.miniMapData.mHomeAreaCircleSw = 5.0f;
		ad.miniMapData.mHomeAreaDiamiter = 100.0f;
		ad.miniMapData.mHomeNameTextSize = 50.0f;
		ad.miniMapData.mCharacterNameTextSize = 30.0f;
		ad.miniMapData.mHomeAreaAlpha = 128.0f;
		ad.miniMapData.mCharacterNameContainsAreaRadius = 5.0f;
		ad.miniMapData.mMiniMapCornerPos = VECTOR2(108.0f, 68.0f);
		ad.miniMapData.mItemStrokeColor = COLOR(255, 255, 255);
		ad.miniMapData.mArrowStrokeColor = COLOR(255, 255, 255);
		ad.miniMapData.mWindowColor = COLOR(128, 128, 128, 128);
		ad.miniMapData.mFloorColor = COLOR(40, 150, 128, 128);
		ad.miniMapData.mPlayerHomeAreaColor = COLOR(40, 40, 200);
		ad.miniMapData.mEnemyHomeAreaColor = COLOR(200, 40, 40);
		ad.miniMapData.mPlayerHomeNameColor = COLOR(50, 50, 255);
		ad.miniMapData.mEnemyHomeNameColor = COLOR(255, 50, 50);
		ad.miniMapData.mHpGaugeNormalColor = COLOR(50, 255, 50, 128);
		ad.miniMapData.mHpGaugeDangerColor = COLOR(255, 255, 50, 128);
		ad.miniMapData.mHpGaugeDyingColor = COLOR(255, 50, 50, 128);
		ad.miniMapData.mCharacterNameTextColor = COLOR(0, 0, 0);
	}
	//camera
	{
		ad.cameraData.mDistanceFromLookatPos = 1.0f;
		ad.cameraData.mChangePosSpeed = 0.5f;
		ad.cameraData.mOffsetPos = VECTOR(0.0f, 1.25f, 10.0f);
		ad.cameraData.mUpVec = VECTOR(0.0f, 1.0f, 0.0f);
	}
	//normalCamera
	{
		ad.normalCameraData.mLookatPosOffset = VECTOR(0.0f, -5.0f, 0.0f);
		ad.normalCameraData.mPos = VECTOR(15.0f, 15.0f, 25.0f);
		ad.normalCameraData.mRotX = 1.75f;
	}
	//pHomeCamera
	{
		ad.lookPHomeCameraData.mLookatPosOffset = VECTOR(0.0f, 5.0f, -10.0f);
	}
	//centerCamera
	{
		ad.lookCenterCameraData.mPos = VECTOR(0.0f, 94.0f, -27.0f);
		ad.lookCenterCameraData.mRotX = 1.57f;
	}
	//pHome
	{

		ad.pHomeData.mFlag1Offset = VECTOR(-2.0f, 2.0f, -3.0f + 0.25f);
		ad.pHomeData.mFlag2Offset = VECTOR(2.0f, 2.0f, -3.0f + 0.25f);
		ad.pHomeData.mDoreOffset = VECTOR(0.0f, 1.8f, -1.9f);
		ad.pHomeData.mHpGaugeOffset = VECTOR(0.0f, 3.0f, 0.0f);
		ad.pHomeData.mHomeTargetPointOffsets[0] = VECTOR(-7.0f, 0.0f, -7.0f);
		ad.pHomeData.mHomeTargetPointOffsets[1] = VECTOR(7.0f, 0.0f, -7.0f);
		ad.pHomeData.mHomeTargetPointOffsets[2] = VECTOR(7.0f, 0.0f, 5.0f);
		ad.pHomeData.mHomeTargetPointOffsets[3] = VECTOR(-7.0f, 0.0f, 5.0f);
		ad.pHomeData.mFieldTargetPointOffsets[0] = VECTOR(-7.0f, 0.0f, -7.0f);
		ad.pHomeData.mFieldTargetPointOffsets[1] = VECTOR(7.0f, 0.0f, -7.0f);
		ad.pHomeData.mFieldTargetPointOffsets[2] = VECTOR(7.0f, 0.0f, 7.0f);
		ad.pHomeData.mFieldTargetPointOffsets[3] = VECTOR(-7.0f, 0.0f, 7.0f);
		ad.pHomeData.mRadius = 3.0f;
		ad.pHomeData.mHeight = 0.0f;
		ad.pHomeData.mMaxHp = 20;
		ad.pHomeData.mInitMaxBattlePoint = 500;
		ad.pHomeData.mCannonBasePoint = 150;
		ad.pHomeData.mBarricadeBasePoint = 100;
		ad.pHomeData.mLvUpBasePoint = 100;
		ad.pHomeData.mLvEveryUpPoint = 50;
		ad.pHomeData.mMaxDamageInterval = 0.09f;
		ad.pHomeData.mImageColor = COLOR(0, 0, 255);
	}
	//eHome
	{
		ad.eHomeData.mFlag1Offset = VECTOR(-2.0f, 2.0f, 3.0f + 0.25f);
		ad.eHomeData.mFlag2Offset = VECTOR(2.0f, 2.0f, 3.0f + 0.25f);
		ad.eHomeData.mDoreOffset = VECTOR(0.0f, 1.8f, 1.9f);
		ad.eHomeData.mHpGaugeOffset = VECTOR(0.0f, 3.0f, 0.0f);
		ad.eHomeData.mMaxHp = 20;
		ad.eHomeData.mRadius = 3.0f;
		ad.eHomeData.mHeight = 0.0f;
		ad.eHomeData.mSpecialReleaseSoundVolumeOffset = -850;
		ad.eHomeData.mMaxDamageInterval = 0.09f;
		ad.eHomeData.mGenerateInterval = 200.0f;
		ad.eHomeData.mInitMaxPoint = 500;
		ad.eHomeData.mHomeLvUpUsePoint = 300;
		ad.eHomeData.mUnitLvUpBasePoint = 100;
		ad.eHomeData.mUnitLvUpEveryLvPoint = 50;
		ad.eHomeData.mSatelliteGenerateBasePoint = 200;
		ad.eHomeData.mTamaGenerateBasePoint = 150;
		ad.eHomeData.mGenerateLvLvUpPoint = 300;
		ad.eHomeData.mImageColor = COLOR(255, 0, 0);
	}
	//cannon
	{
		ad.cannonData.mAdvSpeed = 0.05f * 10.0f;
		ad.cannonData.mAmbient = 0.3f;
		ad.cannonData.mGravity = -24.0f;
		ad.cannonData.mJumpVelocity = 0.0f;
		ad.cannonData.mInterval = 0.5f;
		ad.cannonData.mJumpFlag = 1;
		ad.cannonData.mRange = 20.0f;
		ad.cannonData.mMaxHp = 7;
		ad.cannonData.mMaxDamageInterval = 0.16f;
		ad.cannonData.mCannonCapsulHeight = 0.50f;
		ad.cannonData.mCannonCapsulRadius = 0.75f;
		ad.cannonData.mWheelAngleOffset = 1.57f;
		ad.cannonData.mLaunchTimeDecreaseAdvSpeed = 300.0f;
		ad.cannonData.mLaunchBodyScale = 1.5f;
		ad.cannonData.mNormalBodyScale = 1.0f;
		ad.cannonData.mJumpSoundVolumeOffset = -800;
		ad.cannonData.mFallSoundVolumeOffset = -100;
		ad.cannonData.mItemStockMaxSize = 6;
		ad.cannonData.mChangeScaleSpeed = 0.4f;
		ad.cannonData.mLaunchTime = 50.0f;
		ad.cannonData.mSlideSoundVolumeOffset = -400;
		ad.cannonData.mWheelOffsetPos = VECTOR(-0.5f, 0.0f, 0.0f);
		ad.cannonData.mBarrelDir = VECTOR(0.0f, 0.0f, -1.0f);
		ad.cannonData.mInitPos = VECTOR(0.0f, 10.0f, 1.0f);
		ad.cannonData.mCapsulOffset = VECTOR(0, 0.5f, 0);
		ad.cannonData.mBodyOffsetPos = VECTOR(0.0f, 0.3f, 0.0f);
		ad.cannonData.mImageColor = COLOR(0, 0, 255);
	}
	//barricade
	{
		ad.barricadeData.mHp = 20;
		ad.barricadeData.mGravity = -9.8f;
		ad.barricadeData.mRadius = 0.75f;
		ad.barricadeData.mAdvSpeed = 0.5f;
		ad.barricadeData.mJumpFlag = 1;
		ad.barricadeData.mMaxDamageInterval = 0.09f;
		ad.barricadeData.mCollisionSoundVolumeOffset = -900;
		ad.barricadeData.mImageColor = COLOR(0, 0, 255);
		ad.barricadeData.mCapsuleOffset = VECTOR(0.0f, 0.5f, 0.0f);
	}
	//itemすべてに共通するデータ
	{
		ad.itemCommonData.mJumpVelocity = 0.0f;
		ad.itemCommonData.mGravity = -5.0f;
		ad.itemCommonData.mJumpFlag = 1;
		ad.itemCommonData.mAdvSpeed = 0.5f;
		ad.itemCommonData.mLifeTime = 0.0f;
		ad.itemCommonData.mMaxLifeTime = 30.0f;
		ad.itemCommonData.mRadius = 0.1f;
		ad.itemCommonData.mDropSoundVolumeOffset = -1150;
		ad.itemCommonData.mHp = 1;
		ad.itemCommonData.mCapsulOffset = VECTOR(0.0f, 1.0f, 0.0f);
	}
	//recover
	{
		ad.recoverData.mNum = 1;
		ad.recoverData.mSound1VolumeOffset = -1150;
		ad.recoverData.mSound2VolumeOffset = -1250;
		ad.recoverData.mColor = COLOR(0, 255, 0);
		ad.recoverData.mName = "Recovery";
	}
	//power
	{
		ad.powerData.mNum = 2;
		ad.powerData.mSound1VolumeOffset = -750;
		ad.powerData.mSound2VolumeOffset = 0;
		ad.powerData.mColor = COLOR(255, 255, 0);
		ad.powerData.mName = "PowerUp";

	}
	//speed
	{
		ad.speedData.mNum = 3;
		ad.speedData.mSound1VolumeOffset = -1550;
		ad.speedData.mSound2VolumeOffset = 0;
		ad.speedData.mColor = COLOR(0, 0, 255);
		ad.speedData.mName = "SpeedUp";

	}
	//rapid
	{
		ad.rapidData.mNum = 4;
		ad.rapidData.mSound1VolumeOffset = -750;
		ad.rapidData.mSound2VolumeOffset = 0;
		ad.rapidData.mColor = COLOR(255, 0, 0);
		ad.rapidData.mName = "RapidFire";
	}
	//barrier
	{
		ad.barrierData.mNum = 5;
		ad.barrierData.mSound1VolumeOffset = -1250;
		ad.barrierData.mSound2VolumeOffset = 0;
		ad.barrierData.mColor = COLOR(255, 0, 255);
		ad.barrierData.mName = "Barrier";
	}
	//itemEffectに共通するデータ
	{
		ad.itemEffectData.mUIPosY = 0.0f;
		ad.itemEffectData.mUIOffsetPosY = 150.0f;
		ad.itemEffectData.mUIPosAdvSpeed = -100.0f;
		ad.itemEffectData.mUIMinPosX = 1600.0f;
		ad.itemEffectData.mUIPosChangeSpeed = 0.5f;
		ad.itemEffectData.mNumber = 0;
		ad.itemEffectData.mKeepTime = 0.0f;
	}
	//recoverEffect
	{
		ad.recoverEffectData.mName = "回復";
		ad.recoverEffectData.mLevel = 1;
		ad.recoverEffectData.mMaxLevel = 1;
		ad.recoverEffectData.mTime = 0.0f;
		ad.recoverEffectData.mInterval = 0.0f;
		ad.recoverEffectData.mMaxHp = 0;
		ad.recoverEffectData.mColor = COLOR(0, 255, 0);
	}
	//powerEffect
	{
		ad.powerEffectData.mName = "パワー";
		ad.powerEffectData.mLevel = 1;
		ad.powerEffectData.mMaxLevel = 4;
		ad.powerEffectData.mTime = 0.0f;
		ad.powerEffectData.mInterval = 100.0f;
		ad.powerEffectData.mMaxHp = 1;
		ad.powerEffectData.mColor = COLOR(255, 255, 0);
	}
	//speedEffect
	{
		ad.speedEffectData.mName = "スピード";
		ad.speedEffectData.mLevel = 1;
		ad.speedEffectData.mMaxLevel = 5;
		ad.speedEffectData.mTime = 0.0f;
		ad.speedEffectData.mInterval = 100.0f;
		ad.speedEffectData.mMaxHp = 1;
		ad.speedEffectData.mColor = COLOR(0, 0, 255);
	}
	//rapidEffect
	{
		ad.rapidEffectData.mName = "Rファイア";
		ad.rapidEffectData.mLevel = 1;
		ad.rapidEffectData.mMaxLevel = 3;
		ad.rapidEffectData.mTime = 0.0f;
		ad.rapidEffectData.mInterval = 100.0f;
		ad.rapidEffectData.mMaxHp = 1;
		ad.rapidEffectData.mColor = COLOR(255, 0, 0);
	}
	//barrierEffect
	{
		ad.barrierEffectData.mName = "バリア―";
		ad.barrierEffectData.mLevel = 1;
		ad.barrierEffectData.mMaxLevel = 5;
		ad.barrierEffectData.mTime = 0.0f;
		ad.barrierEffectData.mInterval = 100.0f;
		ad.barrierEffectData.mMaxHp = 3;
		ad.barrierEffectData.mColor = COLOR(255, 0, 255);
	}
	//playerBullet
	{
		ad.pBulletData.mRadius = 0.2f;
		ad.pBulletData.mHeight = 0.0f;
		ad.pBulletData.mAdvSpeed = 15.5f;
		ad.pBulletData.mMaxLifeTime = 10.0f;
		ad.pBulletData.mLifeTimeDecreaseSpeed = 5.0f;
		ad.pBulletData.mJumpFlag = 0;
		ad.pBulletData.mGravity = 0.0f;
		ad.pBulletData.mJumpVelocity = 0.0f;
		ad.pBulletData.mSize = ad.pBulletData.mRadius * 2;
		ad.pBulletData.mDamage = 1;
		ad.pBulletData.mOffsetPos = VECTOR(0.0f, 0.0f, 0.0f);
		ad.pBulletData.mImageColor = COLOR(0, 0, 255);
		ad.pBulletIData.mLaunchSoundVolumeOffset = -1400;
		ad.pBulletIData.mImpactSoundVolumeOffset = -850;
		ad.pBulletIData.mItemStockSoundVolumeOffset = -1250;
	}
	//tama
	{
		ad.tamaData.mAnimSpeed = 0.017f;
		ad.tamaData.mJumpVelocity = 1.0f;
		ad.tamaData.mGravity = -19.6f;
		ad.tamaData.mJumpFlag = 1;
		ad.tamaData.mAdvSpeed = 0.5f;
		ad.tamaData.mMaxHp = 7;
		ad.tamaData.mAnimAngle = 0.0f;
		ad.tamaData.mWeaponCnt = 0;
		ad.tamaData.mElapsedTime = 0.0f;
		ad.tamaData.mInterval = 80.0f;
		ad.tamaData.mRadius = 0.4f;
		ad.tamaData.mHeight = 0.0f;
		ad.tamaData.mMaxDamageInterval = 0.016f * 3;
		ad.tamaData.mBlackEyeScale = 0.01f;
		ad.tamaData.mMaxOffsetZ = 0.5f;
		ad.tamaData.mMaxScale = ad.tamaData.mMaxOffsetZ * 2;
		ad.tamaData.mChangeScaleSpeed = 0.4f;
		ad.tamaData.mOffsetPos = VECTOR(0.0f, ad.tamaData.mRadius, 0.0f);
		ad.tamaData.mDushSoundVolumeOffsset = -1000;
		ad.tamaData.mBlackEyeOffsetPos = VECTOR(0.0f, 0.0f, 0.375f);
		ad.tamaData.mCapsulOffset = VECTOR(0.0f, 1.0f, 0.0f);
		ad.tamaData.mHpGaugeOffset = VECTOR(0.0f, 0.25f, 0.0f);
		ad.tamaData.mImageColor = COLOR(255.0f, 0.0f, 0.0f);
		ad.tamaData.mSightSp = VECTOR(0.0f, 0.0f, 0.0f);
		ad.tamaData.mSightEp = VECTOR(0.0f, 0.0f, 7.0f);
	}
	//tamaWeapon
	{
		ad.tWeaponData.mHeight = 0.0f;
		ad.tWeaponData.mRadius = 0.2f;
		ad.tWeaponData.mAdvSpeed = 10.0f;
		ad.tWeaponData.mMaxLifeTime = 10.0f;
		ad.tWeaponData.mLifeTimeDecreaseSpeed = 5.0f;
		ad.tWeaponData.mSize = ad.tamaData.mRadius;
		ad.tWeaponData.mJumpFlag = 0;
		ad.tWeaponData.mGravity = 0.0f;
		ad.tWeaponData.mJumpVelocity = 0.0f;
		ad.tWeaponData.mOffsetPos = VECTOR(0.0f, 0.0f, 0.0f);
		ad.tWeaponData.mImageColor = COLOR(255, 0, 0);
		ad.tWeaponData.mDamage = 1;
		ad.tWeaponIData.mAttackTime = 1.0f;
		ad.tWeaponIData.mAttackSoundOffset = -200;
	}
	//satellite
	{
		ad.satelliteData.mHeight = 0.75f;
		ad.satelliteData.mRadius = 0.6f;
		ad.satelliteData.mLaunchInterval = 0.250f;
		ad.satelliteData.mMoveRange = 2;
		ad.satelliteData.mAdvSpeed = 0.01f;
		ad.satelliteData.mAnimSpeed = 0.017f;
		ad.satelliteData.mMaxHp = 5;
		ad.satelliteData.mMaxHp2 = 8;
		ad.satelliteData.mAngleForPos = 0.05f;
		ad.satelliteData.mMaxDamageInterval = 0.016f * 3.0f;
		ad.satelliteData.mGravity = -4.9f;
		ad.satelliteData.mMaxRange = 10.0f;
		ad.satelliteData.mGenerateSatelliteLvLvUpPoint = 150;
		ad.satelliteData.mSatelliteAGetPoint = 150;
		ad.satelliteData.mSatelliteBGetPoint = 100;
		ad.satelliteData.mSatelliteEveryLvUpPoint = 50;
		ad.satelliteData.mBulletOffsetPos = VECTOR(0.0f, -0.75f, 0.0f);
		ad.satelliteData.mCapsulOffset = VECTOR(0.0f, 0.5f, 0.0f);
		ad.satelliteData.mOffsetPos = VECTOR(0.0f, 0.0f, 0.75f);
		ad.satelliteData.mTargetOffsetPos = VECTOR(0.0f, 0.0f, 3.0f);
		ad.satelliteData.mMeshOffset = VECTOR(0.0f, 0.75f, 0.0f);
		ad.satelliteData.mImageColor = COLOR(255, 0, 0);
	}
	//satelliteBullet
	{
		ad.sBulletData.mAdvSpeed = 10.0f;
		ad.sBulletData.mHeight = 0.0f;
		ad.sBulletData.mRadius = 0.05f;
		ad.sBulletData.mMaxLifeTime = 10.0f;
		ad.sBulletData.mLifeTimeDecreaseSpeed = 5.0f;
		ad.sBulletData.mJumpFlag = 0;
		ad.sBulletData.mGravity = 0.0f;
		ad.sBulletData.mJumpVelocity = 0.0f;
		ad.sBulletData.mSize = ad.sBulletData.mRadius * 2;
		ad.sBulletData.mDamage = 1;
		ad.sBulletData.mOffsetPos = VECTOR(0.0f, 0.0f, 0.0f);
		ad.sBulletData.mImageColor = COLOR(255, 0, 0);
		ad.sBulletIData.mChangeFlame = 50;
		ad.sBulletIData.mLaunchSoundVolumeOffset = -850;
		ad.sBulletIData.mImpactSoundVolumeOffset = -850;
	}
	//satelliteWing
	{
		ad.sWingData.mGravity = -9.8f;
		ad.sWingData.mWingAmbient = 0.8f;
		ad.sWingData.mRadius = 0.5f;
		ad.sWingData.mHeight = 0.0f;
		ad.sWingData.mAdvSpeed = 0.5f;
		ad.sWingData.mMaxOffsetZ = 5.0f;
		ad.sWingData.mId = 0;
		ad.sWingData.mChangePosSpeed = 0.05f;
		ad.sWingData.mChangeOffsetPosSpeed = 0.4f;
		ad.sWingData.mClashText = "が壊れた";
		ad.sWingData.mClashSoundVolumeOffset = -400;
		ad.sWingData.mWingScale1 = VECTOR(0.7f, 1.1f, 1.0f);
		ad.sWingData.mWingScale2 = VECTOR(1.1f, 1.1f, 1.0f);
		ad.sWingData.mS0IdW0IdOffsetPos = VECTOR(0.0f, 0.0f, 0.8f);
		ad.sWingData.mS0IdW1IdOffsetPos = VECTOR(0.85f, 0.0f, 0.0f);
		ad.sWingData.mS0IdW2IdOffsetPos = VECTOR(-0.85f, 0.0f, 0.0f);
		ad.sWingData.mS0IdW3IdOffsetPos = VECTOR(0.0f, 0.0f, -0.8f);
		ad.sWingData.mS1IdOffsetPos = VECTOR(0.0f, 0.750f, -1.0f);
		ad.sWingData.mS0IdAttackOffsetPos = VECTOR(0.0f, 0.0f, -1.0f);
		ad.sWingData.mOffsetPos = VECTOR(0.0f, 0.0f, 0.0f);
		ad.sWingData.mImageColor = COLOR(255, 0, 0);
	}
	//map
	{
		ad.mapData.CollisionText = nullptr;
		ad.mapData.mStageMaxX = 0;
		ad.mapData.mStageMinX = 0;
		ad.mapData.mStageMaxZ = 0;
		ad.mapData.mStageMinZ = 0;
	}
	//stage
	{
		ad.stageData.mEnemyHomeAngleOffset = 3.1415926f;
		ad.stageData.mFirstCannonAngleOffset = 3.1415926f;

		ad.stageData.mPlayerHomeDefaultPos = VECTOR(0.0f, 0.0f, -3.0f);
		ad.stageData.mEnemyHomeDefaultPos = VECTOR(0.0f, 0.0f, -51.0f);
		ad.stageData.mFirstCannonDefaultPos = VECTOR(0.0f, 0.0f, -30.0f);
	}
	//log
	{
		ad.logData.mLogWindowColor = COLOR(128, 128, 128, 128);
		ad.logData.mLogTextColor = COLOR(255, 255, 255);
		ad.logData.mPos = VECTOR2(1920 - (400), 1080 - (200 + 50));
		ad.logData.mWidth = 380.0f;
		ad.logData.mHeight = 200.0f;
		ad.logData.mTextSize = 20.0f;
	}
	//sccroll
	{
		ad.scrollData.mInitPos = VECTOR2(1900.0f, 80.0f);
		ad.scrollData.mMaxPos = VECTOR2(1900.0f, 1000.0f);
		ad.scrollData.mBarLength = VECTOR2(0.0f, 100.0f);
		ad.scrollData.mRadius = 20.0f;
		ad.scrollData.mPointColor = COLOR(255, 255, 255);
		ad.scrollData.mRailColor = COLOR(128, 128, 128);
	}
	//loading
	{
		ad.loadingData.mContainerLoadStartTime = 3.0f;
		ad.loadingData.mChangeStateTime = 13.0f;
		ad.loadingData.mTextSize = 30.0f;
		ad.loadingData.mMaxAlpha = 255.0f;
		ad.loadingData.mAddTextInterval = 0.5f;
		ad.loadingData.mPlusAlpha = 5.0f;
		ad.loadingData.mStateChangeAlpha = 150.0f;
		ad.loadingData.mRev = -1;
		ad.loadingData.mAddTextSize = 4;
		ad.loadingData.mText = "NowLoading";
		ad.loadingData.mAddText[0] = ".";
		ad.loadingData.mAddText[1] = ".";
		ad.loadingData.mAddText[2] = ".";
		ad.loadingData.mAddText[3] = "。";
		ad.loadingData.mTextColor = COLOR(255, 255, 255);
		ad.loadingData.mBackColor = COLOR(0, 0, 0);
	}
	//eCamera
	{
		ad.lookEHomeCameraData.mLookatPosOffset = VECTOR(0.0f, 5.0f, 10.0f);
	}
	//arrow
	{
		ad.arrowData.mAdvSpeed = 5.0f;
		ad.arrowData.mRadius = 0.25f;
		ad.arrowData.mRotateSpeed = 0.05f;
		ad.arrowData.mGravity = -9.8f;
		ad.arrowData.mFlySoundVolumeOffset = -1200;
		ad.arrowData.mHitSoundVolumeOffset = -700;
	}
}
void loadGraphic(struct Container& ad)
{
	loadingSound(ad);
	loadingImage(ad);
}

void loadingSound(struct Container& ad)
{
	//button
	{
		ad.buttonData.mClickSound = loadSound("Assets\\sound\\Button\\Click.wav");
		ad.buttonData.mContainsSound = loadSound("Assets\\sound\\Button\\Contains.wav");
		ad.buttonData.mCancellSound = loadSound("Assets\\sound\\Button\\Cancell.wav");

	}
	//title
	{
		ad.titleData.mBgm = loadSound("Assets\\sound\\Title\\Title.wav");
	}
	//pause
	{
		ad.pauseData.mSound = loadSound("Assets\\sound\\Pause\\Pause.wav");
	}
	//gamePlay
	{
		ad.playData.mBgm1 = loadSound("Assets\\sound\\Play\\BGM\\Play1.wav");
		ad.playData.mBgm2 = loadSound("Assets\\sound\\Play\\BGM\\Play2.wav");
	}
	//stageClear
	{
		ad.stageClearData.mSound = loadSound("Assets\\sound\\StageClear\\StageClear1.wav");
		ad.stageClearData.mSound2 = loadSound("Assets\\sound\\StageClear\\StageClear2.wav");
	}
	//gameOver
	{
		ad.overData.mSound = loadSound("Assets\\sound\\GameOver\\GameOver.wav");
	}
	//allClear
	{
		ad.allClearData.mBgm = loadSound("Assets\\sound\\AllClear\\AllClear.wav");
	}
	//アクター共通の音データ
	{
		ad.mDeadSound = loadSound("Assets\\sound\\Play\\AllActor\\Dead.wav");
		ad.mFallSound = loadSound("Assets\\sound\\Play\\AllActor\\Fall.wav");;
		ad.mDamageSound = loadSound("Assets\\sound\\Play\\Cannon\\Damage.wav");;
		ad.mGurdSound = loadSound("Assets\\sound\\Play\\Cannon\\Gurd.wav");
	}
	//cannon
	{
		ad.cannonData.mJumpSound = loadSound("Assets\\sound\\Play\\Cannon\\Jump.wav");
		ad.cannonData.mCyakuchi = loadSound("Assets\\sound\\Play\\Cannon\\Landing.wav");
		ad.cannonData.mSlide = loadSound("Assets\\sound\\Play\\Cannon\\Slide.wav");
		ad.cannonData.mOutOfBullets = loadSound("Assets\\sound\\Play\\Cannon\\OutOfBullets.wav");
	}
	//barricade
	{
		ad.barricadeData.mCollisionSound = loadSound("Assets\\sound\\Play\\Barricade\\Collision.wav");
	}
	//item共通のデータ
	{
		ad.itemCommonData.mDropSound = loadSound("Assets\\sound\\Play\\Item\\Drop.wav");
	}
	//item固有のデータ
	{
		ad.recoverData.mSound1 = loadSound("Assets\\sound\\Play\\Item\\Recover.wav");
		ad.recoverData.mSound2 = loadSound("Assets\\sound\\Play\\Item\\Stock.wav");
		ad.powerData.mSound1 = loadSound("Assets\\sound\\Play\\Item\\Power.wav");
		ad.powerData.mSound2 = -1;
		ad.speedData.mSound1 = loadSound("Assets\\sound\\Play\\Item\\Speed.wav");
		ad.speedData.mSound2 = -1;
		ad.rapidData.mSound1 = loadSound("Assets\\sound\\Play\\Item\\Rapid.wav");
		ad.powerData.mSound2 = -1;
		ad.barrierData.mSound1 = loadSound("Assets\\sound\\Play\\Item\\Barrier.wav");
		ad.barrierData.mSound2 = -1;
	}

	{
		ad.mCloseSound = loadSound("Assets\\sound\\Play\\Item\\Close.wav");
	}
	//pBullet
	{
		ad.pBulletIData.mLaunchSound = loadSound("Assets\\sound\\Play\\Cannon\\Bullet_Launch.wav");
		ad.pBulletIData.mImpactSound = loadSound("Assets\\sound\\Play\\Cannon\\Bullet_Hit.wav");
		ad.pBulletIData.mItemStockSound = loadSound("Assets\\sound\\Play\\Item\\Stock.wav");
	}
	//tama
	{
		ad.tamaData.mDushSound = loadSound("Assets\\sound\\Play\\Tama\\Dush.wav");
	}
	//tamaWeapon
	{
		ad.tWeaponIData.mAttackSound = loadSound("Assets\\sound\\Play\\Tama\\Weapon.wav");
	}
	//sBullet
	{
		ad.sBulletIData.mLaunchSound = loadSound("Assets\\sound\\Play\\Satellite\\Bullet_Launch.wav");
		ad.sBulletIData.mImpactSound = loadSound("Assets\\sound\\Play\\Satellite\\Bullet_Hit.wav");
	}
	//sWing
	{
		ad.sWingData.mClashSound = loadSound("Assets\\sound\\Play\\Satellite\\Wing_Clash.wav");
	}
	//arrow
	{
		ad.arrowData.mFlySound = loadSound("Assets\\sound\\Play\\Home\\Arrow.wav");
		ad.arrowData.mHitSound = loadSound("Assets\\sound\\Play\\Home\\ArrowHit.wav");
	}
	//eHome
	{
		ad.eHomeData.mSpecialReleaseSound = loadSound("Assets\\sound\\Play\\Home\\SpecialCharge.wav");
	}
}

void loadingImage(struct Container& ad)
{
	//title
	{
		ad.titleData.mBackImg = loadImage("assets\\Image\\Title\\Title.png");
	}
	//uiDialog
	{
		ad.mDialog1 = loadImage("Assets\\Image\\Dialog\\Dialog1.png");
		ad.mDialog2 = loadImage("Assets\\Image\\Dialog\\Dialog2.png");
	}
	//help1
	{
		ad.helpData.mHelp1Img = loadImage("Assets\\Image\\Help\\Help1.png");
	}
	//help2
	{
		ad.helpData.mHelp2Img = loadImage("Assets\\Image\\Help\\Help2.png");
	}
	//help3
	{
		ad.helpData.mHelp3Img = loadImage("Assets\\Image\\Help\\Help3.png");
	}
	//help4
	{
		ad.helpData.mHelp4Img = loadImage("Assets\\Image\\Help\\Help4.png");
	}
	//help5
	{
		ad.helpData.mHelp5Img = loadImage("Assets\\Image\\Help\\Help5.png");
	}
	//allclear
	{
		ad.allClearData.mImg = loadImage("Assets\\Image\\AllClear\\AllClear.png");
	}
}