#include "Items.h"
#include "Game.h"
#include "BatchMeshComponent.h"
#include "UILog.h"
#include <sstream>

Recovery::Recovery(class Game* game)
	:ItemObject(game)
{
	iData = GetGame()->GetAllData()->recoverData;
	SetImageColor(iData.mColor);
	SetUp();

	mBatchName = "RecoverSphere";
	CreateMesh(mBatchName, "RecoverTranSphere");
}

bool Recovery::update()
{
	auto p = static_cast<class PSideCharacterActor*>(mOwner);

	if (p->GetHp() < p->GetMaxHp())
	{
		new RecoveryEffect(p);
		PlayUseSound1(iData);
	}
	else
	{
		if (mOwner->GetTag() == CharacterActor::CharactersTag::ECannon)
		{
			static_cast<class Cannon*>(p)->AddItemNum(iData.mNum);
			PlayUseSound2(iData);
			std::ostringstream oss;
			oss << GetName() << "アイテムをストック。";
			GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
		}
	}

	return true;
}

RecoveryEffect::RecoveryEffect(class PSideCharacterActor* owner)
	: ItemEffect(owner)
{
	Data = owner->GetGame()->GetAllData()->recoverEffectData;
	SetHp(Data.mMaxHp);
	SetMaxHp(GetHp());
	SetName(Data.mName.c_str());
	SetMaxLevel(Data.mMaxLevel);

	if (owner->GetHp() < owner->GetMaxHp())
	{
		owner->SetHp(owner->GetHp() + mRecoveryHp);
	}
	mMeshName = "RecoverSphere";

	mOwner->SpawnParticle(GetGame(), mOwner->GetPosition() + mOwner->GetCapsulOffset(), mMeshName, 10);
}

SpeedUp::SpeedUp(class Game* game)
	: ItemObject(game)
{
	iData = GetGame()->GetAllData()->speedData;
	SetImageColor(iData.mColor);
	SetUp();

	mBatchName = "SpeedSphere";
	CreateMesh(mBatchName, "SpeedTranSphere");
}

bool SpeedUp::update()
{
	auto c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		if (!c->GetSpeed())
		{
			new SpeedUpEffect(c);
			c->GetSpeed()->SetInterval(GetGame()->GetAllData()->speedEffectData.mInterval);
			c->GetSpeed()->SetTime(c->GetSpeed()->GetInterval());
			c->GetSpeed()->SetColor(iData.mColor);
		}
		else
		{
			ItemEffectLvUp(c->GetSpeed());
			c->GetSpeed()->TimeReset();
		}
	}

	PlayUseSound1(iData);

	return true;

}

SpeedUpEffect::SpeedUpEffect(class PSideCharacterActor* owner)
	: ItemEffect(owner)
{
	owner->SetSpeed(this);
	Data = owner->GetGame()->GetAllData()->speedEffectData;
	mMeshName = "SpeedSphere";
	SetHp(Data.mMaxHp);
	SetMaxHp(GetHp());
	SetName(Data.mName.c_str());
	SetMaxLevel(Data.mMaxLevel);
}

void SpeedUpEffect::UpdateActor()
{
	ItemEffect::UpdateActor();
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c && c->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		c->SetAdvSpeed(GetGame()->GetAllData()->cannonData.mAdvSpeed + Data.mLevel * GetGame()->GetAllData()->cannonData.mAdvSpeed * mSpeedUpRate);
	}
}

void SpeedUpEffect::Dead()
{
	ItemEffect::Dead();
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c && c->GetState() == Actor::State::EActive && GetGame()->GetState() == Game::GameState::EGameplay)
	{
		c->SetAdvSpeed(GetGame()->GetAllData()->cannonData.mAdvSpeed);
		c->SetSpeed(nullptr);
	}

}

PowerUp::PowerUp(class Game* game)
	:ItemObject(game)
{
	iData = GetGame()->GetAllData()->powerData;
	SetImageColor(iData.mColor);
	SetUp();

	mBatchName = "PowerSphere";
	CreateMesh(mBatchName, "PowerTranSphere");

}

bool PowerUp::update()
{
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		if (!c->GetPower())
		{
			new PowerUpEffect(c);
			c->GetPower()->SetInterval(GetGame()->GetAllData()->powerEffectData.mInterval);
			c->GetPower()->SetTime(c->GetPower()->GetInterval());
			c->GetPower()->SetColor(iData.mColor);
		}
		else
		{
			ItemEffectLvUp(c->GetPower());
			c->GetPower()->TimeReset();
		}
	}

	PlayUseSound1(iData);

	return true;
}

PowerUpEffect::PowerUpEffect(class PSideCharacterActor* owner)
	:ItemEffect(owner)
{
	owner->SetPower(this);
	Data = owner->GetGame()->GetAllData()->powerEffectData;
	SetHp(Data.mMaxHp);
	mMeshName = "PowerSphere";
	SetMaxHp(GetHp());
	SetName(Data.mName.c_str());
	SetMaxLevel(Data.mMaxLevel);
}

