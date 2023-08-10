#pragma once
#include "UIButton.h"
class CircleButton :
	public Button
{
public:
	CircleButton(const char* name,
		std::function<void()> onClick,
		const VECTOR2& pos,
		float radius,
		class Game* game,
		const char* text = 0,
		const VECTOR2& textOffset = VECTOR2(0, 0)
	);

	bool ContainsPoint(const VECTOR2& pt, bool flag = true);
	void Draw()override;
private:
	float mRadius;
};

