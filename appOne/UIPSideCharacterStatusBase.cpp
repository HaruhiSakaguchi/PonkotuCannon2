#include "UIPSideCharacterStatusBase.h"
#include "Game.h"
#include "PlayerHome.h"
#include "UIPopUp.h"
#include "input.h"
#include "UIScroll.h"

float UIPSideCharacterStatusBase::mUITop = 0.0f;
float UIPSideCharacterStatusBase::mUIBottom = 0.0f;

UIPSideCharacterStatusBase::UIPSideCharacterStatusBase(PSideCharacterActor* owner)
	: UIScreen(owner->GetGame())
	, mOwner(owner)
	, mPosition(0.0f, 0.0f)
	, mLvUpButton(nullptr)
	, mHpGaugeWidth(0.0f)
	, mBarrierHpGaugeWidth(0.0f)
	, mStatusState(StatusUIState::EBase)
	, mIsDraw(true)
{
	Data = mGame->GetAllData()->psData;

	mGame->GetUIManager()->AddUIPSide(this);
	mOwner->SetUI(this);

	mUITop = mGame->GetAllData()->uiPHomeData.mUnitSizeTextPos.y + mGame->GetAllData()->uiPHomeData.mPopUpTextSize;
	mUIBottom = mGame->GetAllData()->logData.mPos.y;
}

UIPSideCharacterStatusBase::~UIPSideCharacterStatusBase()
{
	mGame->GetUIManager()->RemoveUIPSide(this);
}

void UIPSideCharacterStatusBase::Update()
{
	if (!mOwner)
	{
		CloseMe();
	}
	else
	{
		if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
		{
			mIsDraw = true;
		}
		else
		{
			mIsDraw = false;
		}

		if (mPosition.x > mGame->GetAllData()->itemEffectData.mUIMinPosX)
		{
			mPosition.x += mGame->GetAllData()->itemEffectData.mUIPosAdvSpeed;
		}

		int num = mOwner->GetNum();

		if (mGame->GetActorManager()->GetPHome() && num > mGame->GetActorManager()->GetPHome()->GetNum())
		{
			num--;
		}

		mPosition.y = (mGame->GetAllData()->itemEffectData.mUIOffsetPosY / 2.0f) * num + Data.mUIOffsetPosY;

		int cnt = 0;

		for (auto ui : mGame->GetUIManager()->GetUIPSideStatus())
		{
			if (mOwner->GetNum() > ui->GetOwner()->GetNum() && ui->GetStatusState() == StatusUIState::EOpen)
			{
				cnt++;
			}
		}

		mPosition.y += (mGame->GetAllData()->itemEffectData.mUIOffsetPosY * 1.5f) * cnt + mGame->GetActorManager()->GetStage()->GetScroll()->GetOffset().y;

		float preWidth = mHpGaugeWidth;
		float wid = Data.mHpGaugeMaxWidth * mOwner->GetHp() / mOwner->GetMaxHp();
		mHpGaugeWidth = preWidth + (wid - preWidth) * 0.05f;

		if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
		{
			if (mOwner->GetBarrier())
			{
				float preBWidth = mBarrierHpGaugeWidth;
				float Bwid = Data.mBarrierHpGaugeMaxWidth * mOwner->GetBarrier()->GetHp() / mOwner->GetBarrier()->GetMaxHp();
				mBarrierHpGaugeWidth = preBWidth + (Bwid - preBWidth) * 0.05f;
			}
		}

		update();

		if (!mGame->GetActorManager()->GetPHome() || mGame->GetState() != Game::GameState::EGameplay || mGame->GetCurState()->GetMState() != UIMainState::State::EGamePlay)
		{
			if (mGame->GetCurState()->GetMState() != UIMainState::State::EGamePlay)
			{
				for (auto button : GetButtons())
				{
					button->SetState(Button::ButtonState::EDisable);
				}
			}
			else
			{
				for (auto button : GetButtons())
				{
					button->SetState(Button::ButtonState::EDraw_Enable);
				}
			}
		}
		else
		{
			for (auto button : GetButtons())
			{
				if (mUITop < button->GetPosition().y - button->GetRectButtonDim().y / 2.0f && button->GetPosition().y + button->GetRectButtonDim().y / 2.0f < mUIBottom)
				{
					if (mGame->GetActorManager()->GetPHome() && static_cast<UIPlayerHome*>(mGame->GetActorManager()->GetPHome()->GetUI())->GetGenerate())
					{
						button->SetState(Button::ButtonState::EDraw_Enable);
					}
					else
					{
						button->SetState(Button::ButtonState::EEnable);
					}
				}
				else
				{
					button->SetState(Button::ButtonState::EDisable);
				}
			}
		}

	}
}

