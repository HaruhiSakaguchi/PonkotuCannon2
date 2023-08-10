#include "UIScroll.h"
#include "input.h"
#include "Game.h"

UIScroll::UIScroll(Game* game)
	: UIScreen(game)
	, mPos(0.0f, 0.0f)
	, mOffset(0.0f, 0.0f)
{
	Data = mGame->GetAllData()->scrollData;
	mPos = Data.mInitPos;
}

void UIScroll::Update()
{
	VECTOR2 mouse = VECTOR2(mouseX, mouseY);
	if (isPress(MOUSE_LBUTTON) && OnRail(mouse) && mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay && mGame->GetState() == Game::GameState::EGameplay)
	{
		mPos.y = mouse.y;
	}

	mOffset = (mPos - Data.mInitPos) * -1.0f;
}

void UIScroll::Draw()
{
	if (mGame->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		strokeWeight(Data.mRadius);
		stroke(Data.mRailColor);
		Line(Data.mInitPos, Data.mMaxPos);
		noStroke();
		fill(Data.mPointColor);
		strokeWeight(Data.mRadius / 2.0f);
		stroke(Data.mPointColor);
		Line(mPos, mPos + Data.mBarLength);
	}
}

bool UIScroll::ContainsPoint(const VECTOR2& pt)
{
	VECTOR2 dist = pt - mPos;
	if (sqrt(dist.x * dist.x + dist.y * dist.y) < Data.mRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UIScroll::OnRail(const VECTOR2& pos)
{
	if (Data.mInitPos.y <= pos.y && pos.y <= Data.mMaxPos.y - Data.mBarLength.y && Data.mInitPos.x - Data.mRadius <= pos.x && pos.x < Data.mInitPos.x + Data.mRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
