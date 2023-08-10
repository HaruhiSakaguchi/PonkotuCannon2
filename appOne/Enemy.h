#pragma once
#include "CharacterActor.h"

class Enemy :
    public CharacterActor
{
public:
    Enemy(class Game* game);
    ~Enemy();
};

