#pragma once
#include "Component.h"

class CollisionMapComponent :
    public Component
{
public:
    CollisionMapComponent(Actor* owner);
    void Update()override;
    void NoCollisionMap() { mIsMapCollision = false; }
private:
    bool mIsMapCollision;
};

