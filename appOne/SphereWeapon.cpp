#include "SphereWeapon.h"
#include "window.h"
#include "Game.h"

SphereWeapon::SphereWeapon(class CharacterActor* owner, const VECTOR& pos, const VECTOR& dir)
	: ActorsWeapon(owner, pos, dir)
	, mLifeTime(0.0f)
{
}

int SphereWeapon::SetUp(const DATA& data)
{
	SetRadius(data.mRadius);
	SetHeight(data.mHeight);
	SetAdvSpeed(data.mAdvSpeed);
	SetPosition(mTmpPos);
	SetImageColor(data.mImageColor);
	SetTag(CharactersTag::EWaepon);

	SetDir(mTmpDir);

	if (mMoveFlag)
	{
		mMove = new MoveComponent(this);
		mMove->SetSpeed(GetAdvSpeed());
		mMove->SetDirection(GetDir());
	}

	mLifeTime = data.mMaxLifeTime;
	SetScale(VECTOR(data.mSize, data.mSize, data.mSize) * 2);

	return 1;
}


void SphereWeapon::UpdateActor()
{
	mLifeTime -= Data.mLifeTimeDecreaseSpeed * delta;

	//LifeTime‚ª‚È‚­‚È‚é‚©AOwner‚ª€‚ñ‚¾‚ç€‚Ê
	if (mLifeTime <= 0.0f || GetOwner()->GetState() != Actor::State::EActive)
	{
		SetState(Actor::State::EDead);
	}

};