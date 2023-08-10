#include "TreeMeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "SHADER/SHADER.h"
#include "CONTAINER/CONTAINER.h"
#include "CONTAINER/TREE.h"
#include "CONTAINER/ANIMATION.h"

TreeMeshComponent::TreeMeshComponent(Actor* owner, bool isDraw)
	: MeshComponent(owner, isDraw)
	, mTree(nullptr)
{
}

TreeMeshComponent::~TreeMeshComponent()
{
	delete mTree;
	mAnims.clear();
}

void TreeMeshComponent::SetTree(const char* name)
{
	CONTAINER* c = mOwner->GetGame()->GetRenderer()->GetContainer();
	mTree = new TREE(c->treeOrigin(name));
	mMeshName = name;
}

void TreeMeshComponent::SetAnim(const char* name)
{
	CONTAINER* c = mOwner->GetGame()->GetRenderer()->GetContainer();
	mAnims.emplace_back(c->animation(name));
}

void TreeMeshComponent::SetAnimId(int id)
{
	mTree->setAnimation(mAnims[id]);
}

void TreeMeshComponent::SetNextAnimId(int id, float morphFrame, float startFrame)
{
	mTree->setNextAnimation(mAnims[id], morphFrame, startFrame);
}

void TreeMeshComponent::Update()
{
	VECTOR pos = mOwner->GetPosition() + mOffsetPos;
	VECTOR angle = mOwner->GetRotation() + mOffsetAngle;
	mWorld.identity();
	mWorld.mulTranslate(pos);
	mWorld.mulRotateY(angle.y);
	mWorld.mulRotateX(angle.x);
	mWorld.mulRotateZ(angle.z);
	mWorld.mulScaling(mOwner->GetScale());
	mTree->update(mWorld);
}

void TreeMeshComponent::Draw()
{
	if (mDrawFlag)
	{
		mTree->draw(mOwner->GetGame()->GetRenderer()->GetShader());
	}
}
