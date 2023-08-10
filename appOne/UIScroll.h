#pragma once
#include "UIScreen.h"
class UIScroll :
	public UIScreen
{
public:
	UIScroll(class Game* game);
	void Update() override;
	void Draw()override;
	bool ContainsPoint(const VECTOR2& pt);
	bool OnRail(const VECTOR2& pos);
	const VECTOR2& GetOffset() { return mOffset; }
	struct DATA
	{
		float mRadius = 0.0f;
		VECTOR2 mInitPos;
		VECTOR2 mMaxPos;
		VECTOR2 mBarLength;
		COLOR mPointColor;
		COLOR mRailColor;
	};
private:
	DATA Data;
	VECTOR2 mPos;
	VECTOR2 mOffset;
};

