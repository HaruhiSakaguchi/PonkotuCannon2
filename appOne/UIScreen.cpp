#include "UIScreen.h"
#include "graphic.h"
#include "input.h"
#include "Game.h"
#include "Container.h"
#include "TransitionFade.h"
#include "UIButton.h"
#include "UICircleButton.h"

UIScreen::UIScreen(Game* game)
	: mGame(game)
	, mState(UIState::EActive)
	, mBackImg(-1)
	, mTextSize(40.0f)
	, mTitlePos(width / 2.0f, 100.0f)
	, mButtonPos(width / 2.0f, 170.0f)
	, mBackPos(0.0f, 0.0f)
	, mTitleColor(0, 0, 0)
	, mButtonTextcolor(0, 0, 0)
{
	//GameのUIStackに追加
	mGame->GetUIManager()->PushUI(this);
}

UIScreen::~UIScreen()
{
	for (auto b : mButtons)
	{
		delete b;
	}
	mButtons.clear();
	mGame->GetUIManager()->PullUI(this);
}

void UIScreen::ProcessInput()
{
	// ボタンがあるなら
	if (!mButtons.empty())
	{
		// マウスの位置を取得
		VECTOR2 mousePos = VECTOR2(mouseX, mouseY);
		// 全ボタンのチェック
		for (auto b : mButtons)
		{
			// ロールオーバーしていたら
			if (b->ContainsPoint(mousePos))
			{
				if (mGame->GetRenderer()->GetTransition()->inEndFlag())
				{
					//サウンドフラッグが立っていなかったら音を鳴らす。鳴らすとサウンドフラッグが立つ。
					if (!b->GetSound())
					{
						b->Update();
					}
					if (isTrigger(MOUSE_LBUTTON))
					{
						b->OnClick();
					}
				}
			}
		}
	}
}

void UIScreen::Draw()
{
	rectMode(CENTER);
	// 背景画像表示（もしあったら）
	if (mBackImg >= 0)
	{
		image(mBackImg, mBackPos.x, mBackPos.y);
	}

	draw();

	rectMode(CENTER);

	// タイトル表示（もしあったら）
	if (mTitle.c_str())
	{
		textSize(mTextSize);
		fill(mTitleColor);
		text(mTitle.c_str(),
			mTitlePos.x - mTitle.length() * mTextSize / 4.0f,//半角文字のみ対応
			mTitlePos.y + mTextSize / 2.0f
		);
	}

	// ボタン表示（もしあったら）
	for (auto b : mButtons)
	{
		b->Draw();
	}

	DrawAfterButton();

}

void UIScreen::CloseMe()
{
	if (this)
	{
		mState = UIState::EClosing;
	}
}

Button* UIScreen::AddRectButton(const char* name, std::function<void()> onClick, const char* text, const VECTOR2 dim, const COLOR onColor, const COLOR& offColor)
{
	Button* b = new Button(name, onClick, mButtonPos, mGame, text);
	b->SetRectButtonDim(dim);
	b->SetContainsRectButtonCOLOR(onColor);
	b->SetNoContainsRectButtonCOLOR(offColor);
	mButtons.emplace_back(b);
	mButtonPos.y += mGame->GetAllData()->buttonData.mBasicOffsetY;
	return b;
}

Button* UIScreen::AddCircleButton(const char* name, std::function<void()> onClick, const char* text, float radius, const COLOR onColor, const COLOR& offColor)
{
	Button* b = new CircleButton(name, onClick, mButtonPos, radius, mGame, text);

	b->SetContainsRectButtonCOLOR(onColor);
	b->SetNoContainsRectButtonCOLOR(offColor);

	mButtons.emplace_back(b);
	mButtonPos.y += mGame->GetAllData()->buttonData.mBasicOffsetY;

	return b;
}

void UIScreen::SetOtherUIButtonState(Button::ButtonState state)
{
	for (auto ui : mGame->GetUIManager()->GetUIStack())
	{
		if (ui != this)
		{
			for (auto button : ui->GetButtons())
			{
				button->SetBeforeState(button->GetState());
				if (button->GetState() == Button::ButtonState::EDisable && state == Button::ButtonState::EDraw_Enable)
				{
					continue;
				}
				button->SetState(state);
			}
		}
	}
}

void UIScreen::SetOtherUIButtonBeforeState()
{
	for (auto ui : mGame->GetUIManager()->GetUIStack())
	{
		if (ui != this)
		{
			for (auto button : ui->GetButtons())
			{
				button->SetState(button->GetBeforeState());
			}
		}
	}
}

void UIScreen::Line(const VECTOR2& p1, const VECTOR2& p2) { line(p1.x, p1.y, p2.x, p2.y); }