void UIPSideCharacterStatusBase::DrawHpGauge(const VECTOR2& pos)
{
	rectMode(CORNER);

	COLOR color;
	if (mOwner->GetHp() >= mOwner->GetMaxHp() * 0.66f)
	{
		color = Data.mHpNormalColor;
	}
	else if (mOwner->GetHp() >= mOwner->GetMaxHp() * 0.33f)
	{
		color = Data.mHpDangarColor;
	}
	else
	{
		color = Data.mHpDyingColor;
	}

	if (mUITop < pos.y + Data.mHpGaugeInitOffset.y && pos.y + Data.mHpGaugeInitOffset.y + Data.mHpGaugeHeight < mUIBottom)
	{
		noStroke();
		fill(Data.mUIWindowColor);
		rect(pos.x + Data.mHpGaugeInitOffset.x, pos.y + Data.mHpGaugeInitOffset.y, Data.mHpGaugeMaxWidth, Data.mHpGaugeHeight);
		fill(color);
		rect(pos.x + Data.mHpGaugeInitOffset.x, pos.y + Data.mHpGaugeInitOffset.y, mHpGaugeWidth, Data.mHpGaugeHeight);
		fill(0, 0, 0);
		textSize(Data.mNameandLvTextSize);
		text("Hp :" + (let)mOwner->GetHp() + "/" + (let)mOwner->GetMaxHp(), pos.x + 4.5f * Data.mNameandLvTextSize / 2.0f, pos.y + Data.mHpGaugeInitOffset.y + Data.mNameandLvTextSize - 2.5f);

		if (mOwner->GetBarrier())
		{
			DrawBarrierHpGauge(pos);
		}
	}

	if (mLvUpButton->ContainsPoint(VECTOR2(mouseX, mouseY)) && mOwner->GetLevel() < mOwner->GetMaxLevel())
	{
		textSize(Data.mNameandLvTextSize);
		fill(255, 255, 255);
		text("(" + (let)(mGame->GetAllData()->pHomeData.mLvUpBasePoint + mOwner->GetLevel() * mGame->GetAllData()->pHomeData.mLvEveryUpPoint) + "ポイント必要)", mLvUpButton->GetPosition().x + mLvUpButton->GetTextOffset().x + strlen(mLvUpButton->GetText()) * Data.mNameandLvTextSize * 2.0f / 3.0f, mLvUpButton->GetPosition().y + mLvUpButton->GetTextOffset().y + Data.mNameandLvTextSize * 2.0f);
	}

}
void UIPSideCharacterStatusBase::DrawBarrierHpGauge(const VECTOR2& pos)
{
	VECTOR2 Pos = VECTOR2(pos.x + Data.mHpGaugeInitOffset.x - mBarrierHpGaugeWidth + Data.mHpGaugeMaxWidth, pos.y + Data.mBarrierHpGaugeMaxWidth / 2.0f);
	float barrierHeight = Data.mBarrierHpGaugeHeight;

	if (mUITop < Pos.y && Pos.y + Data.mBarrierHpGaugeHeight < mUIBottom)
	{
		rectMode(CORNER);
		noStroke();
		fill(Data.mBarrierHpGaugeColor);
		rect(Pos.x, Pos.y, mBarrierHpGaugeWidth, barrierHeight);
	}
}

