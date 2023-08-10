#include "LookPHomeCamera.h"
#include "Game.h"
#include "PlayerHome.h"

LookPHomeCamera::LookPHomeCamera(Game* game)
	: Camera(game)
{
	mCamName = "PHomeCamera";
	GetGame()->GetCameraManager()->RegisterCamera(this);
	iData = GetGame()->GetAllData()->lookPHomeCameraData;
}

void LookPHomeCamera::UpdateActor()
{
	VECTOR pos = GetPosition();

	if (GetGame()->GetActorManager()->GetPHome())
	{
		SetPosition(GetGame()->GetActorManager()->GetPHome()->GetPosition());
		mLookatPos = GetGame()->GetActorManager()->GetPHome()->GetPosition();
	}
	pos = GetPosition() + iData.mLookatPosOffset;

	SetPosition(pos);
}