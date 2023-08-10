#include "TransitionFade.h"
#include "window.h"
#include "graphic.h"
#include "Game.h"
#include "Container.h"

TransitionFade::TransitionFade(class Game* game)
	: Transition(game)
	, mColor(0, 0, 0)
	, mTime(0.0f)
{
	create();
}

void TransitionFade::create() {
	colorMode(RGB, Data.mMaxAlpha);
	mColor = Data.mDefaultColor;
	mTime = Data.mDefaultTime;
}

void TransitionFade::inTriggerProc() {
	rectMode(CORNER);
	colorMode(RGB, Data.mMaxAlpha);
	noStroke();
	mColor.a = Data.mMaxAlpha;
	fill(mColor);
	rect(0, 0, width, height);
}

bool TransitionFade::inProc() {
	rectMode(CORNER);
	colorMode(RGB, Data.mMaxAlpha);
	noStroke();
	fill(mColor);
	rect(0, 0, width, height);
	mColor.a -= Data.mMaxAlpha / mTime * delta;
	if (mColor.a < 0.0f) {
		return true;
	}
	return false;
}

void TransitionFade::outTriggerProc() {
	mColor.a = 0.0f;
}

bool TransitionFade::outProc() {
	rectMode(CORNER);
	colorMode(RGB, Data.mMaxAlpha);
	noStroke();
	fill(mColor);
	rect(0, 0, width, height);
	mColor.a += Data.mMaxAlpha / mTime * delta;
	if (mColor.a >= Data.mMaxAlpha) {
		return true;
	}
	return false;
}