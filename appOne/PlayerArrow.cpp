#include "PlayerArrow.h"
#include "Game.h"
#include "TreeMeshComponent.h"

PlayerArrow::PlayerArrow(CharacterActor* owner, const VECTOR& pos, const VECTOR& target)
	:Arrow(owner, pos, target)
{
	SetUp();

}

int PlayerArrow::SetUp()
{
	mTc = new TreeMeshComponent(this, false);
	mTc->SetTree("PlayerFlag");
	return 0;
}

void PlayerArrow::UpdateActor()
{
	Arrow::UpdateActor();
	for (auto chara : GetGame()->GetActorManager()->GetEnemies())
	{
		if (chara->GetCapsule() && mCapsule->OverlapActor(this, chara) && chara->GetHp() > 0)
		{
			if (chara->GetHp() == 1)
			{
				chara->Damage(1);
			}
			else
			{
				chara->Damage(chara->GetHp() - 1);
			}

			SetState(Actor::State::EDead);
			PlayHitSound();
		}
	}

	if (GetGame()->GetActorManager()->GetEHome() && mCapsule->OverlapActor(this, GetGame()->GetActorManager()->GetEHome()))
	{
		GetGame()->GetActorManager()->GetEHome()->Damage(1);
		SetState(Actor::State::EDead);
		PlayHitSound();
	}

}
