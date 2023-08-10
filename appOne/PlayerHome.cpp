#include "PlayerHome.h"
#include "TreeMeshComponent.h"
#include "PlayerFlag.h"
#include "HpGaugeSpriteComponent.h"
#include "Game.h"
#include "window.h"
#include "EnemyHome.h"
#include "UIPSideCharacterStatusClose.h"
#include "UIPlayerHome.h"
#include "input.h"
#include "CapsuleComponent.h"
#include "PlayerArrow.h"
#include "EnemyArrow.h"
#include "rand.h"

PlayerHome::PlayerHome(class Game* game, const VECTOR& pos)
	: PSideCharacterActor(game)
	, mTc(nullptr)
	, mFlag1(nullptr)
	, mFlag2(nullptr)
	, mDore(nullptr)
	, mCurMyTpIdx(0)
	, mGenerateFlag(1)
	, mBattlePoints(0)
	, mMaxBattlePoints(0)
	, mFirstGenerateBarricadeFlag(0)
	, mFirstGenerateCannonFlag(0)

{
	Data = GetGame()->GetAllData()->pHomeData;
	SetInitPosition(pos);
	SetPosition(pos);
	SetUp();
	GetGame()->GetActorManager()->SetPHome(this);
	mCapsule = new CapsuleComponent(this);
}

PlayerHome::~PlayerHome()
{
	GetGame()->GetActorManager()->SetPHome(nullptr);
}

int PlayerHome::SetUp()
{
	mTc = new TreeMeshComponent(this);
	mTc->SetTree("Home");
	SetNormalMesh(mTc);
	mDore = new Dore(GetGame());
	mFlag1 = new PlayerFlag(GetGame());
	mFlag2 = new PlayerFlag(GetGame());
	SetTag(CharactersTag::EPHome);
	SetHp(Data.mMaxHp);
	SetMaxHp(Data.mMaxHp);
	SetInitMaxHp(Data.mMaxHp);

	mDore->SetRotationX(0.0f);
	mDore->SetRotationY(-3.1415926f);
	mDore->SetIsRotate(true);
	mDore->Open();
	mDore->SetCloseEvent([this]() { mGenerateFlag = 0; GetGame()->GetCameraManager()->ChangeCamera("NormalCamera"); });

	mDore->SetPosition(GetPosition() + Data.mDoreOffset);
	mFlag1->SetPosition(GetPosition() + Data.mFlag1Offset);
	mFlag2->SetPosition(GetPosition() + Data.mFlag2Offset);

	mMaxDamageInterval = Data.mMaxDamageInterval;

	mProps.emplace_back(mDore);
	mProps.emplace_back(mFlag1);
	mProps.emplace_back(mFlag2);

	SetRadius(Data.mRadius);
	SetHeight(Data.mHeight);
	SetName("PlayerHome");

	new HpGaugeSpriteComponent(this, Data.mHpGaugeOffset);
	new UIPlayerHome(this);
	mMaxBattlePoints = Data.mInitMaxBattlePoint;
	mHomeTargetPoint = GetInitPosition();

	SetImageColor(Data.mImageColor);
	return 1;
}

