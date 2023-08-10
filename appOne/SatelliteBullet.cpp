#include "SatelliteBullet.h"
#include "Game.h"
#include "BatchMeshComponent.h"

SatelliteBullet::SatelliteBullet(class Satellite* satellite, const VECTOR& pos, const VECTOR& dir)
	:SphereWeapon(satellite, pos, dir)
	, mCnt(0)
	, mDefDir(0.0f, 0.0f, 0.0f)
{
	Data = GetGame()->GetAllData()->sBulletData;
	iData = GetGame()->GetAllData()->sBulletIData;

	SetUp(Data);
	mDefDir = dir;
	BatchMeshComponent* bc = new BatchMeshComponent(this);
	bc->SetBatch("SatelliteBulletSphere");

	if (GetGame()->GetState() == Game::GameState::EGameplay && GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		setVolume(iData.mLaunchSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + iData.mLaunchSoundVolumeOffset);
		playSound(iData.mLaunchSound);
	}

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
}

void SatelliteBullet::UpdateActor()
{
	if (mOwner->GetHp() > 0)
	{
		if (++mCnt >= iData.mChangeFlame)
		{
			VECTOR mTarget = VECTOR(0.0f, 0.0f, 0.0f);

			if (static_cast<Satellite*>(mOwner)->GetId() == 1)
			{

				for (auto pSide : GetGame()->GetActorManager()->GetPSide())
				{
					if (pSide->GetHp() != 0)
					{
						VECTOR target = pSide->GetPosition();
						target.y += pSide->GetCapsulOffset().y;
						float distx = target.x - GetPosition().x;
						float disty = target.y - (GetPosition().y);
						float distz = target.z - GetPosition().z;
						float dist = sqrtf(distx * distx + disty * disty + distz * distz);

						float tdistx = mTarget.x - GetPosition().x;
						float tdisty = mTarget.y - (GetPosition().y);
						float tdistz = mTarget.z - GetPosition().z;
						float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

						if (mTarget.x == 0.0f && mTarget.y == 0.0f && mTarget.z == 0.0f)
						{
							mTarget = pSide->GetPosition() + pSide->GetCapsulOffset();
						}
						else if (dist <= tdist)
						{
							mTarget = pSide->GetPosition() + pSide->GetCapsulOffset();
						}
					}
				}

				SetDir((mTarget - GetPosition()).normalize());
			}

			mMove->SetSpeed(GetAdvSpeed() * 2.0f);
			mMove->SetDirection(GetDir());
		}
		else if (static_cast<class Satellite*>(mOwner)->GetId() == 1)
		{
			mMove->SetSpeed(0.0f);
		}

	}
	else
	{
		mMove->SetDirection(VECTOR(0.0f, -1.0f, 0.0f));
		mMove->SetSpeed(GetAdvSpeed() * 2.0f);
	}

	for (auto pSide : GetGame()->GetActorManager()->GetPSide())
	{
		if (mCapsule->OverlapActor(this, pSide))
		{
			SetState(Actor::State::EDead);
			if (GetGame()->GetState() == Game::GameState::EGameplay && GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
			{
				setVolume(iData.mImpactSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + iData.mImpactSoundVolumeOffset);
				playSound(iData.mImpactSound);
			}
			pSide->Damage(Data.mDamage);
		}
	}

	if (!GetOnMapFlag())
	{
		SetState(Actor::State::EDead);
	}

	SphereWeapon::UpdateActor();
}

