#include "TamaStates.h"
#include "Tama.h"
#include "StateComponent.h"
#include "Game.h"
#include "window.h"
#include "rand.h"
#include "TamaWeapon.h"
#include "COLLISION_MAP.h"
#include "PlayerHome.h"
#include "EnemyHome.h"
#include "SEGMENT.h"

void TamaWait::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	elapsedTime = t->GetElapsedtime();
}

void TamaWait::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	elapsedTime += random(1) * delta * 60.0f;

	if (elapsedTime > t->GetMoveInterval())
	{
		elapsedTime = 0;
		t->SetElapsedTime(elapsedTime);
		mOwnerCompo->ChangeState("Move");
		return;
	}
}

void TamaMove::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	mTarget = VECTOR(1000.0f, 1000.0f, 1000.0f);
	mCnt = 0;

	for (auto pSide : t->GetGame()->GetActorManager()->GetPSide())
	{
		if (pSide->GetState() == Actor::State::EActive)
		{
			VECTOR target = pSide->GetPosition() + pSide->GetCapsulOffset();
			float distx = target.x - t->GetPosition().x;
			float disty = target.y - t->GetPosition().y;
			float distz = target.z - t->GetPosition().z;
			float dist = sqrtf(distx * distx + disty * disty + distz * distz);

			float tdistx = mTarget.x - t->GetPosition().x;
			float tdisty = mTarget.y - t->GetPosition().y;
			float tdistz = mTarget.z - t->GetPosition().z;
			float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

			if (mTarget.x == 1000.0f && mTarget.y == 1000.0f && mTarget.z == 1000.0f)
			{
				mTarget = target;
			}
			else if (dist < tdist)
			{
				mTarget = target;
			}
		}
	}
}

void TamaMove::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	VECTOR prePos = t->GetPosition();
	VECTOR pos = prePos;

	VECTOR vec = mTarget - pos;

	vec.normalize();

	VECTOR angle = t->GetRotation();
	t->rotate(&angle, vec, 0.05f);
	angle.x = 0.0f;
	angle.z = 0.0f;
	t->SetRotation(angle);

	pos.x += vec.x * t->GetAdvSpeed() * delta * 60.0f;
	pos.z += vec.z * t->GetAdvSpeed() * delta * 60.0f;

	//移動先がマップエリア内か
	if (t->PositionOnMap(pos, t->GetRadius()))
	{
		t->SetPosition(pos);
	}
	else
	{
		t->SetPosition(prePos);
		mOwnerCompo->ChangeState("Wait");
		return;
	}

	if (++mCnt >= 20 || t->CollisionCircle(5.0f, 1.0f, t->GetPosition(), mTarget))
	{
		mOwnerCompo->ChangeState("Search");
		return;
	}
}
void TamaSeache::OnEnter()
{
	mCnt = 0;
	mRotateCnt = 0;
}

void TamaSeache::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
#ifdef _DEBUG
	t->GetCapsule()->segment(t->GetSight()->GetSP(), t->GetSight()->GetEP(), COLOR(255, 0, 0, 128), 100);
#endif

	if (++mRotateCnt < 36)
	{
		CharacterActor* c = nullptr;
		VECTOR p;

		if (t->GetCapsule()->LineTraceHitActor(t->GetSight(), &c, &p))
		{
			if (c->GetTag() == CharacterActor::CharactersTag::ECannon || c->GetTag() == CharacterActor::CharactersTag::EBarricade || c->GetTag() == CharacterActor::CharactersTag::EPHome)
			{
				t->SetTargetPos(c->GetPosition() + c->GetCapsulOffset());
				mOwnerCompo->ChangeState("RockOn");
				return;
			}
		}
	}
	else
	{
		mOwnerCompo->ChangeState("Wait");
		return;
	}

	t->SetRotationY(t->GetRotation().y + 0.17f);

}

void TamaRockOn::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	mTarget = t->GetTargetPos();
	t->SetAttackVector(mTarget - (t->GetPosition() + t->GetCapsulOffset()));
}

void TamaRockOn::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	VECTOR angle = t->GetRotation();
	VECTOR vec = t->GetAttackVector();
	vec.normalize();
	int EndOfRotate = t->rotate(&angle, vec, 0.05f);

	angle.x = 0.0f;
	angle.z = 0.0f;

	t->SetRotation(angle);

	if (EndOfRotate == 1)
	{
		mOwnerCompo->ChangeState("Charge");
		return;
	}
}

void TamaRockOn::OnExit()
{
}

void TamaCharge::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
	mTarget = t->GetTargetPos();
	mDir = t->GetAttackVector();
	VECTOR vec = mDir.normalize();
	mCnt = 0;
	mReb = 1.0f;
	mDir.normalize();
}

