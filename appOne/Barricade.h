#pragma once
#include "PSideCharacterActor.h"

class Barricade :
    public PSideCharacterActor
{
public:
    Barricade(class Game* game);
    int SetUp()override;
    void UpdateActor()override;
    void Dead()override;
    void SetBNum(int num) { mBNum = num; }
    int GetBNum() { return mBNum; }
    struct DATA
    {
        int mHp = 0;
        float mGravity = 0.0f;
        float mRadius = 0.0f;
        float mAdvSpeed = 0.0f;
        int mJumpFlag = 0;
        float mMaxDamageInterval = 0.0f;
        int mCollisionSound = -1;
        int mCollisionSoundVolumeOffset = 0;

        COLOR mImageColor;
        VECTOR mCapsuleOffset;
    };
private:
    DATA Data;
    static int mBNum;
    bool mCollisionSoundFlag;
};

