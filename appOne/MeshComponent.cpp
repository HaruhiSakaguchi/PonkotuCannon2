#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

MeshComponent::MeshComponent(Actor* owner, bool isDraw)
	: Component(owner)
	, mOffsetPos(0.0f, 0.0f, 0.0f)
	, mOffsetAngle(0.0f, 0.0f, 0.0f)
	, mDrawFlag(isDraw)
	, mMeshName(nullptr)
{
	mOwner->GetGame()->GetRenderer()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMesh(this);
}
