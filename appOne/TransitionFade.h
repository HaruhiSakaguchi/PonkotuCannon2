#pragma once
#include "Transition.h"

class TransitionFade :
	public Transition
{
public:
	TransitionFade(class Game* game);
	void create()override;
	void inTriggerProc();
	bool inProc();
	void outTriggerProc();
	bool outProc();
public:
	struct DATA
	{
		float mMaxAlpha = 255.0f;
		float mDefaultTime = 1.7f;
		COLOR mDefaultColor = COLOR(0, 0, 0);
	};
private:
	DATA Data;
	COLOR mColor;
	float mTime;
};

