#include "UIPSideCharacterStatus.h"
#include "CharacterActor.h"
#include "Cannon.h"
#include "Game.h"
#include "graphic.h"
#include "UIPSideCharacterStatusClose.h"

UIPSideCharacterStatus::UIPSideCharacterStatus(class CharacterActor* owner)
	: UIPSideCharacterStatusBase(static_cast<PSideCharacterActor*>(owner))
	, mCylinderAngle(0.0f)
	, mStateCursorPos(width, 0.0f)
	, mStayButton(nullptr)
	, mReturnButton(nullptr)
	, mHomePatrollButton(nullptr)
	, mFieldPatrollButton(nullptr)
	, mCloseButton(nullptr)
{

	mPosition = VECTOR2(0.0f, (mGame->GetAllData()->itemEffectData.mUIOffsetPosY * 1.5f)) + Data.mUIInitPos;

	mStayButton = AddRectButton(Data.mStayButtonText,
		[this]() {
			class Cannon* c = static_cast<Cannon*>(mOwner);
			c->SetMoveState(Cannon::MoveState::EStay);
			CloseMe();
			new UIPSideCharacterStatusClose(mOwner);
		}
		, Data.mStayButtonGuide
			);

	mStayButton->ConvertReverseButtonGuideTextPos();
	mStayButton->SetTextOffset(VECTOR2(mStayButton->GetTextOffset().x + mGame->GetAllData()->buttonData.mButtonTextSize * strlen(mStayButton->GetText()) / 4.0f - mGame->GetAllData()->buttonData.mButtonTextSize * 2.5f, mStayButton->GetTextOffset().y));

	mReturnButton = AddRectButton(Data.mReturnHomeButtonText,
		[this]() {
			class Cannon* c = static_cast<Cannon*>(mOwner);
			c->SetMoveState(Cannon::MoveState::EReturn);
			CloseMe();
			new UIPSideCharacterStatusClose(mOwner);
		}
		, Data.mReturnHomeButtonGuide
			);

	mReturnButton->ConvertReverseButtonGuideTextPos();
	mReturnButton->SetTextOffset(VECTOR2(mReturnButton->GetTextOffset().x + mGame->GetAllData()->buttonData.mButtonTextSize * strlen(mReturnButton->GetText()) / 4.0f - mGame->GetAllData()->buttonData.mButtonTextSize * 4.5f, mReturnButton->GetTextOffset().y));


	mHomePatrollButton = AddRectButton(Data.mHomePatrollButtonText,
		[this]() {
			class Cannon* c = static_cast<Cannon*>(mOwner);
			c->SetMoveState(Cannon::MoveState::EHomePatroll);
			CloseMe();
			new UIPSideCharacterStatusClose(mOwner);
		}
		, Data.mHomePatrollButtonGuide
			);

	mHomePatrollButton->ConvertReverseButtonGuideTextPos();

	mFieldPatrollButton = AddRectButton(Data.mFieldPatrollButtonText,
		[this]() {
			class Cannon* c = static_cast<Cannon*>(mOwner);
			c->SetMoveState(Cannon::MoveState::EFieldPatroll);
			CloseMe();
			new UIPSideCharacterStatusClose(mOwner);
		}
		, Data.mFieldPatrollButtonGuide
			);

	mFieldPatrollButton->ConvertReverseButtonGuideTextPos();


	mCloseButton = AddRectButton(Data.mCloseButtonText,
		[this]() {
			CloseMe();
			new UIPSideCharacterStatusClose(mOwner);
		}
	);

	AddLvUpButton();

	mStatusState = StatusUIState::EOpen;

}

