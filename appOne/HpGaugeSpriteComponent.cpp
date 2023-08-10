#include "HpGaugeSpriteComponent.h"
#include "Game.h"
#include "CameraManager.h"
#include "CONTAINER/CONTAINER.h"
#include "CONTAINER/BATCH.h"
#include "CONTAINER/TREE.h"

HpGaugeSpriteComponent::HpGaugeSpriteComponent(Actor* owner, const VECTOR& offset)
	: MeshComponent(owner)
	, mMaxHp(static_cast<CharacterActor*>(owner)->GetHp())
	, mDivMaxHp((float)(1.0f / (float)(mMaxHp)) / 2)
	, mOffset(offset)
	, mGaugeWidth(0)
	, mGaugePosX(0)
	, Master()
	, mNormal(nullptr)
	, mDanger(nullptr)
	, mDying(nullptr)
	, mIsNormal(false)
	, mIsDanger(false)
	, mIsDying(false)
{
	CONTAINER* c = mOwner->GetGame()->GetRenderer()->GetContainer();
	mNormal = new TREE(c->treeOrigin("HpNormal"));
	mDanger = new TREE(c->treeOrigin("HpDanger"));
	mDying = new TREE(c->treeOrigin("HpDying"));
}

HpGaugeSpriteComponent::~HpGaugeSpriteComponent()
{
	delete mNormal;
	delete mDanger;
	delete mDying;
}

void HpGaugeSpriteComponent::Update()
{
	CharacterActor* owner = static_cast<CharacterActor*>(mOwner);
	VECTOR pos = owner->GetPosition() + mOffset + owner->GetCapsulOffset();
	float preWidth = mGaugeWidth;
	float Width = (float)(owner->GetHp()) / (float)owner->GetMaxHp();
	mGaugeWidth = preWidth + (Width - preWidth) * 0.05f;

	mDivMaxHp = ((float)(1.0f / (float)(owner->GetMaxHp())) / 2);

	float prePosX = mGaugePosX;
	float PosX = -mDivMaxHp * (owner->GetMaxHp() - owner->GetHp());
	mGaugePosX = prePosX + (PosX - prePosX) * 0.05f;

	Master.identity();

	if (mOwner->GetGame()->GetCameraManager()->GetCurCamera())
	{
		Master.mulTranslate(pos.x, pos.y + owner->GetHeight() + 0.5f, pos.z);
		Master.mulTranslate(cosf(mOwner->GetGame()->GetCameraManager()->GetCurCamera()->GetRotation().y) / owner->GetMaxHp(), 0.0f, sinf(mOwner->GetGame()->GetCameraManager()->GetCurCamera()->GetRotation().y) / owner->GetMaxHp());
		Master.mulScaling(1.0f, 0.1f, 1.0f);
		Master.mulRotateY(mOwner->GetGame()->GetCameraManager()->GetCurCamera()->GetRotation().y);
		Master.mulRotateX(3.141592f / 2);
	}
	Master.mulTranslate(mGaugePosX, 0, 1.5f);
	Master.mulScaling(mGaugeWidth, 1, 1);

	mIsNormal = false;
	mIsDanger = false;
	mIsDying = false;

	if (owner->GetHp() >= owner->GetMaxHp() * 0.66f)
	{
		mIsNormal = true;
	}
	else if (owner->GetHp() >= owner->GetMaxHp() * 0.33f)
	{
		mIsDanger = true;
	}
	else if (owner->GetHp() < owner->GetMaxHp() * 0.33f && owner->GetState() == CharacterActor::State::EActive)
	{
		mIsDying = true;
	}

}

void HpGaugeSpriteComponent::Draw()
{
	if (mOwner)
	{
		if (mIsNormal)
		{
			mNormal->update(Master);
			mNormal->draw(GetOwner()->GetGame()->GetRenderer()->GetShader());
		}
		else if (mIsDanger)
		{
			mDanger->update(Master);
			mDanger->draw(GetOwner()->GetGame()->GetRenderer()->GetShader());
		}
		else if (mIsDying)
		{
			mDying->update(Master);
			mDying->draw(GetOwner()->GetGame()->GetRenderer()->GetShader());
		}
	}
}