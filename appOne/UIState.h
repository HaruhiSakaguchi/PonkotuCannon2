#pragma once
#include "UIScreen.h"

//UIを継承したステート遷移専用クラス

class UIState : public UIScreen
{
public:
	UIState(class Game* game);
	virtual int SetUp() { return 1; }
	virtual void Update()override;
	void ChangeState();
	virtual void ChangeOption() {};//ステート遷移の際に追加でUpdateの中で呼び出す。
};