void PlayerHome::UpdateActor()
{
	for (int i = 0; i < 4; i++)
	{
		mHomeTargetPoints[i] = GetPosition() + Data.mHomeTargetPointOffsets[i];
	}

	if (GetGame()->GetActorManager()->GetEHome())
	{
		VECTOR PEHomeCenterPos = (GetPosition() + GetGame()->GetActorManager()->GetEHome()->GetPosition()) / 2;

		for (int i = 0; i < 4; i++)
		{
			mFieldTargetPoints[i] = PEHomeCenterPos + Data.mFieldTargetPointOffsets[i];
		}
	}

	mMyTargetPoints[0] = GetInitPosition();
	mMyTargetPoints[1] = GetInitPosition() + (VECTOR(0.0f, 0.0f, (GetGame()->GetActorManager()->GetStage()->GetStageMaxZ() + GetGame()->GetActorManager()->GetStage()->GetStageMinZ())) / 4.0f);
	mMyTargetPoints[2] = GetInitPosition() + (VECTOR(0.0f, 0.0f, (GetGame()->GetActorManager()->GetStage()->GetStageMaxZ() + GetGame()->GetActorManager()->GetStage()->GetStageMinZ())) / 2.0f);


	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}

	for (auto enemy : GetGame()->GetActorManager()->GetEnemies())
	{
		if (enemy->GetHp() > 0)
		{
			if (mCapsule->OverlapActor(this, enemy) && !mMoveCompleteFlag)
			{
				enemy->Damage(1 + (int)(GetLevel() / 2));
			}
		}
	}

	mMoveCompleteFlag = GoToTargetPoint(mHomeTargetPoint);

	if (mMoveCompleteFlag == 1 && mGenerateFlag == 1)
	{
		mDore->SetIsRotate(true);
	}

	int cnt = 0;
	for (auto Actor : GetGame()->GetActorManager()->GetPSide())
	{
		if (Actor != this && CollisionCircle(GetRadius(), Actor->GetRadius(), GetPosition(), Actor->GetPosition()))
		{
			if (Actor->GetTag() == CharacterActor::CharactersTag::ECannon)
			{
				if (static_cast<class Cannon*>(Actor)->GetStateCompoState()->GetName() != "Generate")
				{
					continue;
				}
			}
			else
			{
				continue;
			}

			cnt++;
		}
	}

	if (mGenerateFlag == 1 && cnt == 0)
	{
		mDore->Close();
	}

	mMaxBattlePoints = 500 * (GetLevel() + 1);

	if (mBattlePoints < mMaxBattlePoints)
	{
		mBattlePoints++;
	}
	if (mBattlePoints < 0)
	{
		mBattlePoints = 0;
	}

	if (GetDamageInterval() > 0)
	{
		mDore->GetMesh()->SetDrawFlag(false);
		mFlag1->GetMesh()->SetDrawFlag(false);
		mFlag2->GetMesh()->SetDrawFlag(false);
	}
	else
	{
		mDore->GetMesh()->SetDrawFlag(true);
		mFlag1->GetMesh()->SetDrawFlag(true);
		mFlag2->GetMesh()->SetDrawFlag(true);
	}
}

void PlayerHome::Dead()
{
	PSideCharacterActor::Dead();

	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText("PlayerHome‚ª‰ó‚ê‚½");
	SpawnParticle(GetGame(), GetPosition(), "HomeHouse", 20);
	SpawnParticle(GetGame(), GetPosition(), "DoreDore", 20);
	SpawnParticle(GetGame(), GetPosition(), "PlayerFlagFlag", 40);

	for (auto prop : mProps)
	{
		prop->SetState(State::EDead);
	}

	GetGame()->GetCameraManager()->ChangeCamera("NormalCamera");
}

int PlayerHome::GoToTargetPoint(const VECTOR& pos)
{
	VECTOR dir = pos - GetPosition();
	dir.normalize();

	if (CollisionCircle(0.5f, 0.5f, GetPosition(), pos))
	{
		if (mMoveCompleteFlag == 0 && mGenerateFlag == 0)
		{
			GetGame()->GetCameraManager()->ChangeCamera("NormalCamera");
		}
		return 1;
	}
	else
	{
		SetPosition(GetPosition() + dir * delta * 6.0f);
		for (auto prop : mProps)
		{
			prop->SetPosition(prop->GetPosition() + dir * delta * 6.0f);
		}

		if (dir.z < 0.0f)
		{
			for (auto pSide : GetGame()->GetActorManager()->GetPSide())
			{
				if (InPlayerArea(pSide->GetPosition()))
				{
					bool moveFlag = false;
					if (pSide->GetTag() == CharacterActor::CharactersTag::ECannon && static_cast<class Cannon*>(pSide)->GetStateCompoState()->GetName() != "Generate")
					{
						moveFlag = true;
					}
					else if (pSide->GetTag() == CharacterActor::CharactersTag::EBarricade && pSide->GetPosition().y <= 0.0f)
					{
						moveFlag = true;
					}


					if (moveFlag)
					{
						pSide->SetPosition(pSide->GetPosition() + dir * delta * 6.0f);
					}
				}
			}
		}
		return 0;
	}
}

void PlayerHome::CreateHomeArea()
{
	for (int i = 0; i < 36; i++)
	{
		auto flag = new PlayerFlag(GetGame());
		flag->SetPosition(GetPosition().x + sinf(i * 3.1415926f * 2 / 36.0f) * 7.0f, 0.0f, GetPosition().z + cosf(i * 3.1415926f * 2 / 36.0f) * 7.0f);
		flag->SetScale(VECTOR(0.5f, 0.5f, 0.5f));
		mProps.emplace_back(flag);
	}
}

bool PlayerHome::InPlayerArea(const VECTOR& pos)
{
	float distX = pos.x - GetPosition().x;
	float distZ = pos.z - GetPosition().z;

	float dist = sqrtf(distX * distX + distZ * distZ);

	bool in = (dist <= 7.0f);
	return in;
}
