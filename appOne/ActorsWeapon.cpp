#include "ActorsWeapon.h"
#include "Game.h"

ActorsWeapon::ActorsWeapon(class CharacterActor* owner, const VECTOR& pos, const VECTOR& dir)
	: CharacterActor(owner->GetGame())
	, mOwner(owner)
	, mTmpPos(pos)
	, mTmpDir(dir)
	, mDir(dir)
	, mMove(nullptr)
	, mMoveFlag(true)
	, Master()
{
	GetGame()->GetActorManager()->AddWeapons(this);
	SetCategory(Actor::ActorsCategory::EWeapon);
}

ActorsWeapon::~ActorsWeapon()
{
	GetGame()->GetActorManager()->RemoveWeapons(this);
}

void ActorsWeapon::damage()
{
	SetState(State::EDead);
}