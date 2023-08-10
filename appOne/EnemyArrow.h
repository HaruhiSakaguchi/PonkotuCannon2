#pragma once
#include "Arrow.h"
class EnemyArrow :
    public Arrow
{
public:
    EnemyArrow(class CharacterActor* owner, const VECTOR& pos, const VECTOR& target);
    int SetUp()override;
    void UpdateActor()override;
};

