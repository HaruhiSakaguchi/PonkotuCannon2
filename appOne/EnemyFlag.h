#pragma once
#include "Actor.h"
class EnemyFlag :
	public Actor
{
public:
	EnemyFlag(Game* game);
	int SetUp();
	void UpdateActor()override;
	class TreeMeshComponent* GetMesh() { return mTc; }
private:
	class TreeMeshComponent* mTc;
};

