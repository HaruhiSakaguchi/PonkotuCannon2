#pragma once
#include "Actor.h"
class PlayerFlag :
    public Actor
{
public:
    PlayerFlag(Game* game);
    int SetUp();
    void UpdateActor()override {};
    class TreeMeshComponent* GetMesh() { return mTc; }
private:
    class TreeMeshComponent* mTc;
};

