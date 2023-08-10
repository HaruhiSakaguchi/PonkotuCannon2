#pragma once
#include "UIState.h"

class UIMainState :
    public UIState
{

public:
    UIMainState(class Game* game);
    enum class State : int
    {
        ETitle,
        EGamePlay,
        EStageClear,
        EGameOver,
        EAllClear,
        EQuit,
        EEmpty
    };

    void SetMState(State state) { mMState = state; }
    State GetMState() { return mMState; }

protected:
    State mMState;
};

