#include "EnemyHome.h"
#include "TreeMeshComponent.h"
#include "EnemyFlag.h"
#include "HpGaugeSpriteComponent.h"
#include "Game.h"
#include "rand.h"
#include "window.h"
#include "sound.h"
#include "EnemyHomeStates.h"

EnemyHome::EnemyHome(class Game* game)
	: CharacterActor(game)
	, mTc(nullptr)
	, mFlag1(nullptr)
	, mFlag2(nullptr)
	, mDore(nullptr)
	, mBattlePoints(0)
	, mMaxBattlePoints(0)
	, mGenerateTamaLevel(0)
	, mGenerateSatelliteLevel(0)
	, mInterval(0.0f)
	, mElapsedTime(0.0f)
	, mGenerateFlag(0)
	, mFirstSatelliteGenerateFlag(0)
	, mFirstTamaGenerateFlag(0)
	, mSpecialFlag(false)
{
	Data = GetGame()->GetAllData()->eHomeData;
	GetGame()->GetActorManager()->SetEHome(this);
}

EnemyHome::~EnemyHome()
{
	GetGame()->GetActorManager()->SetEHome(nullptr);
}

int EnemyHome::SetUp()
{
	mTc = new TreeMeshComponent(this);
	mTc->SetTree("Home");
	SetNormalMesh(mTc);
	mDore = new Dore(GetGame());
	mDore->SetCloseEvent([this]() {mGenerateFlag = 0; });
	mFlag1 = new EnemyFlag(GetGame());
	mFlag1->SetRotationY(3.1415926f);
	mFlag2 = new EnemyFlag(GetGame());
	mFlag2->SetRotationY(3.1415926f);

	mProps.emplace_back(mDore);
	mProps.emplace_back(mFlag1);
	mProps.emplace_back(mFlag2);

	mCapsule = new CapsuleComponent(this);

	SetTag(CharactersTag::EEHome);
	SetHp(Data.mMaxHp);
	SetMaxHp(Data.mMaxHp);
	SetInitMaxHp(Data.mMaxHp);
	mMaxBattlePoints = Data.mInitMaxPoint;
	SetRadius(Data.mRadius);
	SetHeight(Data.mHeight);
	SetName("EnemyHome");
	new HpGaugeSpriteComponent(this, Data.mHpGaugeOffset);
	mInterval = Data.mGenerateInterval;

	SetImageColor(Data.mImageColor);

	mGenerateTamaLevel = GetLevel();
	mGenerateSatelliteLevel = GetLevel();

	auto state = new StateComponent(this);
	state->RegisterState(new EnemyHomeWait(state));
	state->RegisterState(new EnemyHomeGenerate(state));
	state->RegisterState(new EnemyHomeLvUp(state));
	state->RegisterState(new EnemyHomeSpecial(state));
	state->ChangeState("Wait");

	return 1;
}

void EnemyHome::UpdateActor()
{

	mDore->SetPosition(GetPosition() + Data.mDoreOffset);
	mFlag1->SetPosition(GetPosition() + Data.mFlag1Offset);
	mFlag2->SetPosition(GetPosition() + Data.mFlag2Offset);

	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}

	mInterval = Data.mGenerateInterval - Data.mGenerateInterval / 50.0f * GetLevel();
	mMaxBattlePoints = Data.mInitMaxPoint * (GetLevel() + 1);

	if (mBattlePoints < mMaxBattlePoints)
	{
		mBattlePoints++;
	}
	if (mBattlePoints < 0)
	{
		mBattlePoints = 0;
	}

	if (mGenerateFlag == 1)
	{
		mDore->SetIsRotate(true);
	}

	int cnt = 0;

	for (auto Actor : GetGame()->GetActorManager()->GetEnemies())
	{
		if (CollisionCircle(GetRadius(), Actor->GetRadius(), GetPosition(), Actor->GetPosition()))
		{
			if (Actor->GetTag() == CharacterActor::CharactersTag::ETama)
			{
				if (static_cast<class Tama*>(Actor)->GetStateCompoState()->GetName() != "Generate")
				{
					continue;
				}
			}
			else if (Actor->GetTag() == CharacterActor::CharactersTag::ESatellite)
			{
				if (static_cast<class Satellite*>(Actor)->GetStateCompoState()->GetName() != "Generate")
				{
					continue;
				}
			}
			cnt++;
		}
	}

	if (mGenerateFlag == 1 && cnt == 0)
	{
		mDore->Close();
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

void EnemyHome::Damage(int damage)
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

	if (GetHp() <= 0)
	{
		SetState(State::EDead);
	}
}

