#pragma once
#include "Actor.h"
#include <chrono>

class Particle :
	public Actor
{
public:
	Particle(class Game* game, const VECTOR& pos, float lifeSpan = 1.0f);
	void UpdateActor()override;
	void SetMesh(const char* name);
	void SetVector(const VECTOR& vec) { mVec = vec; }
	void SetAdvSpeed(float speed) { mAdvSpeed = speed; }
	void SetMeshComponent(class MeshComponent* mesh) { mMesh = mesh; }
	enum class MeshType
	{
		EBatch,
		ETree
	};
	void SetMeshType(MeshType meshType) { mMeshType = meshType; }
private:
	float mLifeSpan;
	MeshType mMeshType;
	std::chrono::system_clock::time_point mStart;
	float mTime;
	VECTOR mVec;
	float mAdvSpeed;
	class MeshComponent* mMesh;
};

