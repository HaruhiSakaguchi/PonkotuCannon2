#include "SatelliteWing.h"
#include "Game.h"
#include "window.h"
#include "TreeMeshComponent.h"
#include "UILog.h"
#include <sstream>

int SatelliteWing::mNum = 0;
int SatelliteWing::mGurdSound = -1;
int SatelliteWing::mClashSound = -1;

SatelliteWing::SatelliteWing(class Satellite* satellite)
	:ActorsWeapon(satellite, satellite->GetPosition(), VECTOR(0, 0, 0))
	, mAttackFlag(false)
	, mTc(nullptr)
{
	mOwnerName = GetOwner()->GetName();
	SetUp();
}

int SatelliteWing::SetUp()
{
	class Satellite* s = static_cast<class Satellite*>(mOwner);

	Data = GetGame()->GetAllData()->sWingData;
	Data.mId = mNum % 4;

	mNum++;

	mGurdSound = GetGame()->GetAllData()->mGurdSound;
	mClashSound = Data.mClashSound;

	SetRadius(Data.mRadius);
	SetHeight(Data.mHeight);
	SetAdvSpeed(Data.mAdvSpeed);
	SetPosition(s->GetPosition());
	SetImageColor(Data.mImageColor);

	auto tc = new TreeMeshComponent(this, false);
	auto dTree = new TreeMeshComponent(this, false);
	if (s->GetId() == 0)
	{
		tc->SetTree("SatelliteWing0");
		dTree->SetTree("SatelliteWing0Damage");
	}
	else
	{
		tc->SetTree("SatelliteWing1");
		dTree->SetTree("SatelliteWing1Damage");
	}

	SetNormalMesh(tc);
	SetDamageMesh(dTree);


	int hp = 0;
	if (Data.mId % 2 == 0)
	{
		hp = 2;
	}
	else
	{
		hp = 3;
	}

	SetHp(hp);
	setVolume(mGurdSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume());
	setVolume(mClashSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume());

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);

	std::ostringstream oss;
	oss << mOwnerName.c_str() << "Wing" << Data.mId;
	SetName(oss.str().c_str());
	return 1;
}

