#include "Game.h"
#include "COLLISION_MAP.h"
#include "SatelliteStates.h"
#include "Map.h"
#include "window.h"
#include "TreeMeshComponent.h"
#include "UILog.h"
#include "CollisionMapComponent.h"
#include "CharacterActor.h"
#include "PlayerHome.h"
#include "EnemyHome.h"
#include "CapsuleComponent.h"
#include <sstream>

int Satellite::mNum = 0;

Satellite::Satellite(class Game* game, const VECTOR& pos)
	: Enemy(game)
	, mState(nullptr)
	, mDeadFlag(false)
	, mRange(0.0f)
	, mIsAttack(false)
	, mCollision(nullptr)
	, mDeadPoint(0.0f, 0.0f, 0.0f)
	, mTargetPos(0.0f, 0.0f, 0.0f)
	, mId(0)
	, mElapsedTime(0.0f)
	, mAnimAngle(0.0f)
	, mAngleForPos(0.0f)
	, Master()
	, Target()
{

	SetInitPosition(pos);
	SetPosition(GetInitPosition());
	mState = new StateComponent(this);
	mState->RegisterState(new SatelliteNormal(mState));
	mState->RegisterState(new SatelliteGenerate(mState));
	mState->RegisterState(new SatelliteMove(mState));
	mState->RegisterState(new SatelliteRockOn(mState));
	mState->RegisterState(new SatelliteAttack(mState));
	mState->ChangeState("Generate");

}

int Satellite::SetUp()
{
	Data = GetGame()->GetAllData()->satelliteData;
	SetHeight(Data.mHeight);
	SetRadius(Data.mRadius);
	SetAdvSpeed(Data.mAdvSpeed);
	SetJumpFlag(0);
	SetRange(Data.mMaxRange);
	SetTag(CharacterActor::CharactersTag::ESatellite);
	SetGravity(0.0f);

	mAngleForPos = Data.mAngleForPos;
	mId = mNum % 2;
	int maxHp = 0;
	auto ntc = new TreeMeshComponent(this, false);

	if (mId == 0)
	{
		maxHp = Data.mMaxHp;
		ntc->SetTree("SatelliteBody0");
	}
	else
	{
		maxHp = Data.mMaxHp2;
		SetCapsulOffset(Data.mCapsulOffset);
		ntc->SetOffsetPos(Data.mMeshOffset);
		ntc->SetTree("SatelliteBody1");
	}

	SetNormalMesh(ntc);

	SetHp(maxHp);
	SetMaxHp(GetHp());
	SetInitMaxHp(GetMaxHp());

	mNum++;


	SetImageColor(Data.mImageColor);
	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
	mCapsule->SetSpandEp(VECTOR(0.0f, 0.0f, GetHeight()), VECTOR(0.0f, 0.0f, -GetHeight()));
	mCapsule->AddNotCollisionTags((int)CharactersTag::EPHome);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EEHome);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EBarricade);
	std::ostringstream oss;

	const char* type = nullptr;
	if (mId == 0)
	{
		type = "SatelliteA";
	}
	else
	{
		type = "SatelliteB";
	}

	oss << type << (int)(mNum / 2);

	SetName(oss.str().c_str());

	new SatelliteWing(this);
	new SatelliteWing(this);
	new SatelliteWing(this);
	new SatelliteWing(this);

	oss << "[Lv." << GetLevel() << "]が出現。";

	mCollision = new CollisionMapComponent(this);
	mCollision->NoCollisionMap();
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());

	return 0;
}

void Satellite::UpdateActor()
{
	if (GetPosition().y >= 10.0f)
	{
		SetHp(0);
	}

	if (GetHp() <= 0 && mDeadFlag == false)
	{
		mDeadFlag = true;
		SetJumpFlag(1);
		SetGravity(Data.mGravity);
		mDeadPoint = GetPosition();
	}

	Master.identity();
	Master.mulTranslate(GetPosition());
	Master.mulRotateY(GetRotation().y);

	if (mId == 1)
	{
		SetRotationX(3.1415926f / 2);
	}

	Target.identity();
	Target.mulTranslate(Data.mTargetOffsetPos);

	Target = Master * Target;

	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}

	if (mDeadFlag == true)
	{
		mState->ChangeState("Normal");
		if (GetPosition().y <= 0.0f)
		{
			SetState(Actor::State::EDead);
		}
	}
}

const VECTOR& Satellite::GetTargetPosition()
{
	mTargetPos = VECTOR(Target._14, Target._24, Target._34);
	return mTargetPos;
}

void Satellite::Damage(int damage)
{
	if (GetDamageInterval() <= 0)
	{
		SetHp(GetHp() - damage);
		PlayDamageSound();
		SetDamageInterval(Data.mMaxDamageInterval);
	}
	else
	{
		return;
	}

	if (mState->GetName() == "Attack")
	{
		mState->ChangeState("Normal");
		SetRotationX(0.0f);
		return;
	}
}

void Satellite::Dead()
{
	if (mId == 0)
	{
		SpawnParticle(GetGame(), GetPosition(), "SatelliteBody0Cylinder", 10);
		SpawnParticle(GetGame(), GetPosition(), "SatelliteWing0Square", 40);
	}
	else
	{
		SpawnParticle(GetGame(), GetPosition(), "SatelliteBody1Cylinder", 10);
		SpawnParticle(GetGame(), GetPosition(), "SatelliteWing1Square", 40);
	}


	PlayDeadSound();
	DropItems(mDeadPoint);

	std::ostringstream oss;
	oss << GetName().c_str() << "を倒した！！";

	int PlayerGetPoint = 0;
	if (mId == 0)
	{
		PlayerGetPoint = Data.mSatelliteAGetPoint + GetLevel() * Data.mSatelliteEveryLvUpPoint;
		GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
	}
	else
	{
		PlayerGetPoint = Data.mSatelliteBGetPoint + GetLevel() * Data.mSatelliteEveryLvUpPoint;
		GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
	}

	if (GetGame()->GetActorManager()->GetPHome())
	{
		GetGame()->GetActorManager()->GetPHome()->SetBattlePoints(GetGame()->GetActorManager()->GetPHome()->GetBattlePoints() + PlayerGetPoint);
		if (GetGame()->GetActorManager()->GetPHome()->GetMaxBattlePoints() < GetGame()->GetActorManager()->GetPHome()->GetBattlePoints())
		{
			GetGame()->GetActorManager()->GetPHome()->SetBattlePoints(GetGame()->GetActorManager()->GetPHome()->GetMaxBattlePoints());
		}
	}

	if (GetGame()->GetActorManager()->GetEHome())
	{
		if (GetGame()->GetActorManager()->GetEHome()->GetLevel() > GetGame()->GetActorManager()->GetEHome()->GetSatelliteGenerateLevel() && GetGame()->GetActorManager()->GetEHome()->GetBattlePoints() >= Data.mGenerateSatelliteLvLvUpPoint)
		{
			GetGame()->GetActorManager()->GetEHome()->SetBattlePoints(GetGame()->GetActorManager()->GetEHome()->GetBattlePoints() - Data.mGenerateSatelliteLvLvUpPoint);
			GetGame()->GetActorManager()->GetEHome()->SetSatelliteGenerateLevel(GetGame()->GetActorManager()->GetEHome()->GetSatelliteGenerateLevel() + 1);
		}
	}
}
