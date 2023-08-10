#include "PSideCharacterActor.h"
#include "Game.h"

PSideCharacterActor::PSideCharacterActor(class Game* game)
	: CharacterActor(game)
	, mUI(nullptr)
	, mNum(0)
	, mPower(nullptr)
	, mSpeed(nullptr)
	, mBarrier(nullptr)
	, mRapid(nullptr)
	, mMaxDamageInterval(0.0f)
{
	GetGame()->GetActorManager()->AddPSide(this);
	mNum = (int)(GetGame()->GetActorManager()->GetPSide().size()) - 1;
}

PSideCharacterActor::~PSideCharacterActor()
{
	GetGame()->GetActorManager()->RemovePSide(this);
	if (mUI)
	{
		mUI->CloseMe();
	}
}

void PSideCharacterActor::Dead()
{
	for (auto pSide : GetGame()->GetActorManager()->GetPSide())
	{
		if (pSide->GetNum() > GetNum())
		{
			pSide->SetNum(pSide->GetNum() - 1);
		}
	}

	if (mPower)
	{
		SAFE_DELETE(mPower);
	}
	if (mSpeed)
	{
		SAFE_DELETE(mSpeed);
	}
	if (mRapid)
	{
		SAFE_DELETE(mRapid);
	}
	if (mBarrier)
	{
		SAFE_DELETE(mBarrier);
	}

	PlayDeadSound();

}

void PSideCharacterActor::Damage(int damage)
{
	if (GetDamageInterval() <= 0.0f)
	{
		if (GetBarrier())
		{
			GetBarrier()->SetHp(GetBarrier()->GetHp() - 1);
			PlayGurdSound();
		}
		else
		{
			SetHp(GetHp() - damage);
			PlayDamageSound();
		}
		SetDamageInterval(mMaxDamageInterval);
	}
	else
	{
		return;
	}

	if (GetHp() <= 0)
	{
		SetState(Actor::State::EDead);
	}
}