void UIPSideCharacterStatusBase::OwnerLvUp()
{
	int lvUpUsePoint = (mGame->GetAllData()->pHomeData.mLvUpBasePoint + mOwner->GetLevel() * mGame->GetAllData()->pHomeData.mLvEveryUpPoint);
	if (mOwner->GetLevel() < mGame->GetActorManager()->GetPHome()->GetLevel() && lvUpUsePoint <= mGame->GetActorManager()->GetPHome()->GetBattlePoints())
	{
		int curMaxHp = mOwner->GetMaxHp();
		mOwner->GetGame()->GetActorManager()->GetPHome()->SetBattlePoints(mOwner->GetGame()->GetActorManager()->GetPHome()->GetBattlePoints() - lvUpUsePoint);
		mOwner->SetLevel(mOwner->GetLevel() + 1);
		mOwner->SetMaxHp((int)(mOwner->GetInitMaxHp() * ((mOwner->GetLevel() + mOwner->GetMaxLevel()) / 10.0f)));
		mOwner->SetHp((int)(round(mOwner->GetMaxHp() * (float)mOwner->GetHp() / (float)curMaxHp)));
		std::ostringstream oss;
		oss << mOwner->GetName().c_str() << "のLvが上がった！！";

		auto pop = new UIPopUp(mGame, oss.str().c_str(), mPosition, 1, VECTOR2(0.0f, -1.0f));
		pop->SetTextSize(Data.mPopUpTextSize);
		pop->SetTextColor(Data.mPopUpPositiveColor);
		pop->NoStrokeRect();

		oss << "[lv." << mOwner->GetLevel() << "]";
		mOwner->GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	}
	else if (mOwner->GetLevel() == mGame->GetActorManager()->GetPHome()->GetMaxLevel())
	{
		auto pop = new UIPopUp(mGame, "Lvはこれ以上上がらない！！", mPosition, 1, VECTOR2(0.0f, -1.0f));
		pop->SetTextSize(Data.mPopUpTextSize);
		pop->SetTextColor(Data.mPopUpPositiveColor);
		pop->NoStrokeRect();
	}
	else if (mOwner->GetLevel() >= mGame->GetActorManager()->GetPHome()->GetLevel())
	{
		auto pop = new UIPopUp(mGame, "HomeのLvを超えることはできない", mPosition, 1, VECTOR2(0.0f, -1.0f));
		pop->SetTextSize(Data.mPopUpTextSize);
		pop->SetTextColor(Data.mPopUpNegativeColor);
		pop->NoStrokeRect();
	}
	else if (lvUpUsePoint > mGame->GetActorManager()->GetPHome()->GetBattlePoints())
	{
		auto pop = new UIPopUp(mGame, "ポイントが足りない", mPosition, 1, VECTOR2(0.0f, -1.0f));
		pop->SetTextSize(Data.mPopUpTextSize);
		pop->SetTextColor(Data.mPopUpNegativeColor);
		pop->NoStrokeRect();
	}

}

void UIPSideCharacterStatusBase::DrawNameandLevel()
{
	VECTOR2 pos = VECTOR2(mPosition.x + Data.mNameandLvTextSize, mPosition.y + Data.mNameandLvTextSize);
	if (mUITop < pos.y && pos.y + Data.mNameandLvTextSize < mUIBottom)
	{
		rectMode(CORNER);
		textSize(Data.mNameandLvTextSize);
		std::ostringstream oss;
		oss << mOwner->GetName().c_str() << " Lv." << mOwner->GetLevel();
		fill(0, 0, 0);
		text(oss.str().c_str(), pos.x, pos.y);
	}
}

void UIPSideCharacterStatusBase::AddLvUpButton()
{
	mLvUpButton = AddRectButton(Data.mLvUpButtonText,
		[this]() {
			OwnerLvUp();
		}
		, Data.mLvUpButtonGuide
			);

	mLvUpButton->SetTextOffset(VECTOR2(mLvUpButton->GetTextOffset().x * -3.0f, mLvUpButton->GetTextOffset().y));
}
