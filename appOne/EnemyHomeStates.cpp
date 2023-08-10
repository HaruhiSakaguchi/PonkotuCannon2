#include "EnemyHomeStates.h"
#include "EnemyHome.h"
#include "StateComponent.h"
#include "window.h"
#include "Game.h"
#include "rand.h"
#include "EnemyArrow.h"
#include "EnemyFlag.h"

void EnemyHomeWait::Update()
{
	auto h = static_cast<EnemyHome*>(mOwnerCompo->GetActor());
	if (h->GetElapsedTime() >= h->GetInterval())
	{
		if (h->GetSpecialFlag())
		{
			mOwnerCompo->ChangeState("Special");
			return;
		}
		else
		{
			if ((int)(h->GetGame()->GetActorManager()->GetEnemies().size() - 1) == (h->GetLevel()))
			{
				mOwnerCompo->ChangeState("LvUp");
				return;
			}
			else if ((int)(h->GetGame()->GetActorManager()->GetEnemies().size()) < (h->GetLevel() + 1) && (int)(h->GetGame()->GetActorManager()->GetEnemies().size()) < h->GetMaxLevel() && h->GetDore()->GetCloseComplete())
			{
				mOwnerCompo->ChangeState("Generate");
				return;
			}
		}
	}
	else
	{
		if (h->GetBattlePoints() >= h->GetMaxBattlePoints())
		{
			int num = rand();
			if (num % 3 == 0)
			{
				if (h->GetGenerateTamaLv() < h->GetLevel())
				{
					h->SetGenerateTamaLv(h->GetGenerateTamaLv() + 1);
					h->SetBattlePoints(h->GetBattlePoints() - h->GetGame()->GetAllData()->eHomeData.mGenerateLvLvUpPoint);
				}
			}
			else if (num % 2 == 0)
			{
				if (h->GetGenerateSatelliteLv() < h->GetLevel())
				{
					h->SetGenerateSatelliteLv(h->GetGenerateSatelliteLv() + 1);
					h->SetBattlePoints(h->GetBattlePoints() - h->GetGame()->GetAllData()->eHomeData.mGenerateLvLvUpPoint);
				}
			}
			else
			{
				h->HomeLvUp();
				h->SetElapsedTime(0.0f);
			}
		}
	}

	h->SetElapsedTime(h->GetElapsedTime() + delta * 60.0f);
}

