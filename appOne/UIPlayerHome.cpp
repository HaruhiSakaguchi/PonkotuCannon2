#include "UIPlayerHome.h"
#include "PSideCharacterActor.h"
#include "Game.h"
#include "PlayerHome.h"
#include "UIGenerate.h"
#include <sstream>
#include "UIPopUp.h"
#include "window.h"
#include "PlayerArrow.h"
#include "PlayerFlag.h"
#include "rand.h"

UIPlayerHome::UIPlayerHome(PlayerHome* owner)
	: UIScreen(owner->GetGame())
	, mOwner(owner)
	, mMoveOnButton(nullptr)
	, mReturnButton(nullptr)
	, mGenerate(nullptr)
	, mGenerateItemButton(nullptr)
	, mSpecialButton(nullptr)
	, mHpGaugeWidth(0.0f)
	, mBarrierHpGaugeWidth(0.0f)
	, mUnitMaxNum(1)
	, mInterval(0.0f)
	, mTime(0.0f)
	, mIntervalAngle(0.0f)
	, mSpecialFlag(true)
	, mSpecialEffectFlag(false)
	, mEnemySize(0)
	, mCnt(0)
	, mSpecialReleaseSound(-1)
{
	Data = mGame->GetAllData()->uiPHomeData;

	mSpecialReleaseSound = mGame->GetAllData()->eHomeData.mSpecialReleaseSound;

	float Width = (float)(Data.mHpGaugeHeight * mOwner->GetMaxHp());
	mPos = VECTOR2(width / 2.0f, height - Data.mHpGaugeHeight * 2.0f);

	PlayerHome* h = static_cast<PlayerHome*>(mOwner);

	mMoveOnButton = AddRectButton(Data.mMoveOnButtonText
		, [this]()
		{
			PlayerHome* h = static_cast<PlayerHome*>(mOwner);
			if (h->GetTargetPosIdx() < 2 && h->GetGenerateFlag() == 0)
			{
				h->SetTargetPoint(h->GetHomeMoveTargetPoints()[h->GetTargetPosIdx() + 1]);
				h->SetTargetPosIdx(h->GetTargetPosIdx() + 1);
				mInterval = Data.mMoveOnInterval;
				mStart = std::chrono::system_clock::now();
				mGame->GetCameraManager()->ChangeCamera("PHomeCamera");

			}
			else if (h->GetTargetPosIdx() == 2)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotMoveOnText, mMoveOnButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else if (h->GetGenerateFlag() == 1)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpPHomeGenerateNotMoveText, mMoveOnButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}
		, Data.mMoveOnButtonGuide
			, Data.mHomeMoveButtonDim
			);
	mMoveOnButton->SetTextOffset(VECTOR2(strlen(mMoveOnButton->GetText()) * -Data.mPopUpTextSize / 4.0f, -Data.mPopUpTextSize * 2.0f));

	mReturnButton = AddRectButton(Data.mReturnButtonText
		, [this]()
		{
			PlayerHome* h = static_cast<PlayerHome*>(mOwner);
			if (h->GetTargetPosIdx() > 0 && h->GetGenerateFlag() == 0)
			{
				h->SetTargetPoint(h->GetHomeMoveTargetPoints()[h->GetTargetPosIdx() - 1]);
				h->SetTargetPosIdx(h->GetTargetPosIdx() - 1);
				mInterval = Data.mReturnInterval;
				mStart = std::chrono::system_clock::now();
				mGame->GetCameraManager()->ChangeCamera("PHomeCamera");
			}
			else if (h->GetTargetPosIdx() == 0)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotReturnText, mReturnButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else if (h->GetGenerateFlag() == 1)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpPHomeGenerateNotMoveText, mReturnButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}
		, Data.mReturnButtonGuide
			, Data.mHomeMoveButtonDim
			);

	mReturnButton->SetTextOffset(VECTOR2(strlen(mReturnButton->GetText()) * -Data.mPopUpTextSize / 4.0f, Data.mPopUpTextSize * 3.0f));


	mHomeLvUpButton = AddRectButton(Data.mHomeLvUpButtonText
		, [this]()
		{
			if (mOwner->GetLevel() < mOwner->GetMaxLevel() && static_cast<PlayerHome*>(mOwner)->GetBattlePoints() >= Data.mHomeLvUpUsePoint)
			{
				int curMaxHp = mOwner->GetMaxHp();
				mOwner->SetLevel(mOwner->GetLevel() + 1);
				mOwner->SetMaxHp((int)(mOwner->GetInitMaxHp() * ((mOwner->GetLevel() + mOwner->GetMaxLevel()) / 10.0f)));
				mOwner->SetHp((int)(round(mOwner->GetMaxHp() * (float)mOwner->GetHp() / (float)curMaxHp)));
				static_cast<PlayerHome*>(mOwner)->SetBattlePoints(static_cast<PlayerHome*>(mOwner)->GetBattlePoints() - Data.mHomeLvUpUsePoint);
				std::ostringstream oss;
				oss << Data.mPopUpHomeLvUpText << "[Lv." << mOwner->GetLevel() << "]";
				auto pop = new UIPopUp(mGame, Data.mPopUpHomeLvUpText, mHomeLvUpButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpPositiveColor);
				pop->NoStrokeRect();
				mGame->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
				if (mUnitMaxNum < mOwner->GetMaxLevel())
				{
					mUnitMaxNum++;
				}
				if (mOwner->GetLevel() == Data.mCanItemGenerateHomeLv)
				{
					mGenerateItemButton->SetState(Button::ButtonState::EEnable);
					auto pop = new UIPopUp(mGame, Data.mPopUpCanGenerateItemText, mGenerateItemButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
					pop->SetTextSize(Data.mPopUpTextSize);
					pop->SetTextColor(Data.mPopUpPositiveColor);
					pop->NoStrokeRect();
					mGame->GetActorManager()->GetStage()->GetLog()->AddText(Data.mCanGenerateItemLogText);
				}
				if (mOwner->GetLevel() == mOwner->GetMaxLevel())
				{
					playSound(mSpecialReleaseSound);
					setVolume(mSpecialReleaseSound, mGame->GetSoundVolumeManager()->GetTmpEffectVolume() + mGame->GetAllData()->eHomeData.mSpecialReleaseSoundVolumeOffset);
					auto pop = new UIPopUp(mGame, Data.mPopUpReleaseSpecialText, mSpecialButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
					pop->SetTextSize(Data.mPopUpTextSize);
					pop->SetTextColor(Data.mPopUpPositiveColor);
					pop->NoStrokeRect();
				}
			}

			else if (mOwner->GetLevel() == mOwner->GetMaxLevel())
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotHomeLvUpText, mHomeLvUpButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpPositiveColor);
				pop->NoStrokeRect();
			}
			else
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotEnoughPointText, mHomeLvUpButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		},
		Data.mHomeLvUpButtonGuide
	);

	mHomeLvUpButton->SetTextOffset(VECTOR2(strlen(mHomeLvUpButton->GetText()) * mGame->GetAllData()->buttonData.mButtonTextSize / -4.0f, -69.0f));

	mGenerateUnitButton = AddRectButton(Data.mGenerateUnitButtonText
		, [this]()
		{
			PlayerHome* h = static_cast<PlayerHome*>(mOwner);
			if (h->GetMoveCompleteFlag() == 1 && ((int)(mGame->GetActorManager()->GetPSide().size()) - 1) <= mGame->GetActorManager()->GetPHome()->GetLevel() && h->GetGenerateFlag() == 0 && (int)(mGame->GetActorManager()->GetPSide().size()) - 1 != mOwner->GetMaxLevel())
			{
				h->SetGenerateFlag(1);
				if (!mGenerate)
				{
					mGenerate = new UIGenerate(this, mGame, UIGenerate::GenerateActor_Id::ECannon);
				}
				else
				{
					mGenerate->CloseMe();
					mGenerate = new UIGenerate(this, mGame, UIGenerate::GenerateActor_Id::ECannon);
				}
			}
			else if (h->GetMoveCompleteFlag() == 0)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpPHomeMoveNotGenerateText, mGenerateUnitButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else if (h->GetGenerateFlag() == 1)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotGenerateInGenerateText, mGenerateUnitButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpFullUnitText, mGenerateUnitButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}
	);

	mGenerateItemButton = AddRectButton(Data.mGenerateItemButtonText,
		[this]()
		{
			PlayerHome* h = static_cast<PlayerHome*>(mOwner);
			if (h->GetMoveCompleteFlag() == 1 && h->GetGenerateFlag() == 0)
			{
				h->SetGenerateFlag(1);
				if (!mGenerate)
				{
					mGenerate = new UIGenerate(this, mGame, UIGenerate::GenerateActor_Id::EBarrier);
				}
				else
				{
					mGenerate->CloseMe();
					mGenerate = new UIGenerate(this, mGame, UIGenerate::GenerateActor_Id::EBarrier);
				}
			}
			else if (h->GetMoveCompleteFlag() == 0)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpPHomeMoveNotGenerateText, mGenerateItemButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else if (h->GetGenerateFlag() == 1)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpNotGenerateInGenerateText, mGenerateItemButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}
	);

	mGenerateItemButton->SetState(Button::ButtonState::EDraw_Enable);

	mStart = std::chrono::system_clock::now();

	mOwner->SetUI(this);

	mSpecialButton = AddCircleButton(Data.mSpecialButtonText,
		[this]()
		{
			auto h = static_cast<PlayerHome*>(mOwner);
			if (h->GetMoveCompleteFlag() == 1 && h->GetGenerateFlag() == 0)
			{
				if (0 < (int)mGame->GetActorManager()->GetEnemies().size())
				{
					std::ostringstream oss;
					auto pop = new UIPopUp(mGame, Data.mLogUseSpecialText, mSpecialButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
					pop->SetTextSize(Data.mPopUpTextSize);
					pop->SetTextColor(Data.mPopUpPositiveColor);
					pop->NoStrokeRect();
					oss << mOwner->GetName().c_str() << "が" << Data.mLogUseSpecialText;
					mGame->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
					mSpecialFlag = false;
					mSpecialEffectFlag = true;
					mEnemySize = (int)mGame->GetActorManager()->GetEnemies().size() * 2;
					mGame->GetCameraManager()->ChangeCamera("PHomeCamera");
				}
				else
				{
					auto pop = new UIPopUp(mGame, Data.mPopUpEmemyEmptyText, mSpecialButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
					pop->SetTextSize(Data.mPopUpTextSize);
					pop->SetTextColor(Data.mPopUpNegativeColor);
					pop->NoStrokeRect();
				}
			}
			else if (h->GetMoveCompleteFlag() == 0)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpMoveSpecialText, mSpecialButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
			else if (h->GetGenerateFlag() == 1)
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpGenerateSpecialText, mSpecialButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(Data.mPopUpTextSize);
				pop->SetTextColor(Data.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		},
		Data.mSpecialButtonGuide
		, Data.mSpecialButtonRadius
	);

	mSpecialButton->SetTextOffset(Data.mSpecialGuideOffset - VECTOR2(strlen(mSpecialButton->GetText()) * mGame->GetAllData()->buttonData.mButtonTextSize / 4.0f, 0.0f));
	mSpecialButton->SetState(Button::ButtonState::EDisable);

}

void UIPlayerHome::draw()
{
	if (mGame->GetState() == Game::GameState::EGameplay && mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		rectMode(CORNER);
		strokeWeight(Data.mHpGaugeEdgeSw);
		stroke(Data.mHpGaugeEdgeColor);

		COLOR color;
		if (mOwner->GetHp() >= mOwner->GetMaxHp() * 0.66f)
		{
			color = Data.mNormalColor;
		}
		else if (mOwner->GetHp() >= mOwner->GetMaxHp() * 0.33f)
		{
			color = Data.mDangarColor;
		}
		else
		{
			color = Data.mDyingColor;
		}

		rectMode(CORNER);
		fill(Data.mHpWindowColor);
		strokeWeight(Data.mHpGaugeEdgeSw);
		rect(mPos.x - Data.mHpGaugeEdgeSw, mPos.y - Data.mHpGaugeEdgeSw, Data.mHpGaugeMaxWidth, Data.mHpGaugeHeight + Data.mHpGaugeEdgeSw * 2.0f);
		if (mOwner->GetHp() > mOwner->GetMaxHp())
		{
			rect(mPos.x + Data.mHpGaugeMaxWidth - Data.mHpGaugeEdgeSw * 1.50f, mPos.y - Data.mHpGaugeEdgeSw, Data.mHpGaugeMaxWidth * ((float)mOwner->GetHp() / (float)mOwner->GetMaxHp()) - Data.mHpGaugeMaxWidth + Data.mHpGaugeEdgeSw, Data.mHpGaugeHeight + Data.mHpGaugeEdgeSw * 2.0f);
		}
		fill(color);
		stroke(color);

		rect(mPos.x - 1.0f, mPos.y - 1.0f, mHpGaugeWidth - Data.mHpGaugeEdgeSw * 1.50f, Data.mHpGaugeHeight + 2.0f);

		if (mOwner->GetHp() <= mOwner->GetMaxHp())
		{
			fill(0, 0, 0);
		}
		else
		{
			fill(Data.mOverMaxHpColor);
		}

		textSize(Data.mHpGaugeHeight);
		text((let)"Lv : " + (let)mOwner->GetLevel() + " Hp : " + mOwner->GetHp() + (let)" / " + mOwner->GetMaxHp(), width / 2.0f - Data.mHpGaugeHeight * 7.0f, mPos.y + Data.mHpGaugeHeight);

		if (mOwner->GetBarrier())
		{
			noStroke();
			fill(Data.mBarrierHpGaugeColor);
			rect(mPos.x + Data.mHpGaugeMaxWidth - mBarrierHpGaugeWidth - Data.mBarrierHpGaugeHeight + Data.mBarrierHpGaugeHeight / 2.0f, mPos.y + Data.mBarrierHpGaugeHeight, mBarrierHpGaugeWidth, Data.mBarrierHpGaugeHeight);
		}

		textSize(Data.mPopUpTextSize);
		fill(0, 0, 0);
		text((let)"ユニット数　" + (let)((int)mGame->GetActorManager()->GetPSide().size() - 1) + (let)" / " + (let)mUnitMaxNum, Data.mUnitSizeTextPos.x, Data.mUnitSizeTextPos.y);
	}
}

void UIPlayerHome::Update()
{
	if (!mOwner)
	{
		CloseMe();
	}
	else
	{
		if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
		{
			float preWidth = mHpGaugeWidth;
			float wid = Data.mHpGaugeMaxWidth * ((float)mOwner->GetHp() / (float)mOwner->GetMaxHp());
			mHpGaugeWidth = preWidth + (wid - preWidth) * 0.05f;

			if (mOwner->GetBarrier())
			{
				float preBWidth = mBarrierHpGaugeWidth;
				float Bwid = Data.mBarrierHpGaugeMaxWidth * ((float)mOwner->GetBarrier()->GetHp() / (float)mOwner->GetBarrier()->GetMaxHp());
				mBarrierHpGaugeWidth = preBWidth + (Bwid - preBWidth) * 0.05f;
			}
		}

		if (mGame->GetState() == Game::GameState::EGameplay && mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
		{
			if (!mGenerate)
			{
				if (mOwner->GetLevel() < Data.mCanItemGenerateHomeLv)
				{
					mGenerateItemButton->SetState(Button::ButtonState::EDraw_Enable);
				}
				else
				{
					mGenerateItemButton->SetState(Button::ButtonState::EEnable);
				}

				if (mOwner->GetLevel() < mOwner->GetMaxLevel() || !mSpecialFlag)
				{
					mSpecialButton->SetState(Button::ButtonState::EDisable);
				}
				else
				{
					mSpecialButton->SetState(Button::ButtonState::EEnable);
				}
			}
			else
			{
				mGenerateItemButton->SetState(Button::ButtonState::EDisable);
				mSpecialButton->SetState(Button::ButtonState::EDisable);
			}

			mCnt++;

			if (mSpecialEffectFlag && mCnt % 7 == 0)
			{
				int num = random(0, (int)mGame->GetActorManager()->GetEnemies().size() - 1);
				auto enemy = mGame->GetActorManager()->GetEnemies()[num];
				auto owner = static_cast<PlayerHome*>(mOwner);
				new PlayerArrow(owner, owner->GetFlag1()->GetPosition(), enemy->GetPosition() + enemy->GetCapsulOffset());
				new PlayerArrow(owner, owner->GetFlag2()->GetPosition(), enemy->GetPosition() + enemy->GetCapsulOffset());

				if (--mEnemySize <= 0)
				{
					mSpecialEffectFlag = false;
					mGame->GetCameraManager()->ChangeCamera("NormalCamera");
				}
			}

			if (!mGenerate)
			{
				if (mTime < mInterval)
				{
					auto end = std::chrono::system_clock::now();
					auto dur = end - mStart;
					auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
					float time = msec / 1000.0f;
					mTime = time;
					mMoveOnButton->SetState(Button::ButtonState::EDraw_Enable);
					mReturnButton->SetState(Button::ButtonState::EDraw_Enable);
				}
				else
				{
					mTime = 0.0f;
					mInterval = 0.0f;
					mMoveOnButton->SetState(Button::ButtonState::EEnable);
					mReturnButton->SetState(Button::ButtonState::EEnable);
				}

				mGenerateUnitButton->SetState(Button::ButtonState::EEnable);
				mHomeLvUpButton->SetState(Button::ButtonState::EEnable);
			}
			else
			{
				mMoveOnButton->SetState(Button::ButtonState::EDisable);
				mReturnButton->SetState(Button::ButtonState::EDisable);
				mGenerateUnitButton->SetState(Button::ButtonState::EDisable);
				mHomeLvUpButton->SetState(Button::ButtonState::EDisable);
			}
		}
		else
		{
			for (auto button : mButtons)
			{
				button->SetState(Button::ButtonState::EDisable);
			}

		}

	}

	mMoveOnButton->SetPosition(mPos + Data.mMoveOnButtonOffset);
	mReturnButton->SetPosition(mMoveOnButton->GetPosition() + Data.mReturnButtonOffset);
	mHomeLvUpButton->SetPosition(mPos + Data.mHomeLvUpButtonOffset);
	mGenerateUnitButton->SetPosition(mPos + Data.mGenerateUnitButtonOffset);
	mGenerateItemButton->SetPosition(mPos + Data.mGenerateItemButtonOffset);
	VECTOR2 spePos = Data.mSpecialButtonOffset;
	spePos.y += mGenerateUnitButton->GetPosition().y;
	mSpecialButton->SetPosition(spePos);

}

void UIPlayerHome::DrawAfterButton()
{
	if (mGame->GetState() == Game::GameState::EGameplay && mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		if (!mGenerate)
		{
			textSize(Data.mPopUpTextSize);
			fill(0, 0, 0);
			text((let)"ポイント　" + (let)static_cast<PlayerHome*>(mOwner)->GetBattlePoints() + " / " + (let)static_cast<PlayerHome*>(mOwner)->GetMaxBattlePoints(), Data.mPointTextPos.x, Data.mPointTextPos.y);
		}

		if (mTime < mInterval)
		{
			VECTOR2 pos = (mMoveOnButton->GetPosition() + mReturnButton->GetPosition()) / 2.0f;
			DrawRing(pos, Data.mIntervalGaugeRingRadius, Data.mIntervalGaugeRingSw, (mInterval - mTime) / mInterval * 3.1415926f / 180.0f, Data.mIntervalGaugeRingRadiusColor, Data.mIntervalGaugeRingAngleOffset);
		}
	}
}

void UIPlayerHome::DrawRing(const VECTOR2& pos, float radius, float sw, float angle, const COLOR& color, float angleOffset)
{
	VECTOR2 centerPos = pos;
	float defAngle = 3.14159264f / 180.0f * angleOffset;
	for (int i = 0; i < 360; i++)
	{
		float preAngle = angle;
		float Angle = (float)i * angle;

		mIntervalAngle = defAngle + preAngle + (Angle - preAngle);

		float px = centerPos.x + cosf(mIntervalAngle) * radius;
		float py = centerPos.y - sinf(mIntervalAngle) * radius;
		stroke(color);
		strokeWeight(mGame->GetAllData()->psData.mLineSw);
		line(px - cosf(mIntervalAngle) * sw / 2.0f, py + sinf(mIntervalAngle) * sw / 2.0f, px + cosf(mIntervalAngle) * sw / 2.0f, py - sinf(mIntervalAngle) * sw / 2.0f);
	}
}