void SatelliteWing::UpdateActor()
{
	if (!mOwner || (mOwner && (mOwner->GetTag() != CharactersTag::ESatellite || mOwnerName != mOwner->GetName())))
	{
		SetState(State::EDead);
	}
	else
	{
		class Satellite* s = static_cast<class Satellite*>(mOwner);

		if (s->IsAttack())
		{
			mAttackFlag = true;
		}
		else
		{
			mAttackFlag = false;
		}

		SetDamageInterval(s->GetDamageInterval());


		float preOfsetZ = Data.mOffsetPos.z;
		float ofsetZ = 0.0f;

		if (GetDamageInterval() > 0)
		{
			ofsetZ = Data.mMaxOffsetZ;
		}
		else
		{
			ofsetZ = GetGame()->GetAllData()->sWingData.mOffsetPos.z;
		}

		Data.mOffsetPos.z = preOfsetZ + (ofsetZ - preOfsetZ) * Data.mChangeOffsetPosSpeed;

		Master.identity();

		if (GetHp() > 0 || GetOwner()->GetHp() > 0)
		{
			Master.mulTranslate(GetOwner()->GetPosition());
		}
		else
		{
			SetHp(0);
			SetJumpFlag(1);

			Master.mulTranslate(GetPosition());
		}

		if (GetOwner() && s->GetId() == 0)
		{
			if (Data.mId == 0)
			{
				Master.mulRotateX(-s->GetRotation().x);
			}
			else if (Data.mId == 3)
			{
				Master.mulRotateX(-s->GetRotation().x);
			}
		}

		Master.mulRotateY(GetRotation().y);

		Wing.identity();


		if (!mAttackFlag)
		{
			if (s->GetId() == 0)
			{
				if (Data.mId == 0)
				{
					Wing.mulTranslate(Data.mS0IdW0IdOffsetPos);
					Wing.mulRotateY(0);
					Wing.mulRotateZ(s->GetAnimAngle());
					Wing.mulScaling(Data.mWingScale2.x, Data.mWingScale2.y, Data.mWingScale2.z);
					SetRotationZ(s->GetAnimAngle());
					SetRotationX(s->GetRotation().x);
					SetScale(VECTOR(Data.mWingScale2.x, Data.mWingScale2.y, Data.mWingScale2.z));

				}
				else if (Data.mId == 1)
				{
					Wing.mulTranslate(Data.mS0IdW1IdOffsetPos);
					Wing.mulRotateY(0);
					Wing.mulRotateX(s->GetAnimAngle());
					Wing.mulScaling(Data.mWingScale1.x, Data.mWingScale1.y, Data.mWingScale1.z);
					SetRotationX(s->GetAnimAngle());
					SetScale(VECTOR(Data.mWingScale1.x, Data.mWingScale1.y, Data.mWingScale1.z));

				}
				else if (Data.mId == 2)
				{
					Wing.mulTranslate(Data.mS0IdW2IdOffsetPos);
					Wing.mulRotateY(0);
					Wing.mulRotateX(s->GetAnimAngle());
					Wing.mulScaling(Data.mWingScale1.x, Data.mWingScale1.y, Data.mWingScale1.z);
					SetRotationX(s->GetAnimAngle());
					SetScale(VECTOR(Data.mWingScale1.x, Data.mWingScale1.y, Data.mWingScale1.z));
				}
				else if (Data.mId == 3)
				{
					Wing.mulTranslate(Data.mS0IdW3IdOffsetPos);
					Wing.mulRotateY(0);
					Wing.mulRotateZ(-s->GetAnimAngle());
					SetRotationX(s->GetRotation().x);
					Wing.mulScaling(Data.mWingScale2.x, Data.mWingScale2.y, Data.mWingScale2.z);
					SetRotationZ(-s->GetAnimAngle());
					SetScale(VECTOR(Data.mWingScale2.x, Data.mWingScale2.y, Data.mWingScale2.z));

				}
			}
			else
			{
				Wing.mulRotateY(s->GetRotation().y + (Data.mId) * (3.1415926f / 2));
				Wing.mulTranslate(Data.mS1IdOffsetPos);
			}
		}
		else
		{
			if (s->GetId() == 0)
			{
				Wing.mulRotateY(s->GetRotation().y + (Data.mId) * (3.1415926f / 2));
				Wing.mulTranslate(Data.mS0IdAttackOffsetPos);
			}
			else
			{
				Wing.mulRotateY((Data.mId) * (3.1415926f / 2));
				if (Data.mId % 2 == 0)
				{
					Wing.mulTranslate(cosf(s->GetAnimAngle() * 10.0f), cosf(s->GetAnimAngle() * 10.0f), cosf(s->GetAnimAngle() * 10.0f - 1.0f) + sinf(s->GetAnimAngle() * 10.0f));
				}
				else
				{
					Wing.mulTranslate(-cosf(s->GetAnimAngle() * 10.0f), cosf(s->GetAnimAngle() * 10.0f), cosf(s->GetAnimAngle() * 10.0f - 1.0f) + sinf(s->GetAnimAngle() * 10.0f));
				}
				Wing.mulRotateX(GetRotation().y + 0.17f);
			}
		}

		if (s->GetId() == 0)
		{
			SetRotationY(s->GetRotation().y);
		}


		Wing.mulTranslate(Data.mOffsetPos);

		Wing = Master * Wing;

		float posY = GetPosition().y;
		if (GetJumpFlag() == 1)
		{
			posY += GetJumpVel() * delta;
			SetJumpVel(GetJumpVel() + GetGravity() * delta);
		}

		SetPosition(GetPosition().x, posY, GetPosition().z);

		VECTOR prePos = GetPosition();
		VECTOR pos = VECTOR(Wing._14, Wing._24, Wing._34);

		if (GetHp() <= 0)
		{
			SetPosition(prePos + (pos.y - prePos.y) * Data.mChangePosSpeed);
			if (GetPosition().y <= 0.0f)
			{
				SetState(Actor::State::EDead);
			}

		}
		else
		{
			SetPosition(pos);
		}

	}
}

void SatelliteWing::damage()
{
	SetHp(GetHp() - 1);
	if (GetHp() > 0)
	{
		PlayGurdSound();
	}
	else
	{
		setVolume(mClashSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + Data.mClashSoundVolumeOffset);
		playSound(mClashSound);
		SetGravity(Data.mGravity);
		SetJumpFlag(1);
		std::ostringstream oss;
		oss << GetName().c_str() << Data.mClashText;
		GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
	}
}

void SatelliteWing::Dead()
{
	for (int i = 0; i < 10; i++)
	{
		int num = rand();
		if (num % 2 == 0)
		{
			SpawnParticle(GetGame(), GetPosition(), "SatelliteWing0Square", 1);
		}
		else
		{
			SpawnParticle(GetGame(), GetPosition(), "SatelliteWing1Square", 1);
		}
	}
}
