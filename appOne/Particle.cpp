#include "Particle.h"
#include "TreeMeshComponent.h"
#include "BatchMeshComponent.h"
#include "rand.h"
#include <window.h>
#include "Game.h"

Particle::Particle(class Game* game, const VECTOR& pos, float lifeSpan)
	: Actor(game)
	, mLifeSpan(lifeSpan)
	, mMeshType(MeshType::ETree)
	, mTime(0.0f)
	, mVec(0.0f, 1.0f, 0.0f)
	, mAdvSpeed(1.0f)
	, mMesh(nullptr)
{
	SetPosition(pos);
	float scale = random(0.1f, 0.5f);
	SetScale(VECTOR(scale, scale, scale));
	mStart = std::chrono::system_clock::now();
}

void Particle::UpdateActor()
{
	SetPosition(GetPosition() + mVec * delta * mAdvSpeed);
	SetRotationY(GetRotation().y + 0.017f * delta * mAdvSpeed);

	mMesh->SetDrawFlag(true);

	if (mTime < mLifeSpan)
	{
		auto end = std::chrono::system_clock::now();
		auto dur = end - mStart;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		float time = msec / 1000.0f;
		mTime = time;
	}
	else
	{
		SetState(State::EDead);
	}
}

void Particle::SetMesh(const char* name)
{
	if (mMeshType == MeshType::EBatch)
	{
		auto batch = new BatchMeshComponent(this, false);
		batch->SetBatch(name);
		mMesh = batch;
	}
	else if (mMeshType == MeshType::ETree)
	{
		auto tree = new TreeMeshComponent(this, false);
		tree->SetTree(name);
		mMesh = tree;
	}
}
