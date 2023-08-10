#pragma once
#include "UIMainState.h"
#include "sound.h"

class AllClear : public UIMainState
{
public:
	AllClear(class Game* game);
	~AllClear();
	void ChangeOption()override;
	void draw()override;
	void Update()override;
	struct DATA
	{
		int mBgm = -1;
		int mImg = -1;
		const char* mReturnTitleText = nullptr;
		const char* mQuitText = nullptr;
		VECTOR2 mButtonPos;
	};
private:
	DATA Data;
	bool mIsChangeTitle;
};