void EnemyHome::Dead()
{
	PlayDeadSound();

	std::ostringstream oss;
	oss << GetName().c_str() << "を破壊した！！";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());

	int tamaGenePoint = (Data.mTamaGenerateBasePoint + mGenerateTamaLevel * Data.mUnitLvUpEveryLvPoint);
	int satelliteGenePoint = (Data.mSatelliteGenerateBasePoint + mGenerateSatelliteLevel * Data.mUnitLvUpEveryLvPoint);

	while (mBattlePoints > tamaGenePoint || mBattlePoints > satelliteGenePoint)
	{
		VECTOR pos = VECTOR(random(GetGame()->GetActorManager()->GetStage()->GetStageMinX(), GetGame()->GetActorManager()->GetStage()->GetStageMaxX()), random(4.0f, 7.5f), random(GetGame()->GetActorManager()->GetStage()->GetStageMinZ(), GetGame()->GetActorManager()->GetStage()->GetCenterPos().z));
		int num = random(0, 4);
		if (num < 4)
		{
			if (PositionOnMap(pos, GetGame()->GetAllData()->tamaData.mRadius) && InEnemyArea(pos) && mBattlePoints >= tamaGenePoint && pos.z >= GetPosition().z)
			{
				pos.y = 0.0f;
				GenerateTama(pos);
				mBattlePoints -= tamaGenePoint;
				mElapsedTime = 0.0f;
				mGenerateFlag = true;
				mDore->Open();
			}
		}
		else
		{
			if (PositionOnMap(pos, GetGame()->GetAllData()->satelliteData.mHeight) && InEnemyArea(pos) && mBattlePoints >= satelliteGenePoint)
			{
				GenerateSatellite(pos);
				mBattlePoints -= satelliteGenePoint;
				mElapsedTime = 0.0f;
			}
		}
	}

	SpawnParticle(GetGame(), GetPosition(), "HomeHouse", 20);
	SpawnParticle(GetGame(), GetPosition(), "DoreDore", 20);
	SpawnParticle(GetGame(), GetPosition(), "EnemyFlagFlag", 40);

	for (auto prop : mProps)
	{
		prop->SetState(State::EDead);
	}
}

bool EnemyHome::InEnemyArea(const VECTOR& pos)
{
	float distX = pos.x - GetPosition().x;
	float distZ = pos.z - GetPosition().z;

	float dist = sqrtf(distX * distX + distZ * distZ);

	bool in = (dist <= 7.0f);
	return in;
}

void EnemyHome::GenerateTama(const VECTOR& pos)
{
	class Tama* tama = new class Tama(GetGame(), pos);
	if (mFirstTamaGenerateFlag == 0)
	{
		mFirstTamaGenerateFlag = 1;
		tama->SetNum(0);
	}
	tama->SetLevel(mGenerateTamaLevel);
	tama->SetUp();
	tama->SetPosition(GetPosition());
	tama->SetMaxHp((int)(tama->GetInitMaxHp() * ((tama->GetLevel() + tama->GetMaxLevel()) / 10.0f)));
	tama->SetHp(tama->GetMaxHp());
}

void EnemyHome::GenerateSatellite(const VECTOR& pos)
{
	class Satellite* satellite = new class Satellite(GetGame(), pos);
	if (mFirstSatelliteGenerateFlag == 0)
	{
		mFirstSatelliteGenerateFlag = 1;
		satellite->SetNum(0);
	}
	satellite->SetLevel(mGenerateSatelliteLevel);
	satellite->SetUp();
	satellite->SetMaxHp((int)(satellite->GetInitMaxHp() * ((satellite->GetLevel() + satellite->GetMaxLevel()) / 10.0f)));
	satellite->SetHp(satellite->GetMaxHp());
	VECTOR EPos = GetPosition();
	EPos.y = 0.5f;
	if (satellite->GetId() == 1)
	{
		EPos.y = -0.5f;
	}

	satellite->SetPosition(EPos);
}

void EnemyHome::HomeLvUp()
{
	SetLevel(GetLevel() + 1);
	std::ostringstream oss;
	oss << GetName().c_str() << "のLvが上がった！！[Lv." << GetLevel() << "]";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
}

void EnemyHome::EnemyLvUp(Enemy* enemy)
{
	enemy->SetLevel(enemy->GetLevel() + 1);
	int curMaxHp = enemy->GetMaxHp();
	enemy->SetMaxHp((int)(enemy->GetInitMaxHp() * ((enemy->GetLevel() + enemy->GetMaxLevel()) / 10.0f)));
	enemy->SetHp((int)(round(enemy->GetMaxHp() * (float)enemy->GetHp() / (float)curMaxHp)));
	std::ostringstream oss;
	oss << enemy->GetName().c_str() << "のLvが上がった！！[Lv." << enemy->GetLevel() << "]";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str().c_str());
}

void EnemyHome::CreateHomeArea()
{
	for (int i = 0; i < 36; i++)
	{
		auto flag = new EnemyFlag(GetGame());
		flag->SetPosition(GetPosition().x + sinf(i * 3.1415926f * 2 / 36.0f) * 7.0f, 0.0f, GetPosition().z + cosf(i * 3.1415926f * 2 / 36.0f) * 7.0f);
		flag->SetScale(VECTOR(0.5f, 0.5f, 0.5f));
		mProps.emplace_back(flag);
	}
}

