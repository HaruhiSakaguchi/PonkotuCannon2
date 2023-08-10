#pragma once
#include "Component.h"
#include "MATRIX.h"

class MeshComponent :
	public Component
{
public:
	MeshComponent(class Actor*, bool isDraw = true);
	virtual ~MeshComponent();
	virtual void Update() {};
	virtual void Draw() {};
	void SetOffsetPos(const VECTOR& pos) { mOffsetPos = pos; }
	void SetOffsetAngle(const VECTOR& angle) { mOffsetPos = angle; }
	void SetDrawFlag(bool flag) { mDrawFlag = flag; }
	const char* GetMeshName() { return mMeshName; }
protected:
	MATRIX mWorld;
	VECTOR mOffsetPos;
	VECTOR mOffsetAngle;
	bool mDrawFlag;
	const char* mMeshName;
};

