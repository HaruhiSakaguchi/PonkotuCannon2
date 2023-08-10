#pragma once
#include "Arrow.h"
class PlayerArrow :
    public Arrow
{
public:
    PlayerArrow(class CharacterActor* owner, const VECTOR& pos, const VECTOR& target);
    int SetUp()override;
    void UpdateActor()override;
};

