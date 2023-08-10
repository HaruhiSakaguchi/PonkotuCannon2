#include "EnemyFlag.h"
#include "TreeMeshComponent.h"

EnemyFlag::EnemyFlag(Game* game)
	: Actor(game)
{
	SetUp();
}
int EnemyFlag::SetUp()
{
	mTc = new TreeMeshComponent(this);
	mTc->SetTree("EnemyFlag");
	return 1;
}

void EnemyFlag::UpdateActor()
{
}