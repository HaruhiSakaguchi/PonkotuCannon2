#include "Game.h"
#include "Tama.h"
#include "window.h"
#include "TamaStates.h"
#include "StateComponent.h"
#include "BatchMeshComponent.h"
#include "TamaBlackEye.h"
#include "CollisionMapComponent.h"
#include "CapsuleComponent.h"
#include "SEGMENT.h"
#include <sstream>

int Tama::mNum = 0;

Tama::Tama(Game* game, const VECTOR& pos)
	: Enemy(game)
	, mState(nullptr)
	, mScale(1.0f)
	, mTc(nullptr)
	, mEye(nullptr)
	, mLine(nullptr)
{
	mState = new StateComponent(this);
	mState->RegisterState(new TamaGenerate(mState));
	mState->RegisterState(new TamaWait(mState));
	mState->RegisterState(new TamaMove(mState));
	mState->RegisterState(new TamaRockOn(mState));
	mState->RegisterState(new TamaSeache(mState));
	mState->RegisterState(new TamaCharge(mState));
	mState->RegisterState(new TamaAttack(mState));
	mState->ChangeState("Generate");
	SetInitPosition(pos);
}

Tama::~Tama()
{
	delete mLine;
}

int Tama::SetUp()
{
	Data = GetGame()->GetAllData()->tamaData;

	SetHeight(Data.mHeight);
	SetRadius(Data.mRadius);
	SetHp(Data.mMaxHp);
	SetMaxHp(GetHp());
	SetInitMaxHp(GetMaxHp());
	SetAdvSpeed(Data.mAdvSpeed);
	SetJumpVel(Data.mJumpVelocity);
	SetJumpFlag(Data.mJumpFlag);
	SetImageColor(Data.mImageColor);
	SetGravity(Data.mGravity);
	SetCapsulOffset(Data.mCapsulOffset);
	SetTag(CharacterActor::CharactersTag::ETama);

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EBarricade);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EPHome);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EEHome);


	auto nb = new BatchMeshComponent(this);
	nb->SetBatch("TamaSphere");
	nb->SetOffsetPos(GetCapsulOffset());
	SetNormalMesh(nb);
	auto db = new BatchMeshComponent(this, false);
	db->SetBatch("TamaDamageSphere");
	db->SetOffsetPos(GetCapsulOffset());
	SetDamageMesh(db);

	mEye = new TamaBlackEye(this);
	new CollisionMapComponent(this);


	std::ostringstream oss;

	oss << "Tama" << mNum;

	SetName(oss.str().c_str());

	mNum++;
	mLine = new SEGMENT(Data.mSightSp, Data.mSightEp);

	oss << "[Lv." << GetLevel() << "]が出現。";

	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	return 0;
}

void Tama::UpdateActor()
{
	SetScale(VECTOR(mScale, mScale, mScale));

	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}

	if (GetHp() <= 0)
	{
		mScale -= 0.01f;
		SetRotationY(GetRotation().y + 0.17f);
		mState->ChangeState("Wait");

		if (mScale <= 0.0f)
		{
			SetState(Actor::State::EDead);
		}
	}
}

void Tama::Damage(int damage)
{
	if (GetDamageInterval() <= 0.0f)
	{
		SetHp(GetHp() - damage);
		SetDamageInterval(Data.mMaxDamageInterval);
		PlayDamageSound();
	}
	else
	{
		return;
	}
}

void Tama::FallOption()
{
	std::stringstream oss;
	oss << GetName().c_str() << "が奈落に落ちた。";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	SetState(State::EDead);
}

void Tama::Dead()
{
	SpawnParticle(GetGame(), GetPosition(), "TamaSphere", 10);
	SpawnParticle(GetGame(), GetPosition(), "TamaBlackEyeCylinder", 10);

	PlayDeadSound();
	DropItems(GetPosition());

	std::stringstream oss;
	oss << GetName().c_str() << "を倒した！！";

	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	if (GetGame()->GetActorManager()->GetPHome())
	{
		GetGame()->GetActorManager()->GetPHome()->SetBattlePoints(GetGame()->GetActorManager()->GetPHome()->GetBattlePoints() + 100 + GetLevel() * 50);
		if (GetGame()->GetActorManager()->GetPHome()->GetMaxBattlePoints() < GetGame()->GetActorManager()->GetPHome()->GetBattlePoints())
		{
			GetGame()->GetActorManager()->GetPHome()->SetBattlePoints(GetGame()->GetActorManager()->GetPHome()->GetMaxBattlePoints());
		}
	}

	if (GetGame()->GetActorManager()->GetEHome())
	{
		if (GetGame()->GetActorManager()->GetEHome()->GetLevel() > GetGame()->GetActorManager()->GetEHome()->GetTamaGenerateLevel() && GetGame()->GetActorManager()->GetEHome()->GetBattlePoints() >= 100)
		{
			GetGame()->GetActorManager()->GetEHome()->SetBattlePoints(GetGame()->GetActorManager()->GetEHome()->GetBattlePoints() - 100);
			GetGame()->GetActorManager()->GetEHome()->SetTamaGenerateLevel(GetGame()->GetActorManager()->GetEHome()->GetTamaGenerateLevel() + 1);
		}
	}
}

