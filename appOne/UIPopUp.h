#pragma once
#include "UIScreen.h"
#include <chrono>

class UIPopUp :
    public UIScreen
{
public:
    UIPopUp(class Game* game, const char* text, const VECTOR2& pos, int lifeSpan = 1, const VECTOR2& vec = VECTOR2(0.0f, 0.0f));
    void Update()override;
    void Draw()override;
    void SetTextColor(const COLOR& color) { mTextColor = color; }
    void SetTextSize(float size) { mTextSize = size; }
    void SetRectColor(const COLOR& color) { mRectColor = color; }
    void NoStrokeRect() { mIsStrokeRect = false; }
private:
    VECTOR2 mPos;
    VECTOR2 mVec;
    int mLifeSpan;
    int mTime;
    float mTextSize;
    COLOR mTextColor;
    COLOR mRectColor;
    std::chrono::system_clock::time_point mStart;
    bool mIsStrokeRect;
};

