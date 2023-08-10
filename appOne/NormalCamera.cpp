#include "NormalCamera.h"
#include "Camera.h"
#include "Game.h"

NormalCamera::NormalCamera(Game* game)
	: Camera(game)
{
	SetRotationX(iData.mRotX);
	SetPosition(iData.mPos);

	iData = GetGame()->GetAllData()->normalCameraData;
	mCamName = "NormalCamera";
	GetGame()->GetCameraManager()->RegisterCamera(this);
}

void NormalCamera::UpdateActor()
{
	float rotX = GetRotation().x;
	float rotY = GetRotation().y;

	VECTOR pos = GetPosition();
	//現在のカメラ位置をとっておく
	VECTOR prePos = pos;
	SetPosition(iData.mPos);
	mLookatPos = iData.mLookatPosOffset + VECTOR(0.0f, 0.0f, GetGame()->GetActorManager()->GetStage()->GetCenterPos().z);
	pos = GetPosition();
	mLookatPos.y += GetGame()->GetAllData()->cameraData.mOffsetPos.y;

	//カメラの位置を求める
	pos.x += sinf(rotY) * cosf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;
	pos.y += sinf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;
	pos.z += cosf(rotY) * cosf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;

	SetPosition(pos);
}
