#include "Game.h"
#include "Cannon.h"
#include "CannonStates.h"
#include "window.h"
#include "TreeMeshComponent.h"
#include "CannonWheelL.h"
#include "CannonWheelR.h"
#include "UILog.h"
#include "CollisionMapComponent.h"
#include <sstream>
#include "UIPSideCharacterStatusClose.h"
#include "CapsuleComponent.h"

int Cannon::mCNum = 0;

Cannon::Cannon(class Game* game)
	: PSideCharacterActor(game)
	, mState(nullptr)
	, mCnt(0)
	, mSlideCnt(0)
	, mScale(1.0f)
	, mLaunchTime(0.0f)
	, mWheelL(nullptr)
	, mWheelR(nullptr)
	, mRange(0.0f)
	, mTimer(0.0f)
	, mMoveState(MoveState::EStay)
	, mTPIndex(0)
	, Body()
	, Master()
	, Target()
	, mInterval(0.0f)
{
}

Cannon::~Cannon()
{
	mItemNums.clear();
}

int Cannon::SetUp()
{
	//Data
	Data = GetGame()->GetAllData()->cannonData;

	//StateMacine
	mState = new StateComponent(this);
	mState->RegisterState(new CannonGenerate(mState));
	mState->RegisterState(new CannonWait(mState));
	mState->RegisterState(new CannonLaunch(mState));
	mState->RegisterState(new CannonMove(mState));
	mState->RegisterState(new CannonRotate(mState));
	mState->RegisterState(new CannonMoveReturnHome(mState));
	mState->RegisterState(new CannonMoveHomePatroll(mState));
	mState->RegisterState(new CannonMoveFieldPatroll(mState));
	mState->ChangeState("Generate");

	//基底クラスのデータにセット
	SetTag(CharacterActor::CharactersTag::ECannon);
	SetPosition(Data.mInitPos);
	SetRadius(Data.mCannonCapsulRadius);
	SetHeight(Data.mCannonCapsulHeight);
	SetHp(Data.mMaxHp);
	SetMaxHp(GetHp());
	SetInitPosition(Data.mInitPos);
	SetGravity(Data.mGravity);
	SetJumpFlag(Data.mJumpFlag);
	SetJumpVel(Data.mJumpVelocity);
	SetAdvSpeed(Data.mAdvSpeed);
	SetCapsulOffset(Data.mCapsulOffset);
	SetImageColor(Data.mImageColor);
	SetRange(Data.mRange);
	SetDamage(1);
	SetInitMaxHp(GetMaxHp());
	mMaxDamageInterval = Data.mMaxDamageInterval;
	mInterval = Data.mInterval;
	auto tc = new TreeMeshComponent(this, false);
	tc->SetTree("CannonBarrel");
	tc->SetOffsetAngle(VECTOR(0.0f, 3.141592f, 0.0f));
	tc->SetOffsetPos(Data.mBodyOffsetPos + GetCapsulOffset());
	SetNormalMesh(tc);

	tc = new TreeMeshComponent(this, false);
	tc->SetTree("CannonBarrelDamage");
	tc->SetOffsetAngle(VECTOR(0.0f, 3.141592f, 0.0f));
	tc->SetOffsetPos(Data.mBodyOffsetPos + GetCapsulOffset());
	SetDamageMesh(tc);

	mWheelL = new CannonWheelL(this);
	mWheelR = new CannonWheelR(this);

	new CollisionMapComponent(this);

	//砲弾のナンバー0をあらかじめセットしておく
	mItemNums.emplace_back(0);

	std::ostringstream oss;
	oss << "Cannon" << mCNum;

	mCNum++;

	mCapsule = new CapsuleComponent(this);
	mCapsule->SetIsCollision(false);
	mCapsule->AddNotCollisionTags((int)CharacterActor::CharactersTag::EPHome);
	mCapsule->AddNotCollisionTags((int)CharacterActor::CharactersTag::EBarricade);
	mCapsule->AddNotCollisionTags((int)CharacterActor::CharactersTag::EEHome);

	SetName(oss.str().c_str());

	oss << "[Lv." << GetLevel() << "]" << "が出撃。";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());

	new UIPSideCharacterStatusClose(this);
	return 0;
}

void Cannon::UpdateActor()
{
	float preScale = mScale;
	float Scale = preScale;

	//発射時に少し膨らむ
	if (mLaunchTime > 0.0f)
	{
		mLaunchTime -= delta * Data.mLaunchTimeDecreaseAdvSpeed;
		Scale = Data.mLaunchBodyScale;
	}
	else
	{
		if (mLaunchTime < 0.0f)
		{
			mLaunchTime = 0.0f;
		}
		Scale = Data.mNormalBodyScale;
	}

	mScale = preScale + (Scale - preScale) * Data.mChangeScaleSpeed;

	if (mScale < 0.0f)
	{
		mScale = Data.mNormalBodyScale;
	}

	//発射方向を決める
	Master.identity();

	Master.mulTranslate(GetPosition());
	Master.mulRotateY(GetRotation().y);
	Master.mulRotateY(3.141592f);

	Target.identity();
	Target.mulTranslate(0.0f, 0.0f, -GetRange());

	Body.identity();
	Body.mulTranslate(Data.mBodyOffsetPos);
	Body.mulScaling(mScale, mScale, mScale);
	Body.mulRotateX(-GetRotation().x);

	Target = Master * Body * Target;
	mTargetPos = VECTOR(Target._14, Target._24, Target._34);

	SetScale(VECTOR(mScale, mScale, mScale));

	if (GetGame()->GetCurState()->GetMState() != UIMainState::State::EGamePlay)
	{
		mState->ChangeState("Wait");
	}

	if (GetDamageInterval() > 0.0f)
	{
		SetDamageInterval(GetDamageInterval() - delta);
	}
}

void Cannon::Dead()
{
	PSideCharacterActor::Dead();
	SpawnParticle(GetGame(), GetPosition(), "CannonBarrelBarrel", 10);
	SpawnParticle(GetGame(), GetPosition(), "CannonWheelCylinder", 20);
	std::ostringstream oss;
	oss << GetName().c_str() << "は死んでしまった...。";
	GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
}


void Cannon::AddItemNum(int num)
{
	mItemNums.emplace_back(num);
	//6個以上は保存しない
	if (Data.mItemStockMaxSize < (int)mItemNums.size())
	{
		//0は砲弾なので除外から除外
		//ランダムで一つ取り除く
		int i = 0;
		while (i == 0)
		{
			i = rand() % Data.mItemStockMaxSize;
		}
		RemoveItemNum(i);
	}
}

void Cannon::RemoveItemNum(int num)
{
	//num番目のナンバーを取り除く
	auto iter = std::find(mItemNums.begin(), mItemNums.end(), mItemNums[num]);
	if (iter != mItemNums.end())
	{
		mItemNums.erase(iter);
	}
}

int Cannon::GetNextTpIndex()
{
	int idx = (mTPIndex + 1) % 4;
	return idx;
}
