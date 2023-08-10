#include "Arrow.h"
#include "TreeMeshComponent.h"
#include "window.h"
#include "CapsuleComponent.h"
#include "Game.h"
#include "CollisionMapComponent.h"
#include "sound.h"

Arrow::Arrow(class CharacterActor* owner, const VECTOR& pos, const VECTOR& target)
	: ActorsWeapon(owner, pos, VECTOR(target - pos))
	, mTc(nullptr)
{
	Data = GetGame()->GetAllData()->arrowData;

	SetPosition(pos);
	SetDir(target - pos);
	int flame = (int)GetDir().magSq() / 2;

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
	SetRadius(Data.mRadius);

	auto colllision = new CollisionMapComponent(this);
	colllision->NoCollisionMap();

	SetJumpFlag(1);
	SetGravity(Data.mGravity / flame * delta * 60.0f);

	setVolume(Data.mFlySound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + Data.mFlySoundVolumeOffset);
	playSound(Data.mFlySound);

	SetImageColor(mOwner->GetImageColor());

}

void Arrow::UpdateActor()
{
	mTc->SetDrawFlag(true);

	VECTOR angle = GetRotation();
	angle.x = -3.1415926f / 2.0f;

	VECTOR dir = GetDir();
	dir.normalize();

	rotate(&angle, dir, Data.mRotateSpeed);
	SetRotation(angle);

	SetPosition(GetPosition() + dir * delta * Data.mAdvSpeed);

	for (auto chara : GetGame()->GetActorManager()->GetWeapons())
	{
		if (chara != this && mOwner != chara->GetOwner() && chara->GetCapsule() && mCapsule->OverlapActor(this, chara) && chara->GetHp() > 0)
		{
			chara->damage();
			SetState(Actor::State::EDead);
			PlayHitSound();
		}
	}

	if (!PositionOnMap(GetPosition(), GetRadius()) || GetPosition().y <= 0.0f)
	{
		SetState(Actor::State::EDead);
	}

}

void Arrow::PlayHitSound()
{
	setVolume(Data.mHitSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + Data.mHitSoundVolumeOffset);
	playSound(Data.mHitSound);
}
