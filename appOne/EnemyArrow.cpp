#include "EnemyArrow.h"
#include "Game.h"
#include "TreeMeshComponent.h"

EnemyArrow::EnemyArrow(CharacterActor* owner, const VECTOR& pos, const VECTOR& target)
	:Arrow(owner, pos, target)
{
	SetUp();
}

int EnemyArrow::SetUp()
{
	mTc = new TreeMeshComponent(this, false);
	mTc->SetTree("EnemyFlag");
	return 0;
}

void EnemyArrow::UpdateActor()
{
	Arrow::UpdateActor();

	for (auto chara : GetGame()->GetActorManager()->GetPSide())
	{
		if (chara->GetCapsule() && mCapsule->OverlapActor(this, chara) && chara->GetHp() > 0)
		{
			if (chara != GetGame()->GetActorManager()->GetPHome())
			{
				if (chara->GetHp() == 1)
				{
					chara->Damage(1);
				}
				else
				{
					chara->Damage(chara->GetHp() - 1);
				}
			}
			else if (GetGame()->GetActorManager()->GetPHome())
			{
				chara->Damage(1);
			}

			PlayHitSound();
			SetState(Actor::State::EDead);
		}
	}
}