void UIPSideCharacterStatus::draw()
{
	if (mIsDraw)
	{
		rectMode(CORNER);
		if (mOwner->GetState() == Actor::State::EActive)
		{
			class Cannon* c = static_cast<Cannon*>(mOwner);

			float posy = mPosition.y;
			float Height = Data.mHeight;
			float EdgeHeight = Height * 1.75f;
			float itemWindowPosY = mPosition.y + Data.mItemGaugeWindowOffset.y;
			float itemWindowHeight = Data.mItemGaugeWindowDim;
			if (posy < mUITop)
			{
				Height -= mUITop - posy;
				EdgeHeight -= mUITop - posy;
				posy = mUITop;
			}
			else if (mUIBottom < posy + Height * 1.75f)
			{
				Height = mUIBottom - posy;
				EdgeHeight = Height;
			}

			if (itemWindowPosY < mUITop)
			{
				itemWindowHeight -= mUITop - itemWindowPosY;
				itemWindowPosY = mUITop;
			}
			else if (mUIBottom < itemWindowPosY + itemWindowHeight)
			{
				itemWindowHeight -= itemWindowPosY + itemWindowHeight - mUIBottom;
			}

			if (mUITop < posy + EdgeHeight && posy < mUIBottom)
			{
				fill(Data.mWindowColor);
				stroke(Data.mOpenWindowEdgeColor);
				strokeWeight(Data.mWindowEdgeSw);
				rect(mPosition.x, posy, Data.mWidth, EdgeHeight);
			}
			if (mUITop < posy + Height && posy < mUIBottom)
			{
				noStroke();
				fill(Data.mUIWindowColor);
				rect(mPosition.x, posy, Data.mWidth, Height);
				rect(mPosition.x + Data.mItemGaugeWindowOffset.x, itemWindowPosY, Data.mItemGaugeWindowDim, itemWindowHeight);
				DrawNameandLevel();
			}

			if (mUITop < posy + EdgeHeight && posy < mUIBottom)
			{
				DrawHpGauge(mPosition + Data.mHpGaugeOffset);
			}

			if (mUITop < mPosition.y + Data.mSpeedGaugeOffset.y - Data.mLaunchRingRadius && mPosition.y + Data.mSpeedGaugeOffset.y + Data.mLaunchRingRadius < mUIBottom)
			{
				DrawItemEffectLifeSpanGauge(c->GetSpeed(), Data.mSpeedGaugeOffset);
			}
			if (mUITop < mPosition.y + Data.mPowerGaugeOffset.y - Data.mLaunchRingRadius && mPosition.y + Data.mPowerGaugeOffset.y + Data.mLaunchRingRadius < mUIBottom)
			{
				DrawItemEffectLifeSpanGauge(c->GetPower(), Data.mPowerGaugeOffset);
			}
			if (mUITop < mPosition.y + Data.mRapidGaugeOffset.y - Data.mLaunchRingRadius && mPosition.y + Data.mRapidGaugeOffset.y + Data.mLaunchRingRadius < mUIBottom)
			{
				DrawItemEffectLifeSpanGauge(c->GetRapid(), Data.mRapidGaugeOffset);
			}
			if (mUITop < mPosition.y + Data.mBarrierGaugeOffset.y - Data.mLaunchRingRadius && mPosition.y + Data.mBarrierGaugeOffset.y + Data.mLaunchRingRadius < mUIBottom)
			{
				DrawItemEffectLifeSpanGauge(c->GetBarrier(), Data.mBarrierGaugeOffset);
			}

			if (mUITop < mPosition.y + Data.mLaunchRingOffset.y - Data.mLaunchRingRadius && mPosition.y + Data.mLaunchRingOffset.y + Data.mLaunchRingRadius < mUIBottom)
			{
				DrawLaunchIntervalGauge();
			}

		}
	}
}

void UIPSideCharacterStatus::update()
{
	if (mOwner->GetState() == Actor::State::EActive)
	{
		Cannon* c = static_cast<Cannon*>(mOwner);
		float preAngle = mCylinderAngle;
		mCylinderAngle = preAngle + (3.1415926f * 2.0f / Data.mMaxItemNum * (-static_cast<Cannon*>(mOwner)->GetCnt()) - preAngle) * Data.mChangeAngleSpeed;
	}

	class Cannon* c = static_cast<Cannon*>(mOwner);
	VECTOR2 preCursorPos = mStateCursorPos;
	VECTOR2 cursorPos;

	if (c->GetMoveState() == Cannon::MoveState::EStay)
	{
		cursorPos = mStayButton->GetPosition();
	}
	else if (c->GetMoveState() == Cannon::MoveState::EReturn)
	{
		cursorPos = mReturnButton->GetPosition();

	}
	else if (c->GetMoveState() == Cannon::MoveState::EHomePatroll)
	{
		cursorPos = mHomePatrollButton->GetPosition();

	}
	else if (c->GetMoveState() == Cannon::MoveState::EFieldPatroll)
	{
		cursorPos = mFieldPatrollButton->GetPosition();

	}

	mStateCursorPos = preCursorPos + (cursorPos - preCursorPos) * 0.5f;

	mStayButton->SetPosition(mPosition + Data.mStayButtonOffset);
	mReturnButton->SetPosition(mPosition + Data.mReturnButtonOffset);
	mHomePatrollButton->SetPosition(mPosition + Data.mHomePatrollButtonOffset);
	mFieldPatrollButton->SetPosition(mPosition + Data.mFieldPatrollButtonOffset);
	mCloseButton->SetPosition(mPosition + Data.mCloseButtonOffset);
	mLvUpButton->SetPosition(mPosition + Data.mOpenLvUpButtonOffset);

}

void UIPSideCharacterStatus::DrawRing(const VECTOR2& pos, float radius, float sw, const COLOR& color)
{
	for (int i = 0; i < 90; i++)
	{
		float px = cosf((float)i * 360.0f * 2.0f) * radius;
		float py = -sinf((float)i * 360.0f * 2.0f) * radius;
		fill(color);
		noStroke();
		circle(pos.x + px, pos.y + py, sw);
	}
}

void UIPSideCharacterStatus::DrawRingOnLine(const VECTOR2& pos, float radius, float dia, float angle, const COLOR& color)
{
	colorMode(RGB);
	VECTOR2 centerPos = pos;
	VECTOR2 lineEdgePos = VECTOR2(centerPos.x + cosf(angle) * radius, centerPos.y - sinf(angle) * radius);
	strokeWeight(Data.mLineSw);
	stroke(color);
	line(lineEdgePos.x - cosf(angle) * dia / 2.0f, lineEdgePos.y + sinf(angle) * dia / 2.0f, lineEdgePos.x + cosf(angle) * dia / 2.0f, lineEdgePos.y + -sinf(angle) * dia / 2.0f);
}

