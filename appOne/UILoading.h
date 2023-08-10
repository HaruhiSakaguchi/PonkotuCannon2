#pragma once
#include "UIScreen.h"
#include <chrono>

class UILoading :
    public UIScreen
{
public:
    UILoading(class Game* game);
    void Closed()override;
    void Draw()override;
    void Update()override;
    struct DATA
    {
        float mContainerLoadStartTime = 0.0f;
        float mChangeStateTime = 0.0f;
        float mTextSize = 0.0f;
        float mMaxAlpha = 0.0f;
        float mAddTextInterval = 0.0f;
        float mPlusAlpha = 0.0f;
        float mStateChangeAlpha = 0.0f;
        int mRev = 0;
        int mAddTextSize = 0;
        const char* mText = nullptr;
        const char* mAddText[4]
        {
            nullptr,nullptr,nullptr,nullptr
        };
        COLOR mTextColor;
        COLOR mBackColor;
    };
private:
    DATA Data;
    std::chrono::system_clock::time_point mStart;
    float mAlpha;
    float mTime;
    VECTOR2 mTextPos;
    std::string mString;
    int mAddTextCnt;
    float mBeforeAddTextTime;
    float mNextAddTextTime;
};

