#pragma once
#include <functional>
#include "COLOR.h"
#include "VECTOR2.h"
#include <string>
#include "sound.h"
#include "UIButton.h"

//ユーザーインターフェイス基底クラス
class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();
	// 派生クラスでオーバーライド可能
	virtual void ProcessInput();
	virtual void Update() {};
	virtual void Draw();
	virtual void draw() {};
	virtual void DrawAfterButton() {};
	virtual void Closed() {};

	// UIステート。アクティブか、閉じるか
	enum class UIState
	{
		EActive,
		EClosing
	};

	void SetBackPos(const VECTOR2& pos) { mBackPos = pos; }
	const VECTOR2& GetBackPos() { return mBackPos; }
	// UIステートをClosingに設定
	void CloseMe();
	// UIステートを取得
	UIState GetState() const { return mState; }
	void SetState(UIState state) { mState = state; }
	// UIタイトルを設定
	void SetTitle(const char* text) { mTitle = text; }
	const char* GetTitle() { return mTitle.c_str(); }

	std::vector<class Button*>& GetButtons() { return mButtons; }

	// ボタンを追加（縦に配置されていく）
	class Button* AddRectButton(const char* name, std::function<void()> onClick, const char* text = 0, const VECTOR2 dim = VECTOR2(44.0f, 44.0f), const COLOR onColor = COLOR(200, 180, 116), const COLOR& offColor = COLOR(99, 163, 200));
	class Button* AddCircleButton(const char* name, std::function<void()> onClick, const char* text = 0, float radius = 50.0f, const COLOR onColor = COLOR(200, 180, 116), const COLOR& offColor = COLOR(99, 163, 200));

	void SetOtherUIButtonState(Button::ButtonState state);
	void SetOtherUIButtonBeforeState();
	void Line(const VECTOR2& p1, const VECTOR2& p2);
protected:
	class Game* mGame;
	// ステート
	UIState mState;
	//背景画像
	int mBackImg;
	VECTOR2 mBackPos;
	//タイトル文字とその属性
	std::string mTitle;
	COLOR mTitleColor;
	VECTOR2 mTitlePos;
	float mTextSize;
	//ボタン
	std::vector<class Button*> mButtons;
	VECTOR2 mButtonPos;
	COLOR mButtonTextcolor;
};

