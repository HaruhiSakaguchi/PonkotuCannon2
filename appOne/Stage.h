#pragma once
#include "Map.h"
class Stage :
    public Map
{
public:
    Stage(class Game* game);
    int SetUp()override;
    struct DATA
    {
        float mEnemyHomeAngleOffset = 0.0f;
        float mFirstCannonAngleOffset = 0.0f;
        VECTOR mPlayerHomeDefaultPos;
        VECTOR mEnemyHomeDefaultPos;
        VECTOR mFirstCannonDefaultPos;
    };
private:
    DATA Data;
    const char* mMaptext1 = "Assets\\All_Map\\BackGround\\Collision.txt";
};

