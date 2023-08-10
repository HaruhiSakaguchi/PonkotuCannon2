#include "BatchMeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "CONTAINER/CONTAINER.h"
#include "CONTAINER/BATCH.h"

BatchMeshComponent::BatchMeshComponent(Actor* owner, bool isDraw)
	: MeshComponent(owner, isDraw)
	, mBatch(nullptr)
{
}

BatchMeshComponent::~BatchMeshComponent()
{

}

void BatchMeshComponent::SetBatch(const char* name)
{
	CONTAINER* c = mOwner->GetGame()->GetRenderer()->GetContainer();
	mBatch = c->batch(name);
	mMeshName = name;
}

void BatchMeshComponent::Draw()
{
	VECTOR pos = mOwner->GetPosition() + mOffsetPos;
	VECTOR angle = mOwner->GetRotation() + mOffsetAngle;
	mWorld.identity();
	mWorld.mulTranslate(pos);
	mWorld.mulRotateY(angle.y);
	mWorld.mulRotateX(angle.x);
	mWorld.mulRotateZ(angle.z);
	mWorld.mulScaling(mOwner->GetScale());

	if (mDrawFlag)
	{
		mBatch->draw(mOwner->GetGame()->GetRenderer()->GetShader(), mWorld);
	}
}
