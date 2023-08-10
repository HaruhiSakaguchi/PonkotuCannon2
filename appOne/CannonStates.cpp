#include "CannonStates.h"
#include "Cannon.h"
#include "StateComponent.h"
#include "window.h"
#include "PlayerBullet.h"
#include "Game.h"
#include "COLLISION_MAP.h"
#include "PlayerHome.h"
#include "CameraManager.h"
#include "EnemyHome.h"

void CountInterval(Cannon* p)
{
	float mTimer = p->GetTimer();
	mTimer += delta * 0.25f;
	p->SetTimer(mTimer);
	if (p->GetTimer() >= p->GetInterval())
	{
		p->SetTimer(p->GetInterval());
	}
}

void UpCounter(Cannon* c)
{
	if (c->GetTimer() >= c->GetInterval()) {
		if ((int)c->GetItemNums().size() != 0)
		{
			if ((int)c->GetItemNums().size() > 1)
			{
				int Scnt = c->GetSlideCnt();
				Scnt++;
				c->SetSlideCnt(Scnt);
			}

			if (c->GetSlideCnt() > 15 && c->GetItemNums()[c->GetCnt()] == 0)
			{
				int cnt = c->GetCnt();
				if (c->GetItemNums()[c->GetCnt() + 1] != 1)
				{
					++cnt %= (int)c->GetItemNums().size();
					c->SetCnt(cnt);
					if (c->GetItemNums().size() != 1)
					{
						setVolume(c->GetSlide(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume() + c->GetGame()->GetAllData()->cannonData.mSlideSoundVolumeOffset);
						playSound(c->GetSlide());
					}
					else
					{
						setVolume(c->GetOutOfBullets(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume());
						playSound(c->GetOutOfBullets());
					}
				}
				else if (c->GetHp() < c->GetMaxHp())
				{
					++cnt %= (int)c->GetItemNums().size();
					c->SetCnt(cnt);
					if (c->GetItemNums().size() != 1)
					{
						setVolume(c->GetSlide(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume() + c->GetGame()->GetAllData()->cannonData.mSlideSoundVolumeOffset);
						playSound(c->GetSlide());
					}
					else
					{
						setVolume(c->GetOutOfBullets(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume());
						playSound(c->GetOutOfBullets());
					}
				}
				else
				{
					if ((int)c->GetItemNums().size() > 2)
					{
						int ItemNum = (int)c->GetItemNums().size();
						int cnt = 0;
						for (int i = 0; i < ItemNum; i++)
						{
							if (c->GetItemNums()[i] == 1)
							{
								cnt++;
							}
						}
						if ((int)c->GetItemNums().size() - 1 != cnt)
						{
							++cnt %= (int)c->GetItemNums().size();
							c->SetCnt(cnt);
							if (c->GetItemNums().size() != 1)
							{
								setVolume(c->GetSlide(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume());
								playSound(c->GetSlide());
							}
							else
							{
								setVolume(c->GetOutOfBullets(), c->GetGame()->GetSoundVolumeManager()->GetEffectVolume());
								playSound(c->GetOutOfBullets());
							}
						}
					}
				}

				c->SetSlideCnt(0);
			}
		}
	}
	else
	{
		c->SetSlideCnt(15);
	}

}

void Launch(Cannon* p)
{
	if (p->GetGame()->GetState() == Game::GameState::EGameplay)
	{
		if (p->GetCnt() == 0 && p->GetTimer() >= p->GetInterval())
		{
			VECTOR vec = p->GetTargetPosition() - (p->GetPosition() + p->GetGame()->GetAllData()->cannonData.mBodyOffsetPos);
			p->SetLaunchTime(p->GetGame()->GetAllData()->cannonData.mLaunchTime);
			new PlayerBullet(p, p->GetPosition() + p->GetGame()->GetAllData()->cannonData.mBodyOffsetPos + p->GetCapsulOffset(), vec.normalize());
		}
		if (p->GetCnt() != 0)
		{
			p->DropItems(p->GetItemNums()[p->GetCnt()]);
			p->RemoveItemNum(p->GetCnt());
			p->SetCnt(0);
		}

		p->SetTimer(0.0f);
	}
}


void CannonWait::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	CountInterval(p);
	UpCounter(p);

	if (p->GetTimer() >= p->GetInterval())
	{
		for (auto enemy : p->GetGame()->GetActorManager()->GetEnemies())
		{
			if (p->CollisionCircle(p->GetRange(), enemy->GetRadius(), p->GetPosition(), enemy->GetPosition() + enemy->GetCapsulOffset()))
			{
				mOwnerCompo->ChangeState("Rotate");
				return;
			}
		}
		for (auto item : p->GetGame()->GetActorManager()->GetItems())
		{
			if (p->CollisionCircle(p->GetRange(), item->GetRadius(), p->GetPosition(), item->GetPosition() + item->GetCapsulOffset()))
			{
				mOwnerCompo->ChangeState("Rotate");
				return;
			}
		}
		if (p->GetGame()->GetActorManager()->GetEHome() && p->CollisionCircle(p->GetRange(), p->GetGame()->GetActorManager()->GetEHome()->GetRadius(), p->GetPosition(), p->GetGame()->GetActorManager()->GetEHome()->GetPosition() + p->GetGame()->GetActorManager()->GetEHome()->GetCapsulOffset()))
		{
			mOwnerCompo->ChangeState("Rotate");
			return;
		}

		p->SetTimer(0.0f);
		mOwnerCompo->ChangeState("Rotate");
		return;
	}
	else
	{
		mOwnerCompo->ChangeState("Move");
		return;
	}
}


void CannonMove::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	if (p->GetMoveState() == Cannon::MoveState::EStay)
	{
		mOwnerCompo->ChangeState("Wait");
		return;
	}
	else if (p->GetMoveState() == Cannon::MoveState::EReturn)
	{
		mOwnerCompo->ChangeState("Return");
		return;
	}
	else if (p->GetMoveState() == Cannon::MoveState::EHomePatroll)
	{
		mOwnerCompo->ChangeState("HomePatroll");
		return;
	}
	else if (p->GetMoveState() == Cannon::MoveState::EFieldPatroll)
	{
		mOwnerCompo->ChangeState("FieldPatroll");
		return;
	}
}

void CannonMoveReturnHome::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	if (p->GetGame()->GetActorManager()->GetPHome())
	{
		if (p->CollisionCircle(10.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetPosition(), p->GetPosition()))
		{
			mOwnerCompo->ChangeState("Wait");
			p->SetMoveState(Cannon::MoveState::EStay);
			return;
		}

		VECTOR vec = p->GetGame()->GetActorManager()->GetPHome()->GetPosition() - p->GetPosition();
		vec.normalize();
		VECTOR angle = p->GetRotation();
		int EndOfRotate = p->rotate(&angle, vec, 0.05f);
		p->SetRotation(angle);
		VECTOR pos = p->GetPosition();

		if (EndOfRotate == 1)
		{
			p->SetPosition(pos + vec * p->GetAdvSpeed());
		}

		if (p->GetMoveState() != Cannon::MoveState::EReturn)
		{
			mOwnerCompo->ChangeState("Wait");
			return;
		}
	}
	else
	{
		mOwnerCompo->ChangeState("Wait");
		p->SetMoveState(Cannon::MoveState::EStay);
		return;
	}

}

void CannonMoveHomePatroll::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	if (p->GetGame()->GetActorManager()->GetPHome())
	{
		VECTOR vec = p->GetGame()->GetActorManager()->GetPHome()->GetHomeTargetPoints()[p->GetTPIndex()] - p->GetPosition();
		vec.normalize();
		VECTOR angle = p->GetRotation();
		int EndOfRotate = p->rotate(&angle, vec, 0.05f);
		p->SetRotation(angle);
		VECTOR pos = p->GetPosition();
		bool NextPointEmpty = true;

		for (auto cannon : p->GetGame()->GetActorManager()->GetPSide())
		{
			if (p != cannon && cannon->GetTag() == CharacterActor::CharactersTag::ECannon && p->CollisionCircle(1.0f, cannon->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetHomeTargetPoints()[p->GetTPIndex()], cannon->GetPosition()))
			{
				NextPointEmpty = false;
			}
		}

		if (EndOfRotate == 1 && NextPointEmpty)
		{
			p->SetPosition(pos + vec * p->GetAdvSpeed());
		}

		if (p->CollisionCircle(1.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetHomeTargetPoints()[p->GetTPIndex()], p->GetPosition()))
		{
			p->SetTPIndex(p->GetNextTpIndex());
		}

		if (p->GetMoveState() != Cannon::MoveState::EHomePatroll)
		{
			mOwnerCompo->ChangeState("Wait");
			return;
		}

		CountInterval(p);

		if (p->GetTimer() >= p->GetInterval())
		{
			for (auto enemy : p->GetGame()->GetActorManager()->GetEnemies())
			{
				if (p->CollisionCircle(p->GetRange(), enemy->GetRadius(), p->GetPosition(), enemy->GetPosition() + enemy->GetCapsulOffset()) && p->CollisionCircle(7.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetPosition(), p->GetPosition()))
				{
					mOwnerCompo->ChangeState("Rotate");
					return;
				}
			}
			for (auto item : p->GetGame()->GetActorManager()->GetItems())
			{
				if (p->CollisionCircle(p->GetRange(), item->GetRadius(), p->GetPosition(), item->GetPosition() + item->GetCapsulOffset()) && p->CollisionCircle(7.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetPosition(), p->GetPosition()))
				{
					mOwnerCompo->ChangeState("Rotate");
					return;
				}
			}
		}
	}
	else
	{
		mOwnerCompo->ChangeState("Wait");
		p->SetMoveState(Cannon::MoveState::EStay);
		return;
	}
}

void CannonMoveFieldPatroll::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	if (p->GetGame()->GetActorManager()->GetPHome())
	{
		VECTOR vec = p->GetGame()->GetActorManager()->GetPHome()->GetFieldTargetPoints()[p->GetTPIndex()] - p->GetPosition();
		vec.normalize();
		VECTOR angle = p->GetRotation();
		int EndOfRotate = p->rotate(&angle, vec, 0.05f);
		p->SetRotation(angle);
		VECTOR pos = p->GetPosition();
		bool NextPointEmpty = true;

		for (auto cannon : p->GetGame()->GetActorManager()->GetPSide())
		{
			if (p != cannon && cannon->GetTag() == CharacterActor::CharactersTag::ECannon && p->CollisionCircle(1.0f, cannon->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetHomeTargetPoints()[p->GetTPIndex()], cannon->GetPosition()))
			{
				NextPointEmpty = false;
			}
		}

		if (EndOfRotate == 1 && NextPointEmpty)
		{
			p->SetPosition(pos + vec * p->GetAdvSpeed());
		}

		if (p->CollisionCircle(1.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetFieldTargetPoints()[p->GetTPIndex()], p->GetPosition()))
		{
			p->SetTPIndex(p->GetNextTpIndex());
		}

		if (p->GetMoveState() != Cannon::MoveState::EFieldPatroll)
		{
			mOwnerCompo->ChangeState("Wait");
			return;
		}

		CountInterval(p);

		if (p->GetTimer() >= p->GetInterval())
		{
			for (auto enemy : p->GetGame()->GetActorManager()->GetEnemies())
			{
				if (p->CollisionCircle(p->GetRange(), enemy->GetRadius(), p->GetPosition(), enemy->GetPosition() + enemy->GetCapsulOffset()) && p->CollisionCircle(7.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetPosition(), p->GetPosition()))
				{
					mOwnerCompo->ChangeState("Rotate");
					return;
				}
			}
			for (auto item : p->GetGame()->GetActorManager()->GetItems())
			{
				if (p->CollisionCircle(p->GetRange(), item->GetRadius(), p->GetPosition(), item->GetPosition() + item->GetCapsulOffset()) && p->CollisionCircle(7.0f, p->GetRadius(), p->GetGame()->GetActorManager()->GetPHome()->GetPosition(), p->GetPosition()))
				{
					mOwnerCompo->ChangeState("Rotate");
					return;
				}
			}
		}
	}
	else
	{
		mOwnerCompo->ChangeState("Wait");
		p->SetMoveState(Cannon::MoveState::EStay);
		return;
	}
}