void TamaCharge::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
	VECTOR pos = t->GetPosition();
	if (mCnt < 20)
	{
		pos.x -= mDir.x * delta * 6.0f;
		pos.z -= mDir.z * delta * 6.0f;
	}

	if (20 < mCnt && mCnt < 40)
	{
		pos.x += mDir.x * delta * mReb * 60.0f;
		pos.z += mDir.z * delta * mReb * 60.0f;
		mReb *= -1;
	}

	t->SetDamageInterval(0.13f);
	t->SetPosition(pos);

	if (++mCnt >= 40)
	{
		mOwnerCompo->ChangeState("Attack");
		return;
	}
}

void TamaCharge::OnExit()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
	mTarget = VECTOR(0.0f, 0.0f, 0.0f);
	mDir = VECTOR(0.0f, 0.0f, 0.0f);
}

void TamaAttack::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	for (int i = 0; i < (int)(t->GetLevel() / 5); i++)
	{
		new TamaWeapon(t);
	}

	mCnt = 0;
	if (t->GetGame()->GetState() == Game::GameState::EGameplay && t->GetGame()->GetCurState()->GetMState() == UIMainState::State::EGamePlay)
	{
		setVolume(t->GetDushSound(), t->GetGame()->GetSoundVolumeManager()->GetEffectVolume() + t->GetGame()->GetAllData()->tamaData.mDushSoundVolumeOffsset);
		playSound(t->GetDushSound());
	}

	mAttackFlame = (int)t->GetAttackVector().magSq() + 2;
}

void TamaAttack::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	VECTOR pos = t->GetPosition();

	VECTOR vec = t->GetAttackVector();
	vec.normalize();

	pos.x += vec.x * t->GetAdvSpeed();
	pos.z += vec.z * t->GetAdvSpeed();

	t->SetPosition(pos);

	for (auto pSide : t->GetGame()->GetActorManager()->GetPSide())
	{
		if (t->GetCapsule()->OverlapActor(t, pSide))
		{
			pSide->Damage(1 + (int)(t->GetLevel() / 2));
			mOwnerCompo->ChangeState("Wait");
			return;
		}
	}

	if (++mCnt >= mAttackFlame || !t->GetGame()->GetActorManager()->GetPHome())
	{
		mOwnerCompo->ChangeState("Search");
		return;
	}
}

void TamaAttack::OnExit()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
	t->SetAttackVector(VECTOR(0.0f, 0.0f, 0.0f));
	t->SetTargetPos(VECTOR(0.0f, 0.0f, 0.0f));
	mAttackFlame = 0;
}

void TamaGenerate::OnEnter()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	mFirstTargetCompleteFlag = false;
	mFirstTarget = VECTOR(t->GetGame()->GetActorManager()->GetEHome()->GetPosition() + VECTOR(0.0f, 0.0f, 10.0f));
}

void TamaGenerate::OnExit()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());
	t->GetCapsule()->SetIsCollision(true);
}

void TamaGenerate::Update()
{
	Tama* t = static_cast<Tama*>(mOwnerCompo->GetActor());

	mTargetPos = t->GetInitPosition();
	if (!mFirstTargetCompleteFlag)
	{
		mTargetPos = mFirstTarget;
	}

	VECTOR vec = mTargetPos - t->GetPosition();
	vec.normalize();
	VECTOR angle = t->GetRotation();
	int endOfRotate = t->rotate(&angle, vec, 0.05f);
	t->SetRotation(angle);

	if (endOfRotate == 1)
	{
		if (!mFirstTargetCompleteFlag)
		{
			if (t->GetGame()->GetActorManager()->GetEHome() && t->GetGame()->GetActorManager()->GetEHome()->GetDore()->GetOpenComplete())
			{
				t->SetPosition(t->GetPosition() + vec * t->GetAdvSpeed());
			}
			else if (!t->GetGame()->GetActorManager()->GetEHome())
			{
				t->SetPosition(t->GetPosition() + vec * t->GetAdvSpeed());
			}
		}
		else
		{
			t->SetPosition(t->GetPosition() + vec * t->GetAdvSpeed());
		}
	}

	if (t->CollisionCircle(t->GetRadius(), 0.5f, t->GetPosition(), mFirstTarget))
	{
		mFirstTargetCompleteFlag = true;
	}
	if (t->CollisionCircle(t->GetRadius(), 0.5f, t->GetPosition(), t->GetInitPosition()))
	{
		mOwnerCompo->ChangeState("Wait");
		return;
	}
}



