#pragma once
#include "UIScreen.h"
#include "graphic.h"

class UIHelpBase :
    public UIScreen
{
public:
    UIHelpBase(class Game* game);
    virtual ~UIHelpBase();
    void Update()override;
    void draw()override;
    virtual void Closed()override;
    virtual void AddNextButton();
    virtual void AddReturnButton();
    struct DATA
    {
        const char* mCloseText = nullptr;
        const char* mCloseButtonGuide = nullptr;
        const char* mNextText = nullptr;
        const char* mNextButtonGuide = nullptr;
        const char* mReturnText = nullptr;
        const char* mReturnButtonGuide = nullptr;
        int mHelp1Img = -1;
        int mHelp2Img = -1;
        int mHelp3Img = -1;
        int mHelp4Img = -1;
        int mHelp5Img = -1;
        VECTOR2 mCloseButtonPos;
        VECTOR2 mNextButtonPos;
        VECTOR2 mReturnButtonPos;
    };
protected:
    DATA Data;
    int mImgNum;
    std::vector<int>mImgs;
    class Button* mNextButton;
    class Button* mReturnButton;
};