void UIPSideCharacterStatus::DrawRing(const VECTOR2& pos, float radius, float sw, float angle, const COLOR& color, float angleOffset)
{
	VECTOR2 centerPos = pos;
	float defAngle = 3.14159264f / 180.0f * angleOffset;
	for (int i = 0; i < 360; i++)
	{
		float preAngle = angle;
		float Angle = (float)i * angle;

		Data.mAngle = defAngle + preAngle + (Angle - preAngle);

		float px = centerPos.x + cosf(Data.mAngle) * radius;
		float py = centerPos.y - sinf(Data.mAngle) * radius;
		stroke(color);
		strokeWeight(Data.mLineSw);
		line(px - cosf(Data.mAngle) * sw / 2.0f, py + sinf(Data.mAngle) * sw / 2.0f, px + cosf(Data.mAngle) * sw / 2.0f, py - sinf(Data.mAngle) * sw / 2.0f);
	}
}

void UIPSideCharacterStatus::DrawLaunchIntervalGauge()
{
	class Cannon* c = static_cast<Cannon*>(mOwner);

	DrawRing(mPosition + Data.mLaunchRingOffset, Data.mLaunchRingRadius, Data.mLaunchRingSw, Data.mWhiteRingColor);
	DrawRing(mPosition + Data.mLaunchRingOffset, Data.mLaunchRingRadius, Data.mLaunchRingSw, 3.1415926f / 180.0f * c->GetTimer() / c->GetInterval(), Data.mGaugeRingColor);

	for (int i = 0; i < 8; i++)
	{
		DrawRingOnLine(mPosition + Data.mLaunchRingOffset, Data.mLaunchRingRadius, Data.mLaunchRingSw, (float)(i * 3.14159264f / 4.0f), Data.mRingOnLineColor);
	}

	strokeWeight(Data.mStockItemWeight);
	stroke(Data.mItemColors[c->GetItemNums()[c->GetCnt()]]);
	point(mPosition.x + Data.mLaunchRingOffset.x, mPosition.y + Data.mLaunchRingOffset.y);

	for (int i = 0; i < (int)c->GetItemNums().size(); i++)
	{
		stroke(Data.mItemColors[c->GetItemNums()[i]]);
		point(mPosition.x + cosf(3.1415926f * 2.0f / Data.mMaxItemNum * i + mCylinderAngle) * Data.mItemCylinderRadius + Data.mLaunchRingOffset.x, mPosition.y + -sinf(3.1415926f * 2.0f / Data.mMaxItemNum * i + mCylinderAngle) * Data.mItemCylinderRadius + Data.mLaunchRingOffset.y);
	}

}

void UIPSideCharacterStatus::DrawItemEffectLifeSpanGauge(class ItemEffect* item, const VECTOR2& pos)
{
	stroke(Data.mWhiteRingColor);
	strokeWeight(Data.mLaunchRingSw);

	COLOR color;
	if (!item)
	{
		color = Data.mNoItemColor;
	}
	else
	{
		color = Data.mWhiteRingColor;
	}

	fill(color);
	circle(mPosition.x + pos.x, mPosition.y + pos.y, Data.mItemIconRadius);

	DrawRing(mPosition + pos, Data.mItemIconRadius / 2.0f, Data.mLaunchRingSw, Data.mWhiteRingColor);


	if (item)
	{
		float preTime = item->GetKeepTime();

		float Time = preTime + (item->GetTime() - preTime) * Data.mChangeTimeSpeed;

		item->SetKeepTime(Time);

		DrawRing(mPosition + pos, Data.mItemIconRadius / 2.0f, Data.mLaunchRingSw, (3.1415926f / 180.0f) * item->GetKeepTime() / item->GetInterval(), item->GetColor(), Data.mItemIconRadius * 2.0f);
		fill(0, 0, 0);
		textSize(Data.mItemLvTextSize);
		text(item->GetLevel(), mPosition.x + pos.x - Data.mItemLvTextSize / 4.0f, mPosition.y + pos.y + Data.mItemLvTextSize / 2.0f);

	}

	for (int i = 0; i < 8; i++)
	{
		DrawRingOnLine(mPosition + pos, Data.mItemIconRadius / 2.0f, Data.mLaunchRingSw, (float)(i * 3.14159264f / 4.0f), COLOR(0, 0, 0));
	}
}

void UIPSideCharacterStatus::DrawStateCursor()
{
	stroke(Data.mStateCursorColor);
	strokeWeight(Data.mStateCursorSw);
	fill(0, 0, 0, 0);
	rectMode(CENTER);
	rect(mStateCursorPos.x, mStateCursorPos.y, Data.mStateCursorDim, Data.mStateCursorDim);
	rectMode(CORNER);
	fill(0, 0, 0);
}

void UIPSideCharacterStatus::DrawAfterButton()
{
	if (mStayButton->GetState() == Button::ButtonState::EEnable)
	{
		DrawStateCursor();
	}
}

