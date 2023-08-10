#include "Barricade.h"
#include "CollisionMapComponent.h"
#include "TreeMeshComponent.h"
#include "Game.h"
#include "window.h"
#include "UIPSideCharacterStatusClose.h"
#include <sstream>
#include "CapsuleComponent.h"

int Barricade::mBNum = 0;

Barricade::Barricade(class Game* game)
	:PSideCharacterActor(game)
	, mCollisionSoundFlag(false)
{
	Data = GetGame()->GetAllData()->barricadeData;
}

int Barricade::SetUp()
{
	SetHp(Data.mHp);
	SetMaxHp(Data.mHp);
	SetGravity(Data.mGravity);
	SetRadius(Data.mRadius);
	SetJumpFlag(Data.mJumpFlag);
	SetAdvSpeed(Data.mAdvSpeed);
	SetCapsulOffset(Data.mCapsuleOffset);
	SetImageColor(Data.mImageColor);
	SetInitMaxHp(GetMaxHp());
	SetTag(CharacterActor::CharactersTag::EBarricade);

	mMaxDamageInterval = Data.mMaxDamageInterval;
	mCapsule = new CapsuleComponent(this);
	mCapsule->AddNotCollisionTags((int)CharactersTag::EPHome);
	mCapsule->AddNotCollisionTags((int)CharactersTag::ESatellite);

	auto tree = new TreeMeshComponent(this);
	tree->SetTree("Barricade");
	SetNormalMesh(tree);

	new CollisionMapComponent(this);
	new UIPSideCharacterStatusClose(this);

	std::ostringstream oss;
	oss << "Barricade" << mBNum;
	SetName(oss.str().c_str());
	mBNum++;

	oss << "[Lv." << GetLevel() << "]" << "‚ðÝ’uB";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());

	setVolume(GetGame()->GetAllData()->itemCommonData.mDropSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + GetGame()->GetAllData()->itemCommonData.mDropSoundVolumeOffset);
	playSound(GetGame()->GetAllData()->itemCommonData.mDropSound);

	return 1;
}

void Barricade::UpdateActor()
{
	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}

	for (auto enemy : GetGame()->GetActorManager()->GetEnemies())
	{
		if (GetPosition().y > GetRadius() && mCapsule->OverlapActor(this, enemy) && enemy->GetHp() > 0)
		{
			enemy->Damage();
		}
	}

	if (GetPosition().y <= GetRadius() && !mCollisionSoundFlag)
	{
		setVolume(Data.mCollisionSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + Data.mCollisionSoundVolumeOffset);
		playSound(Data.mCollisionSound);
		mCollisionSoundFlag = true;
	}
}

void Barricade::Dead()
{
	PSideCharacterActor::Dead();
	std::ostringstream oss;
	oss << GetName().c_str() << "‚ª‰ó‚ê‚½";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
	SpawnParticle(GetGame(), GetPosition(), "BarricadeBarricade", 10);
}
