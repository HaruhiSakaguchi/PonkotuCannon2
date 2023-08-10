#include "ItemObject.h"
#include "Game.h"
#include "window.h"
#include "Cannon.h"
#include "COLLISION_MAP.h"
#include "BatchMeshComponent.h"
#include <sstream>
#include "UILog.h"
#include "CollisionMapComponent.h"
#include "PlayerHome.h"

ItemObject::ItemObject(Game* game)
	: CharacterActor(game)
	, mTc(nullptr)
	, mOwner(nullptr)
	, mTime(0.0f)
	, mIsSpawnParticle(false)
	, mBeforeTime(0)
	, mBatchName(nullptr)
{
	GetGame()->GetActorManager()->AddItems(this);
	mStart = std::chrono::system_clock::now();

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
}

ItemObject::~ItemObject()
{
	GetGame()->GetActorManager()->RemoveItems(this);
}

int ItemObject::SetUp()
{
	cData = GetGame()->GetAllData()->itemCommonData;
	SetRadius(cData.mRadius);
	SetGravity(cData.mGravity);
	SetJumpFlag(cData.mJumpFlag);
	SetJumpVel(cData.mJumpVelocity);
	SetAdvSpeed(cData.mAdvSpeed);
	SetHp(cData.mHp);
	SetCapsulOffset(cData.mCapsulOffset);
	SetCategory(Actor::ActorsCategory::EItem);
	cData.mLifeTime = cData.mMaxLifeTime;
	setVolume(cData.mDropSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + cData.mDropSoundVolumeOffset);
	playSound(cData.mDropSound);
	SetScale(VECTOR(cData.mRadius, cData.mRadius, cData.mRadius) * 4.0f);
	SetName(GetName());
	new CollisionMapComponent(this);

	return 0;
}

void ItemObject::UpdateActor()
{
	if (mTime < cData.mMaxLifeTime)
	{
		auto end = std::chrono::system_clock::now();
		auto dur = end - mStart;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		float time = msec / 1000.0f;
		mTime = time;
	}

	if ((int)mTime % 3 == 0 && (int)mTime != mBeforeTime)
	{
		mIsSpawnParticle = true;
	}

	if (mIsSpawnParticle)
	{
		SpawnParticle(GetGame(), GetPosition() + GetCapsulOffset(), mBatchName, 5, 1.0f);
		mIsSpawnParticle = false;
		mBeforeTime = (int)mTime;
	}

	for (auto pSide : GetGame()->GetActorManager()->GetPSide())
	{
		if (pSide->GetState() == Actor::State::EActive && mCapsule->OverlapActor(this, pSide))
		{
			mOwner = pSide;
			if (mOwner)
			{
				std::ostringstream oss;
				oss << GetName() << "アイテムを使用。";
				GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
				if (update())
				{
					SetHp(GetHp() - 1);
				}
			}

			if (GetHp() <= 0)
			{
				SetState(Actor::State::EDead);
			}
		}
	}

	if (mTime > cData.mMaxLifeTime * 0.7f)
	{
		if ((int)mTime % 2 == 0)
		{
			SetImageColor(iData.mColor);
			SetDamageInterval(0.0f);
		}
		else
		{
			SetImageColor(COLOR(iData.mColor.r, iData.mColor.g, iData.mColor.b, 128));
			SetDamageInterval(1.0f);
		}
	}

	if (mTime >= cData.mMaxLifeTime || GetPosition().y < -5.0f)
	{
		SetState(Actor::State::EDead);
		std::ostringstream oss;
		oss << GetName() << "アイテムが消滅。";
		GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	}
}

void ItemObject::CreateMesh(const char* normalMeshName, const char* damageMeshName)
{
	if (normalMeshName)
	{
		auto nm = new BatchMeshComponent(this, false);
		nm->SetOffsetPos(GetCapsulOffset());
		nm->SetBatch(normalMeshName);
		SetNormalMesh(nm);
	}
	if (damageMeshName)
	{
		auto dm = new BatchMeshComponent(this, false);
		dm->SetBatch(damageMeshName);
		dm->SetOffsetPos(GetCapsulOffset());
		SetDamageMesh(dm);
	}
}

void ItemObject::LvUpAnnounce(class ItemEffect* item)
{
	std::ostringstream oss;
	oss << item->GetOwner()->GetName().c_str() << "の" << item->GetName().c_str() << "がレベルアップ。[Lv." << item->GetLevel() << "]";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
}

void ItemObject::ItemEffectLvUp(ItemEffect* item)
{
	if (item->GetLevel() != item->GetMaxLevel())
	{
		item->SetLevel(item->GetLevel() + 1);
		if (GetGame()->GetState() == Game::GameState::EGameplay)
		{
			LvUpAnnounce(item);
		}
	}
}

void ItemObject::PlayUseSound1(individualDATA& data)
{
	setVolume(data.mSound1, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + data.mSound1VolumeOffset);
	playSound(data.mSound1);
}

void ItemObject::PlayUseSound2(individualDATA& data)
{
	setVolume(data.mSound2, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + data.mSound2VolumeOffset);
	playSound(data.mSound2);
}