void CannonLaunch::OnEnter()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	for (auto eSide : p->GetGame()->GetActorManager()->GetEnemies())
	{
		if (eSide->GetHp() != 0)
		{
			VECTOR target = eSide->GetPosition();
			target.y += eSide->GetCapsulOffset().y;
			float distx = target.x - p->GetPosition().x;
			float disty = target.y - (p->GetPosition().y);
			float distz = target.z - p->GetPosition().z;
			float dist = sqrtf(distx * distx + disty * disty + distz * distz);

			float tdistx = mTarget.x - p->GetPosition().x;
			float tdisty = mTarget.y - (p->GetPosition().y);
			float tdistz = mTarget.z - p->GetPosition().z;
			float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

			if (mTarget.x == 0.0f && mTarget.y == 0.0f && mTarget.z == 0.0f)
			{
				mTarget = eSide->GetPosition();
				mTarget.y += eSide->GetCapsulOffset().y;
			}
			else if (dist <= tdist)
			{
				mTarget = eSide->GetPosition();
				mTarget.y += eSide->GetCapsulOffset().y;
			}
		}
	}
	for (auto item : p->GetGame()->GetActorManager()->GetItems())
	{
		VECTOR target = item->GetPosition();
		target.y += item->GetCapsulOffset().y;
		float distx = target.x - p->GetPosition().x;
		float disty = target.y - (p->GetPosition().y);
		float distz = target.z - p->GetPosition().z;
		float dist = sqrtf(distx * distx + disty * disty + distz * distz);

		float tdistx = mTarget.x - p->GetPosition().x;
		float tdisty = mTarget.y - (p->GetPosition().y);
		float tdistz = mTarget.z - p->GetPosition().z;
		float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

		if (mTarget.x == 0.0f && mTarget.y == 0.0f && mTarget.z == 0.0f)
		{
			mTarget = item->GetPosition() + item->GetCapsulOffset();
		}
		else if (dist <= tdist)
		{
			mTarget = item->GetPosition() + item->GetCapsulOffset();
		}

	}

	if (mTarget.x == 1000.0f && mTarget.y == 1000.0f && mTarget.z == 1000.0f && p->GetGame()->GetActorManager()->GetEHome())
	{
		mTarget = p->GetGame()->GetActorManager()->GetEHome()->GetPosition() + p->GetGame()->GetActorManager()->GetEHome()->GetCapsulOffset();
	}

	float tdistx = mTarget.x - p->GetPosition().x;
	float tdisty = mTarget.y - (p->GetPosition().y + p->GetCapsulOffset().y + p->GetGame()->GetAllData()->cannonData.mBodyOffsetPos.y);
	float tdistz = mTarget.z - p->GetPosition().z;
	float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);
}