void EnemyHomeLvUp::Update()
{
	auto h = static_cast<EnemyHome*>(mOwnerCompo->GetActor());

	if (mLvUpCnt % 2 == 0)
	{
		if (h->GetBattlePoints() >= h->GetGame()->GetAllData()->eHomeData.mHomeLvUpUsePoint && h->GetLevel() < h->GetMaxLevel())
		{
			h->SetBattlePoints(h->GetBattlePoints() - h->GetGame()->GetAllData()->eHomeData.mHomeLvUpUsePoint);
			mLvUpCnt++;
			h->HomeLvUp();

			if (h->GetLevel() == h->GetMaxLevel() && h->GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
			{
				static_cast<GamePlay*>(h->GetGame()->GetCurState())->ChangeBgm();
				h->SetSpecialFlag(true);
				setVolume(h->GetGame()->GetAllData()->eHomeData.mSpecialReleaseSound, h->GetGame()->GetSoundVolumeManager()->GetEffectVolume() + h->GetGame()->GetAllData()->eHomeData.mSpecialReleaseSoundVolumeOffset);
				playSound(h->GetGame()->GetAllData()->eHomeData.mSpecialReleaseSound);
			}
		}

		h->SetElapsedTime(0.0f);
	}
	else
	{
		if (!h->GetGame()->GetActorManager()->GetEnemies().empty())
		{
			int num = random(0, ((int)(h->GetGame()->GetActorManager()->GetEnemies().size()) - 1));
			auto enemy = h->GetGame()->GetActorManager()->GetEnemies()[num];
			int lvUpUsePoint = (h->GetGame()->GetAllData()->eHomeData.mUnitLvUpBasePoint + h->GetGame()->GetAllData()->eHomeData.mUnitLvUpEveryLvPoint * enemy->GetLevel());
			if (enemy->GetLevel() < h->GetLevel() && lvUpUsePoint <= h->GetBattlePoints())
			{
				h->SetBattlePoints(h->GetBattlePoints() - lvUpUsePoint);
				h->EnemyLvUp(enemy);
				h->SetElapsedTime(0.0f);
			}
			else
			{
				h->SetElapsedTime(h->GetInterval() / 2.0f);
			}
		}
		mLvUpCnt++;
	}

	mOwnerCompo->ChangeState("Wait");
	return;
}

void EnemyHomeGenerate::Update()
{
	auto h = static_cast<EnemyHome*>(mOwnerCompo->GetActor());

	VECTOR pos = VECTOR(random(h->GetGame()->GetActorManager()->GetStage()->GetStageMinX(), h->GetGame()->GetActorManager()->GetStage()->GetStageMaxX()), random(4.0f, 7.5f), random(h->GetGame()->GetActorManager()->GetStage()->GetStageMinZ(), h->GetGame()->GetActorManager()->GetStage()->GetCenterPos().z));
	int num = random(0, 4);
	if (h->GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		if (num < 4)
		{
			int tamaGenePoint = (h->GetGame()->GetAllData()->eHomeData.mTamaGenerateBasePoint + h->GetGenerateTamaLv() * h->GetGame()->GetAllData()->eHomeData.mUnitLvUpEveryLvPoint);

			if (h->PositionOnMap(pos, h->GetGame()->GetAllData()->tamaData.mRadius) && h->InEnemyArea(pos) && h->GetBattlePoints() >= tamaGenePoint)
			{
				pos.y = 0.0f;
				h->GenerateTama(pos);
				h->SetBattlePoints(h->GetBattlePoints() - tamaGenePoint);
				h->SetElapsedTime(0.0f);
				h->SetGenerateFlag(1);
				h->GetDore()->Open();
			}
			else
			{
				h->SetElapsedTime(h->GetInterval() / 2.0f);
			}
		}
		else
		{
			int satelliteGenePoint = (h->GetGame()->GetAllData()->eHomeData.mSatelliteGenerateBasePoint + h->GetGenerateSatelliteLv() * h->GetGame()->GetAllData()->eHomeData.mUnitLvUpEveryLvPoint);
			if (h->PositionOnMap(pos, h->GetGame()->GetAllData()->satelliteData.mHeight) && h->InEnemyArea(pos) && h->GetBattlePoints() >= satelliteGenePoint)
			{
				h->GenerateSatellite(pos);
				h->SetBattlePoints(h->GetBattlePoints() - satelliteGenePoint);
				h->SetElapsedTime(0.0f);
				h->SetGenerateFlag(1);
				h->GetDore()->Open();
			}
			else
			{
				h->SetElapsedTime(h->GetInterval() / 2.0f);
			}
		}
	}
	else
	{
		h->SetElapsedTime(0.0f);
	}

	mOwnerCompo->ChangeState("Wait");
	return;
}

void EnemyHomeSpecial::OnEnter()
{
	mSpecialCnt = 20;
	mScnt = 0;
}

void EnemyHomeSpecial::Update()
{
	auto h = static_cast<EnemyHome*>(mOwnerCompo->GetActor());

	if (++mScnt % 7 == 0)
	{
		h->GetGame()->GetCameraManager()->ChangeCamera("EHomeCamera");
		int num = random(0, (int)h->GetGame()->GetActorManager()->GetPSide().size());

		if (num < h->GetGame()->GetActorManager()->GetPSide().size())
		{
			auto chara = h->GetGame()->GetActorManager()->GetPSide()[num];
			new EnemyArrow(h, h->GetFlag1()->GetPosition(), chara->GetPosition() + chara->GetCapsulOffset());
			new EnemyArrow(h, h->GetFlag2()->GetPosition(), chara->GetPosition() + chara->GetCapsulOffset());
		}
		else if (h->GetGame()->GetActorManager()->GetPHome())
		{
			new EnemyArrow(h, h->GetFlag1()->GetPosition(), h->GetGame()->GetActorManager()->GetPHome()->GetPosition() + h->GetGame()->GetActorManager()->GetPHome()->GetCapsulOffset());
			new EnemyArrow(h, h->GetFlag2()->GetPosition(), h->GetGame()->GetActorManager()->GetPHome()->GetPosition() + h->GetGame()->GetActorManager()->GetPHome()->GetCapsulOffset());
		}

		mSpecialCnt--;
	}

	if (mSpecialCnt <= 0)
	{
		mOwnerCompo->ChangeState("Wait");
		return;
	}
}

void EnemyHomeSpecial::OnExit()
{
	auto h = static_cast<EnemyHome*>(mOwnerCompo->GetActor());
	h->SetSpecialFlag(false);
	h->GetGame()->GetCameraManager()->ChangeCamera("NormalCamera");
	h->SetElapsedTime(0.0f);
}
