#include "LookFieldCenterCamera.h"
#include "Game.h"

LookFieldCenterCamera::LookFieldCenterCamera(Game* game)
	: Camera(game)
{
	iData = GetGame()->GetAllData()->lookCenterCameraData;
	SetPosition(iData.mPos);
	SetRotationX(iData.mRotX);
	mCamName = "LookCenterCamera";
	GetGame()->GetCameraManager()->RegisterCamera(this);
}

void LookFieldCenterCamera::UpdateActor()
{
	float rotX = iData.mRotX;
	float rotY = 0.0f;

	VECTOR pos = GetPosition();
	//現在のカメラ位置をとっておく
	VECTOR prePos = pos;

	SetPosition(GetGame()->GetActorManager()->GetStage()->GetCenterPos() + VECTOR(0.0f, iData.mPos.y, 0.0f));

	mLookatPos = GetPosition();
	mLookatPos.y += GetGame()->GetAllData()->cameraData.mOffsetPos.y;

	//カメラの位置を求める
	pos = mLookatPos;
	pos.x += sinf(rotY) * cosf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;
	pos.y += sinf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;
	pos.z += cosf(rotY) * cosf(rotX) * GetGame()->GetAllData()->cameraData.mDistanceFromLookatPos;

	//少し時間差でスムーズにカメラの位置を変更

	SetRotationY(rotY);
	SetRotationX(rotX);
	SetPosition(pos);
}