void CannonLaunch::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	Launch(p);

	mOwnerCompo->ChangeState("Wait");
	return;

}

void CannonLaunch::OnExit()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	p->SetRange(p->GetGame()->GetAllData()->cannonData.mRange);
}

void CannonRotate::OnEnter()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	mTarget = VECTOR(1000.0f, 1000.0f, 1000.0f);

	for (auto eSide : p->GetGame()->GetActorManager()->GetEnemies())
	{
		if (eSide->GetHp() != 0)
		{
			VECTOR target = eSide->GetPosition();
			target.y += eSide->GetCapsulOffset().y;
			float distx = target.x - p->GetPosition().x;
			float disty = target.y - (p->GetPosition().y);
			float distz = target.z - p->GetPosition().z;
			float dist = sqrtf(distx * distx + disty * disty + distz * distz);

			float tdistx = mTarget.x - p->GetPosition().x;
			float tdisty = mTarget.y - (p->GetPosition().y);
			float tdistz = mTarget.z - p->GetPosition().z;
			float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

			if (mTarget.x == 1000.0f && mTarget.y == 1000.0f && mTarget.z == 1000.0f)
			{
				mTarget = eSide->GetPosition() + eSide->GetCapsulOffset();
			}
			else if (dist <= tdist)
			{
				mTarget = eSide->GetPosition() + eSide->GetCapsulOffset();
			}
		}
	}

	for (auto item : p->GetGame()->GetActorManager()->GetItems())
	{
		VECTOR target = item->GetPosition();
		target.y += item->GetCapsulOffset().y;
		float distx = target.x - p->GetPosition().x;
		float disty = target.y - (p->GetPosition().y);
		float distz = target.z - p->GetPosition().z;
		float dist = sqrtf(distx * distx + disty * disty + distz * distz);

		float tdistx = mTarget.x - p->GetPosition().x;
		float tdisty = mTarget.y - (p->GetPosition().y);
		float tdistz = mTarget.z - p->GetPosition().z;
		float tdist = sqrtf(tdistx * tdistx + tdisty * tdisty + tdistz * tdistz);

		if (mTarget.x == 1000.0f && mTarget.y == 1000.0f && mTarget.z == 1000.0f)
		{
			mTarget = item->GetPosition() + item->GetCapsulOffset();
		}
		else if (dist <= tdist)
		{
			mTarget = item->GetPosition() + item->GetCapsulOffset();
		}
	}

	if (mTarget.x == 1000.0f && mTarget.y == 1000.0f && mTarget.z == 1000.0f && p->GetGame()->GetActorManager()->GetEHome())
	{
		mTarget = p->GetGame()->GetActorManager()->GetEHome()->GetPosition() + p->GetGame()->GetActorManager()->GetEHome()->GetCapsulOffset();
	}

	mAdv = mTarget - (p->GetPosition() + p->GetGame()->GetAllData()->cannonData.mBodyOffsetPos + p->GetCapsulOffset());
}