void PowerUpEffect::UpdateActor()
{
	ItemEffect::UpdateActor();
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c)
	{
		c->SetDamage(Data.mLevel + 1);
	}
}

void PowerUpEffect::Dead()
{
	ItemEffect::Dead();
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);
	if (c->GetState() == Actor::State::EActive && GetGame()->GetState() == Game::GameState::EGameplay)
	{
		c->SetDamage(1);
		c->SetPower(nullptr);
	}
}

RapidFire::RapidFire(class Game* game)
	:ItemObject(game)
{
	iData = GetGame()->GetAllData()->rapidData;
	SetImageColor(iData.mColor);
	SetUp();

	mBatchName = "RapidSphere";
	CreateMesh(mBatchName, "RapidTranSphere");
	SetMaxHp(GetHp());
}

bool RapidFire::update()
{
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);

	if (c->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		if (!c->GetRapid())
		{
			new RapidFireEffect(c);
			c->GetRapid()->SetInterval(GetGame()->GetAllData()->rapidEffectData.mInterval);
			c->GetRapid()->SetTime(c->GetRapid()->GetInterval());
			c->GetRapid()->SetColor(iData.mColor);
		}
		else
		{
			ItemEffectLvUp(c->GetRapid());
			c->GetRapid()->TimeReset();
		}
	}

	PlayUseSound1(iData);

	return true;

}

RapidFireEffect::RapidFireEffect(class PSideCharacterActor* owner)
	: ItemEffect(owner)
{
	owner->SetRapid(this);
	Data = owner->GetGame()->GetAllData()->rapidEffectData;
	SetHp(Data.mMaxHp);
	mMeshName = "RapidSphere";
	SetMaxHp(GetHp());
	SetName(Data.mName.c_str());
	SetMaxLevel(Data.mMaxLevel);
}

void RapidFireEffect::UpdateActor()
{
	ItemEffect::UpdateActor();
	if (mOwner->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		static_cast<Cannon*>(mOwner)->SetInterval(GetGame()->GetAllData()->cannonData.mInterval - Data.mLevel * mLaunchIntervalDecreaseRate);
	}
}

void RapidFireEffect::Dead()
{
	ItemEffect::Dead();
	if (mOwner->GetTag() == CharacterActor::CharactersTag::ECannon && mOwner->GetState() == Actor::State::EActive && GetGame()->GetState() == Game::GameState::EGameplay)
	{
		auto c = static_cast<Cannon*>(mOwner);
		c->SetInterval(GetGame()->GetAllData()->cannonData.mInterval);
		c->SetRapid(nullptr);
	}
}

Barrier::Barrier(class Game* game)
	:ItemObject(game)
{
	iData = GetGame()->GetAllData()->barrierData;
	SetImageColor(iData.mColor);
	SetUp();
	mBatchName = "BarrierSphere";
	CreateMesh(mBatchName, "BarrierTranSphere");
}

bool Barrier::update()
{
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);

	if (!c->GetBarrier())
	{
		new BarrierEffect(c);
		c->GetBarrier()->SetInterval(GetGame()->GetAllData()->barrierEffectData.mInterval);
		c->GetBarrier()->SetTime(c->GetBarrier()->GetInterval());
		c->GetBarrier()->SetColor(iData.mColor);
		c->GetBarrier()->SetMaxHp(GetGame()->GetAllData()->barrierEffectData.mMaxHp);
		c->GetBarrier()->SetHp(c->GetBarrier()->GetMaxHp());
	}
	else
	{
		ItemEffectLvUp(c->GetBarrier());
		c->GetBarrier()->SetMaxHp(c->GetBarrier()->GetLevel() * 2 + 1);
		c->GetBarrier()->SetHp(c->GetBarrier()->GetMaxHp());
		c->GetBarrier()->TimeReset();
	}

	PlayUseSound1(iData);

	return true;
}

BarrierEffect::BarrierEffect(class PSideCharacterActor* owner)
	:ItemEffect(owner)
{
	owner->SetBarrier(this);
	Data = owner->GetGame()->GetAllData()->barrierEffectData;
	SetHp(Data.mMaxHp);
	SetMaxHp(GetHp());
	SetMaxLevel(Data.mMaxLevel);
	mMeshName = "BarrierSphere";
	SetName(Data.mName.c_str());

}

void BarrierEffect::Dead()
{
	ItemEffect::Dead();
	class PSideCharacterActor* c = static_cast<class PSideCharacterActor*>(mOwner);

	if (c->GetState() == Actor::State::EActive && GetGame()->GetState() == Game::GameState::EGameplay)
	{
		c->SetBarrier(nullptr);
	}
}
