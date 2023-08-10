#pragma once
#include "ActorsWeapon.h"

class Arrow :
    public ActorsWeapon
{
public:
    Arrow(class CharacterActor* owner, const VECTOR& pos, const VECTOR& target);
    virtual int SetUp()override { return 1; };
    virtual void UpdateActor()override;
    void PlayHitSound();
    struct DATA
    {
        float mAdvSpeed = 0.0f;
        float mRadius = 0.0f;
        float mRotateSpeed = 0.0f;
        float mGravity = 0.0f;
        int mFlySound = -1;
        int mHitSound = -1;
        int mFlySoundVolumeOffset = 0;
        int mHitSoundVolumeOffset = 0;
    };
protected:
    DATA Data;
    class TreeMeshComponent* mTc;

};

