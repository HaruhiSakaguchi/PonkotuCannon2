#include "TamaWeapon.h"
#include "Cannon.h"
#include "Game.h"
#include "window.h"
#include "BatchMeshComponent.h"

int TamaWeapon::mNum = 0;

TamaWeapon::TamaWeapon(class Tama* owner, const VECTOR& pos, const VECTOR& dir)
	: SphereWeapon(owner, owner->GetPosition(), dir)
	, mId(0)
	, mTime(0.0f)
{
	class Tama* t = static_cast<class Tama*>(mOwner);

	Data = GetGame()->GetAllData()->tWeaponData;
	iData = GetGame()->GetAllData()->tWeaponIData;

	UnMoveComponent();
	SetUp(Data);
	if (GetGame()->GetState() == Game::GameState::EGameplay && GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		setVolume(iData.mAttackSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + iData.mAttackSoundOffset);
		playSound(iData.mAttackSound);
	}

	BatchMeshComponent* bc = new BatchMeshComponent(this);
	bc->SetBatch("TamaTamaSphere");

	t->SetWeaponCnt(t->GetWeaponCnt() + 1);

	mId = mNum % 2;
	mNum++;

	SetScale(VECTOR(Data.mSize, Data.mSize, Data.mSize));

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);

	mTime = iData.mAttackTime;

}

TamaWeapon::~TamaWeapon()
{
	class Tama* t = static_cast<class Tama*>(mOwner);
	t->SetWeaponCnt(t->GetWeaponCnt() - 1);
	stopSound(iData.mAttackSound);
}

void TamaWeapon::UpdateActor()
{
	class Tama* t = static_cast<class Tama*>(mOwner);

	SetDamageInterval(t->GetDamageInterval());

	SetRotationY(GetRotation().y + 0.17f);
	SphereWeapon::UpdateActor();

	setVolume(iData.mAttackSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + iData.mAttackSoundOffset);

	VECTOR pos = t->GetPosition() + Data.mOffsetPos;
	VECTOR addPos;

	float preTime = mTime;

	mTime += delta * 2.0f;

	MATRIX mat;
	mat.identity();
	mat.mulRotateY(GetRotation().y);

	if (mId == 0)
	{
		addPos.x = cosf(t->GetAnimAngle() * 10.0f) * mTime;
		addPos.y = cosf(t->GetAnimAngle() * 10.0f);
		addPos.z = cosf(t->GetAnimAngle() * 10.0f) + sinf(t->GetAnimAngle() * 5.0f) * mTime;
	}
	else
	{
		addPos.x = -cosf(t->GetAnimAngle() * 10.0f) * mTime;
		addPos.y = cosf(t->GetAnimAngle() * 10.0f);
		addPos.z = cosf(t->GetAnimAngle() * 10.0f) + sinf(t->GetAnimAngle() * 5.0f) * mTime;
	}

	addPos = mat * addPos;

	SetPosition(pos + addPos);

	//owner‚Ìhp‚ª0ˆÈã‚È‚çcannon‚Æ“–‚½‚è”»’è‚³‚¹‚é
	bool ownerDead = GetOwner()->GetHp() > 0;

	for (auto pSide : GetGame()->GetActorManager()->GetPSide())
	{
		if (mCapsule->OverlapActor(this, pSide))
		{
			pSide->Damage(Data.mDamage);
		}
	}
}