void CannonRotate::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());

	UpCounter(p);
	VECTOR angle = p->GetRotation();
	int endOfRotate = p->rotate(&angle, mAdv.normalize(), 0.05f, true);

	p->SetRotation(angle);

	if (endOfRotate == 1)
	{
		mOwnerCompo->ChangeState("Launch");
		return;
	}
}

void CannonRotate::OnExit()
{
	mAdv = VECTOR(0.0f, 0.0f, 0.0f);
}

void CannonGenerate::OnEnter()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	mFirstTargetCompleteFlag = false;
	mFirstTarget = VECTOR(p->GetGame()->GetActorManager()->GetPHome()->GetPosition() + VECTOR(0.0f, 0.0f, -5.0f));
}

void CannonGenerate::OnExit()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	p->GetCapsule()->SetIsCollision(true);
}

void CannonGenerate::Update()
{
	Cannon* p = static_cast<Cannon*>(mOwnerCompo->GetActor());
	mTargetPos = p->GetInitPosition();
	if (!mFirstTargetCompleteFlag)
	{
		mTargetPos = mFirstTarget;
	}

	VECTOR vec = mTargetPos - p->GetPosition();
	vec.normalize();
	VECTOR angle = p->GetRotation();
	int endOfRotate = p->rotate(&angle, vec, 0.05f);
	p->SetRotation(angle);

	if (p->GetGame()->GetActorManager()->GetPHome())
	{
		if (endOfRotate == 1)
		{
			if (!mFirstTargetCompleteFlag)
			{
				if (p->GetGame()->GetActorManager()->GetPHome()->GetDore()->GetOpenComplete() == true)
				{
					p->SetPosition(p->GetPosition() + vec * p->GetAdvSpeed());
				}
			}
			else
			{
				p->SetPosition(p->GetPosition() + vec * p->GetAdvSpeed());
			}
		}

		if (p->CollisionCircle(p->GetRadius(), 0.5f, p->GetPosition(), mFirstTarget))
		{
			mFirstTargetCompleteFlag = true;
		}
		if (p->CollisionCircle(p->GetRadius(), 0.5f, p->GetPosition(), p->GetInitPosition()))
		{
			mOwnerCompo->ChangeState("Wait");
			return;
		}
	}
	else
	{
		mOwnerCompo->ChangeState("Wait");
		return;
	}

}

